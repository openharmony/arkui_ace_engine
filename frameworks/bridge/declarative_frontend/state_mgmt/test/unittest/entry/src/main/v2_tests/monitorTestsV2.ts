/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { eq, gt, ITestFile } from '../lib/testRunner'

interface IMonitorValue<T> {
  before: T;
  now: T;
  path: string;
}

interface IMonitor {
  dirty: Array<string>;
  value<T>(key?: string): IMonitorValue<T> | undefined;
}

declare class MonitorPathHelper {
  static hasWildcardEnding(path: string): boolean;
  static isWildcardSubPath(path: string): boolean;
  static pathBeforeWildcard(path: string): string;
  static isValidForSyncMonitor(path: string): boolean;
  static isValidForMonitor(path: string): boolean;
}

declare class MonitorValueV2<T> {
  constructor(path: string, id?: number);
  before?: T;
  now?: T;
  path: string;
  props: string[];
  private dirty;
  constructor(path: string);
  setNotFound(isInit: boolean): boolean;
  setValue(isInit: boolean, newValue: T): boolean;
  reset(): void;
  isDirty(): boolean;
  isWildcard(): boolean;
  getWildcardPath(): MonitorValueV2<T> | undefined;
  setWildcardPath(childPath: MonitorValueV2<T> | undefined): void;
  getLastSureValuePath(): MonitorValueV2<T> | undefined;
  setLastSureValuePath(path: MonitorValueV2<T> | undefined): void;
  getReportedPath(): string;
  setReportedPath(path): void;
}

declare class MonitorV2 {
  static readonly WATCH_PREFIX: string;
  static readonly WATCH_INSTANCE_PREFIX: string;
  static readonly SYNC_MONITOR_PREFIX: string;
  static readonly OB_ANY: string;
  static readonly LSV_PREFIX: string;

  static readonly MIN_WATCH_ID: number;
  static readonly MIN_WATCH_FROM_API_ID: number;
  static readonly MIN_SYNC_WATCH_FROM_API_ID: number;
  static nextWatchId_: number;
  static nextWatchApiId_: number;
  static nextSyncWatchApiId_: number;
  static runningCount: number;

  constructor(
    target: object,
    pathsString: string,
    func: (m: IMonitor) => void,
    isDecorator: boolean,
    isSync?: boolean
  );

  getTarget(): Object;
  isSync(): boolean;
  addPath(path: string, lsv?: boolean): MonitorValueV2<unknown> | undefined;
  removePath(path: string): boolean;
  isSyncDecorator(): boolean;
  isMonitorDecorator(): boolean;
  getWatchId(): number;
  getMonitorFuncName(): string;
  getValues(): Map<string, MonitorValueV2<unknown>>;
  get dirty(): Array<string>;
  value<T>(path?: string): IMonitorValue<T>;
  InitRun(): MonitorV2;
  recordDependenciesForProps(): void;
  runMonitorFunction(): void;
  notifyChange(): void;
  notifyChangeForEachPath(pathId: number): number;
  notifyChangeOnReuse(): void;
  getDecoratorName(): string;
  errorMessage(path: string, description: string): string;

  static getMonitorIds(target: Object): number[];
  static clearWatchesFromTarget(target: Object): void;
  // Expose as public
  public values_: Map<string, MonitorValueV2<unknown>>;
  public monitorFunction: (m: IMonitor) => void;

}

declare const ObservedV2: <TFunction extends Function>(target: TFunction) => TFunction | void;
declare const Local: (target: Object, propertyKey: string | symbol) => void;

// Locally defined classes for testing purposes
@ObservedV2
class TestClass {
  @Local testVar1 : number = 0;
  @Local testVar2 : number = 0;
  @Local testVar3 : number = 0;

  constructor () {
  }
}

export class MonitorTestsV2 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll () : void {}

  // Executed before every individual tests. Can be empty
  public beforeEach () : void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}

  public getId(): string {
    return this.idString;
  }

  // Test cases start from here. All functions are run automatically except those starting with _

  /* Monitor creation test. Adds monitor to testClass
  * Monitor has 3 properties to watch ('testVar1 testVar2 testVar3')
  * Output:
  * testClass before monitor: {"__ob_testVar1":0,"__ob_testVar2":0,"__ob_testVar3":0}
  * Num monitored props 3
  * testClass after monitor: {"__ob_testVar1":0,"__ob_testVar2":0,"__ob_testVar3":0,
  * "___watch__obj_":{"testVar1 testVar2 testVar3":281474976710657}}
  */
  public testBasicMonitorCreation(): void {
    let testClass = new TestClass();
    const watchIdBegin = MonitorV2.nextWatchId_;
    console.log(`testClass before monitor: ${JSON.stringify(testClass)}`)

    let monitor = new MonitorV2(testClass, 'testVar1 testVar2 testVar3', (m: IMonitor) => {
    }, true, false)
    console.log(`Num monitored props ${monitor.values_.size} + Watch Id ${MonitorV2.nextWatchId_}`);
    console.log(`testClass after monitor: ${JSON.stringify(testClass)}`)
    // 3 because of these (testVar1 testVar2 testVar3)
    eq(monitor.values_.size, 3, "added three monitor values");
    eq(MonitorV2.nextWatchId_ - watchIdBegin, 1, "watch id increased by one");
  }
}

export class MonitorPathHelperTests implements ITestFile {
  private idString: string = "";
  private static readonly TEST_CLASS_NAME: string = "MonitorPathHelperTests";

  constructor(str: string) {
    this.initializeTestSuite(str);
  }

  private initializeTestSuite(str: string): void {
    this.logTestSuiteCreation(str);
    this.assignIdString(str);
  }

  private logTestSuiteCreation(str: string): void {
    const message: string = this.formatCreationMessage(str);
    console.log(message);
  }

  private formatCreationMessage(str: string): string {
    const prefix: string = "Creating StateManagementTest: ";
    const fullMessage: string = prefix + str;
    return fullMessage;
  }

  private assignIdString(str: string): void {
    this.idString = str;
  }

  public beforeAll(): void {
    this.executeBeforeAllHook();
  }

  private executeBeforeAllHook(): void {
    // Empty implementation
  }

  public beforeEach(): void {
    this.executeBeforeEachHook();
  }

  private executeBeforeEachHook(): void {
    // Empty implementation
  }

  public afterAll(): void {
    this.executeAfterAllHook();
  }

  private executeAfterAllHook(): void {
    // Empty implementation
  }

  public afterEach(): void {
    this.executeAfterEachHook();
  }

  private executeAfterEachHook(): void {
    // Empty implementation
  }

  public getId(): string {
    return this.retrieveIdString();
  }

  private retrieveIdString(): string {
    const id: string = this.idString;
    return id;
  }

  // MonitorPathHelper tests

  public testPathHelperWildcardEnding(): void {
    this.testWildcardEndingWithWildcard();
    this.testWildcardEndingWithoutWildcard();
    this.testWildcardEndingSingleAsterisk();
    this.testWildcardEndingEmptyString();
  }

  private testWildcardEndingWithWildcard(): void {
    const testPath: string = "a.b.*";
    const result: boolean = MonitorPathHelper.hasWildcardEnding(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Check for wildcard ending";
    eq(result, expectedResult, errorMessage);
  }

  private testWildcardEndingWithoutWildcard(): void {
    const testPath: string = "a.b.c";
    const result: boolean = MonitorPathHelper.hasWildcardEnding(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "No wildcard ending";
    eq(result, expectedResult, errorMessage);
  }

  private testWildcardEndingSingleAsterisk(): void {
    const testPath: string = "*";
    const result: boolean = MonitorPathHelper.hasWildcardEnding(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Single wildcard is not ending";
    eq(result, expectedResult, errorMessage);
  }

  private testWildcardEndingEmptyString(): void {
    const testPath: string = "";
    const result: boolean = MonitorPathHelper.hasWildcardEnding(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Empty string has no wildcard ending";
    eq(result, expectedResult, errorMessage);
  }

  public testPathHelperValidForMonitor(): void {
    this.testValidForMonitorNormalPath();
    this.testValidForMonitorWithWildcardEnding();
    this.testValidForMonitorSingleWildcard();
    this.testValidForMonitorWildcardInMiddle();
    this.testValidForMonitorEmptyPath();
  }

  private testValidForMonitorNormalPath(): void {
    const testPath: string = "a.b";
    const result: boolean = MonitorPathHelper.isValidForMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Check for wildcard ending";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForMonitorWithWildcardEnding(): void {
    const testPath: string = "a.b.*";
    const result: boolean = MonitorPathHelper.isValidForMonitor(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Check for wildcard ending";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForMonitorSingleWildcard(): void {
    const testPath: string = "*";
    const result: boolean = MonitorPathHelper.isValidForMonitor(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Single wildcard not valid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForMonitorWildcardInMiddle(): void {
    const testPath: string = "a.*.b";
    const result: boolean = MonitorPathHelper.isValidForMonitor(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Wildcard in middle not valid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForMonitorEmptyPath(): void {
    const testPath: string = "";
    const result: boolean = MonitorPathHelper.isValidForMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Empty path is valid";
    eq(result, expectedResult, errorMessage);
  }

  public testPathHelperIsWildcardSubPath(): void {
    this.testWildcardSubPathSingleAsterisk();
    this.testWildcardSubPathWithEnding();
    this.testWildcardSubPathRegularPath();
  }

  private testWildcardSubPathSingleAsterisk(): void {
    const testPath: string = "*";
    const result: boolean = MonitorPathHelper.isWildcardSubPath(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Single asterisk is wildcard subpath";
    eq(result, expectedResult, errorMessage);
  }

  private testWildcardSubPathWithEnding(): void {
    const testPath: string = "a.*";
    const result: boolean = MonitorPathHelper.isWildcardSubPath(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Path with wildcard ending is not wildcard subpath";
    eq(result, expectedResult, errorMessage);
  }

  private testWildcardSubPathRegularPath(): void {
    const testPath: string = "a.b.c";
    const result: boolean = MonitorPathHelper.isWildcardSubPath(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Regular path is not wildcard subpath";
    eq(result, expectedResult, errorMessage);
  }

  public testPathHelperPathBeforeWildcard(): void {
    this.testPathBeforeWildcardDeepPath();
    this.testPathBeforeWildcardNoWildcard();
    this.testPathBeforeWildcardSingleSegment();
    this.testPathBeforeWildcardNestedPath();
  }

  private testPathBeforeWildcardDeepPath(): void {
    const testPath: string = "a.b.c.*";
    const result: string = MonitorPathHelper.pathBeforeWildcard(testPath);
    const expectedResult: string = "a.b.c";
    const errorMessage: string = "Extract path before wildcard";
    eq(result, expectedResult, errorMessage);
  }

  private testPathBeforeWildcardNoWildcard(): void {
    const testPath: string = "a.b";
    const result: string = MonitorPathHelper.pathBeforeWildcard(testPath);
    const expectedResult: string = "a.b";
    const errorMessage: string = "Path without wildcard returns unchanged";
    eq(result, expectedResult, errorMessage);
  }

  private testPathBeforeWildcardSingleSegment(): void {
    const testPath: string = "x.*";
    const result: string = MonitorPathHelper.pathBeforeWildcard(testPath);
    const expectedResult: string = "x";
    const errorMessage: string = "Single segment before wildcard";
    eq(result, expectedResult, errorMessage);
  }

  private testPathBeforeWildcardNestedPath(): void {
    const testPath: string = "deep.nested.path.*";
    const result: string = MonitorPathHelper.pathBeforeWildcard(testPath);
    const expectedResult: string = "deep.nested.path";
    const errorMessage: string = "Deep nested path before wildcard";
    eq(result, expectedResult, errorMessage);
  }

  public testPathHelperIsValidForSyncMonitor(): void {
    this.testValidForSyncMonitorNoWildcards();
    this.testValidForSyncMonitorEndingWildcard();
    this.testValidForSyncMonitorMiddleWildcard();
    this.testValidForSyncMonitorMultipleWildcards();
    this.testValidForSyncMonitorSingleWildcard();
    this.testValidForSyncMonitorEmptyPath();
  }

  private testValidForSyncMonitorNoWildcards(): void {
    const testPath: string = "a.b.c";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Path with no wildcards is valid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForSyncMonitorEndingWildcard(): void {
    const testPath: string = "a.b.*";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Path with ending wildcard is valid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForSyncMonitorMiddleWildcard(): void {
    const testPath: string = "a.*.b";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Wildcard in middle is invalid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForSyncMonitorMultipleWildcards(): void {
    const testPath: string = "*.*";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Multiple wildcards are invalid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForSyncMonitorSingleWildcard(): void {
    const testPath: string = "*";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = false;
    const errorMessage: string = "Single wildcard with no dots is not valid";
    eq(result, expectedResult, errorMessage);
  }

  private testValidForSyncMonitorEmptyPath(): void {
    const testPath: string = "";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Empty path is valid";
    eq(result, expectedResult, errorMessage);
  }

  public testPathHelperEdgeCases(): void {
    this.testEdgeCaseDotAndWildcard();
    this.testEdgeCaseEmptyPathBeforeWildcard();
    this.testEdgeCaseEmptyStringValidation();
  }

  private testEdgeCaseDotAndWildcard(): void {
    const testPath: string = ".*";
    const result: boolean = MonitorPathHelper.hasWildcardEnding(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Just dot and wildcard";
    eq(result, expectedResult, errorMessage);
  }

  private testEdgeCaseEmptyPathBeforeWildcard(): void {
    const testPath: string = ".*";
    const result: string = MonitorPathHelper.pathBeforeWildcard(testPath);
    const expectedResult: string = "";
    const errorMessage: string = "Empty path before wildcard";
    eq(result, expectedResult, errorMessage);
  }

  private testEdgeCaseEmptyStringValidation(): void {
    const testPath: string = "";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Empty string has no wildcards";
    eq(result, expectedResult, errorMessage);
  }

  public testPathHelperComplexPaths(): void {
    this.testComplexPathDeepWithoutWildcards();
    this.testComplexPathSyncWithWildcard();
    this.testComplexPathLongExtraction();
  }

  private testComplexPathDeepWithoutWildcards(): void {
    const testPath: string = "root.module.component.prop";
    const result: boolean = MonitorPathHelper.isValidForMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Deep path without wildcards";
    eq(result, expectedResult, errorMessage);
  }

  private testComplexPathSyncWithWildcard(): void {
    const testPath: string = "root.module.*";
    const result: boolean = MonitorPathHelper.isValidForSyncMonitor(testPath);
    const expectedResult: boolean = true;
    const errorMessage: string = "Valid sync monitor with wildcard ending";
    eq(result, expectedResult, errorMessage);
  }

  private testComplexPathLongExtraction(): void {
    const testPath: string = "very.long.nested.path.structure.*";
    const result: string = MonitorPathHelper.pathBeforeWildcard(testPath);
    const expectedResult: string = "very.long.nested.path.structure";
    const errorMessage: string = "Long path extraction";
    eq(result, expectedResult, errorMessage);
  }

}

export class MonitorValueTests implements ITestFile {
  private idString: string = "";
  private static readonly CLASS_NAME: string = "MonitorValueTests";
  private static readonly EMPTY_STRING: string = "";
  private static readonly DEFAULT_ID: string = "";

  constructor(str: string) {
    this.performConstructorInitialization(str);
  }

  private performConstructorInitialization(str: string): void {
    this.logCreationMessage(str);
    this.initializeIdString(str);
  }

  private logCreationMessage(str: string): void {
    const message: string = this.buildCreationMessage(str);
    this.outputToConsole(message);
  }

  private buildCreationMessage(str: string): string {
    const prefix: string = "Creating StateManagementTest: ";
    const fullMessage: string = this.concatenateStrings(prefix, str);
    return fullMessage;
  }

  private concatenateStrings(str1: string, str2: string): string {
    const result: string = str1 + str2;
    return result;
  }

  private outputToConsole(message: string): void {
    console.log(message);
  }

  private initializeIdString(str: string): void {
    this.idString = str;
  }

  public beforeAll(): void {
    this.executeBeforeAllSetup();
  }

  private executeBeforeAllSetup(): void {
    // Empty implementation - can be overridden in subclasses
    const setupComplete: boolean = true;
  }

  public beforeEach(): void {
    this.executeBeforeEachSetup();
  }

  private executeBeforeEachSetup(): void {
    // Empty implementation - can be overridden in subclasses
    const setupComplete: boolean = true;
  }

  public afterAll(): void {
    this.executeAfterAllCleanup();
  }

  private executeAfterAllCleanup(): void {
    // Empty implementation - can be overridden in subclasses
    const cleanupComplete: boolean = true;
  }

  public afterEach(): void {
    this.executeAfterEachCleanup();
  }

  private executeAfterEachCleanup(): void {
    // Empty implementation - can be overridden in subclasses
    const cleanupComplete: boolean = true;
  }

  public getId(): string {
    return this.retrieveIdString();
  }

  private retrieveIdString(): string {
    const currentId: string = this.idString;
    return currentId;
  }

  // MonitorValueV2 tests

  public testMonitorValueReturnPath(): void {
    const testPath: string = this.createTestPath();
    const monitorValue: MonitorValueV2<number> = this.createNumberMonitorValue(testPath);

    this.verifyReportedPathMatches(monitorValue, testPath);
    this.verifyPathPropertyMatches(monitorValue, testPath);
  }

  private createTestPath(): string {
    const segment1: string = "a";
    const segment2: string = "b";
    const segment3: string = "c";
    const wildcard: string = "*";
    const separator: string = ".";

    const path: string = this.buildPathFromSegments(
      segment1,
      segment2,
      segment3,
      wildcard,
      separator
    );

    return path;
  }

  private buildPathFromSegments(
    seg1: string,
    seg2: string,
    seg3: string,
    wildcard: string,
    separator: string
  ): string {
    const part1: string = seg1 + separator + seg2;
    const part2: string = part1 + separator + seg3;
    const fullPath: string = part2 + separator + wildcard;
    return fullPath;
  }

  private createNumberMonitorValue(path: string): MonitorValueV2<number> {
    const monitorValue: MonitorValueV2<number> = new MonitorValueV2<number>(path);
    return monitorValue;
  }

  private verifyReportedPathMatches(
    monitorValue: MonitorValueV2<number>,
    expectedPath: string
  ): void {
    const actualReportedPath: string = monitorValue.getReportedPath();
    const errorMessage: string = "Check for reported path";
    this.assertEquality(actualReportedPath, expectedPath, errorMessage);
  }

  private verifyPathPropertyMatches(
    monitorValue: MonitorValueV2<number>,
    expectedPath: string
  ): void {
    const actualPath: string = monitorValue.path;
    const errorMessage: string = "Check for path property";
    this.assertEquality(actualPath, expectedPath, errorMessage);
  }

  private assertEquality<T>(actual: T, expected: T, message: string): void {
    eq(actual, expected, message);
  }

  public testMonitorValueSetValue(): void {
    const path: string = this.createSimplePath();
    const monitorValue: MonitorValueV2<number> = this.createNumberMonitorValue(path);

    this.performInitialValueSetTest(monitorValue);
    this.performSubsequentValueSetTest(monitorValue);
  }

  private createSimplePath(): string {
    const segment1: string = "a";
    const segment2: string = "b";
    const segment3: string = "c";
    const separator: string = ".";

    const path: string = this.joinPathSegments(segment1, segment2, segment3, separator);
    return path;
  }

  private joinPathSegments(
    seg1: string,
    seg2: string,
    seg3: string,
    separator: string
  ): string {
    const part1: string = seg1 + separator + seg2;
    const fullPath: string = part1 + separator + seg3;
    return fullPath;
  }

  private performInitialValueSetTest(monitorValue: MonitorValueV2<number>): void {
    const isInitialSet: boolean = true;
    const initialValue: number = 42;
    const isDirtyResult: boolean = this.setValueOnMonitor(
      monitorValue,
      isInitialSet,
      initialValue
    );

    this.verifyNotDirtyAfterInitialSet(isDirtyResult);
    this.verifyValueWasSet(monitorValue, initialValue);
  }

  private setValueOnMonitor(
    monitorValue: MonitorValueV2<number>,
    isInit: boolean,
    value: number
  ): boolean {
    const isDirty: boolean = monitorValue.setValue(isInit, value);
    return isDirty;
  }

  private verifyNotDirtyAfterInitialSet(isDirty: boolean): void {
    const expectedDirtyState: boolean = false;
    const errorMessage: string = "Setting initial value should not mark as dirty";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  private verifyValueWasSet(
    monitorValue: MonitorValueV2<number>,
    expectedValue: number
  ): void {
    const actualValue: number | undefined = monitorValue.now;
    const errorMessage: string = "Value should be set to 42";
    this.assertEquality(actualValue, expectedValue, errorMessage);
  }

  private performSubsequentValueSetTest(monitorValue: MonitorValueV2<number>): void {
    const isInitialSet: boolean = false;
    const newValue: number = 84;
    const isDirtyResult: boolean = this.setValueOnMonitor(
      monitorValue,
      isInitialSet,
      newValue
    );

    this.verifyDirtyAfterValueChange(monitorValue);
  }

  private verifyDirtyAfterValueChange(monitorValue: MonitorValueV2<number>): void {
    const isDirty: boolean = monitorValue.isDirty();
    const expectedDirtyState: boolean = true;
    const errorMessage: string = "Monitor should be dirty after setValue with new value";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  public testMonitorValueSetNotFound(): void {
    const path: string = this.createSimplePath();
    const monitorValue: MonitorValueV2<string> = this.createStringMonitorValue(path);

    this.performSetNotFoundTest(monitorValue);
  }

  private createStringMonitorValue(path: string): MonitorValueV2<string> {
    const monitorValue: MonitorValueV2<string> = new MonitorValueV2<string>(path);
    return monitorValue;
  }

  private performSetNotFoundTest(monitorValue: MonitorValueV2<string>): void {
    const isInitialSet: boolean = true;
    const isDirtyResult: boolean = this.setNotFoundOnMonitor(monitorValue, isInitialSet);

    this.verifyNotDirtyAfterSetNotFound(isDirtyResult);
    this.verifyValueIsUndefined(monitorValue);
  }

  private setNotFoundOnMonitor(
    monitorValue: MonitorValueV2<string>,
    isInit: boolean
  ): boolean {
    const isDirty: boolean = monitorValue.setNotFound(isInit);
    return isDirty;
  }

  private verifyNotDirtyAfterSetNotFound(isDirty: boolean): void {
    const expectedDirtyState: boolean = false;
    const errorMessage: string = "Setting not found with init should not mark as dirty";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  private verifyValueIsUndefined(monitorValue: MonitorValueV2<string>): void {
    const actualValue: string | undefined = monitorValue.now;
    const expectedValue: undefined = undefined;
    const errorMessage: string = "Value should be undefined when not found";
    this.assertEquality(actualValue, expectedValue, errorMessage);
  }

  public testMonitorValueReset(): void {
    const path: string = this.createResetTestPath();
    const id: number = this.createTestId();
    const monitorValue: MonitorValueV2<number> = this.createMonitorValueWithId(path, id);

    this.performResetTest(monitorValue);
  }

  private createResetTestPath(): string {
    const segment1: string = "x";
    const segment2: string = "y";
    const separator: string = ".";
    const path: string = segment1 + separator + segment2;
    return path;
  }

  private createTestId(): number {
    const id: number = 1;
    return id;
  }

  private createMonitorValueWithId(path: string, id: number): MonitorValueV2<number> {
    const monitorValue: MonitorValueV2<number> = new MonitorValueV2<number>(path, id);
    return monitorValue;
  }

  private performResetTest(monitorValue: MonitorValueV2<number>): void {
    this.setValueAndVerifyDirty(monitorValue);
    this.resetAndVerifyClean(monitorValue);
  }

  private setValueAndVerifyDirty(monitorValue: MonitorValueV2<number>): void {
    const isInitialSet: boolean = false;
    const testValue: number = 100;
    this.setValueOnMonitor(monitorValue, isInitialSet, testValue);

    const isDirty: boolean = this.checkIfMonitorIsDirty(monitorValue);
    const expectedDirtyState: boolean = true;
    const errorMessage: string = "Should be dirty after setValue";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  private checkIfMonitorIsDirty(monitorValue: MonitorValueV2<number>): boolean {
    const isDirty: boolean = monitorValue.isDirty();
    return isDirty;
  }

  private resetAndVerifyClean(monitorValue: MonitorValueV2<number>): void {
    this.resetMonitorValue(monitorValue);

    const isDirty: boolean = this.checkIfMonitorIsDirty(monitorValue);
    const expectedDirtyState: boolean = false;
    const errorMessage: string = "Should not be dirty after reset";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  private resetMonitorValue(monitorValue: MonitorValueV2<number>): void {
    monitorValue.reset();
  }

  public testMonitorValueBeforeAndNow(): void {
    const path: string = this.createBeforeNowTestPath();
    const monitorValue: MonitorValueV2<string> = this.createStringMonitorValue(path);

    this.performBeforeNowTest(monitorValue);
  }

  private createBeforeNowTestPath(): string {
    const segment1: string = "test";
    const segment2: string = "path";
    const separator: string = ".";
    const path: string = segment1 + separator + segment2;
    return path;
  }

  private performBeforeNowTest(monitorValue: MonitorValueV2<string>): void {
    const initialValue: string = "initial";
    const updatedValue: string = "updated";

    this.setInitialValueForBeforeNowTest(monitorValue, initialValue);
    this.resetMonitorValueForBeforeNowTest(monitorValue);
    this.setUpdatedValueForBeforeNowTest(monitorValue, updatedValue);

    this.verifyBeforeValue(monitorValue, initialValue);
    this.verifyNowValue(monitorValue, updatedValue);
  }

  private setInitialValueForBeforeNowTest(
    monitorValue: MonitorValueV2<string>,
    value: string
  ): void {
    const isInitialSet: boolean = true;
    this.setStringValueOnMonitor(monitorValue, isInitialSet, value);
  }

  private setStringValueOnMonitor(
    monitorValue: MonitorValueV2<string>,
    isInit: boolean,
    value: string
  ): boolean {
    const isDirty: boolean = monitorValue.setValue(isInit, value);
    return isDirty;
  }

  private resetMonitorValueForBeforeNowTest(monitorValue: MonitorValueV2<string>): void {
    monitorValue.reset();
  }

  private setUpdatedValueForBeforeNowTest(
    monitorValue: MonitorValueV2<string>,
    value: string
  ): void {
    const isInitialSet: boolean = false;
    this.setStringValueOnMonitor(monitorValue, isInitialSet, value);
  }

  private verifyBeforeValue(
    monitorValue: MonitorValueV2<string>,
    expectedValue: string
  ): void {
    const actualBeforeValue: string | undefined = monitorValue.before;
    const errorMessage: string = "Before value should be initial";
    this.assertEquality(actualBeforeValue, expectedValue, errorMessage);
  }

  private verifyNowValue(
    monitorValue: MonitorValueV2<string>,
    expectedValue: string
  ): void {
    const actualNowValue: string | undefined = monitorValue.now;
    const errorMessage: string = "Now value should be updated";
    this.assertEquality(actualNowValue, expectedValue, errorMessage);
  }

  public testMonitorValueIsWildcard(): void {
    const wildcardPath: string = this.createWildcardPath();
    const regularPath: string = this.createRegularPath();

    const wildcardMonitor: MonitorValueV2<number> = this.createNumberMonitorValue(wildcardPath);
    const regularMonitor: MonitorValueV2<number> = this.createNumberMonitorValue(regularPath);

    this.verifyIsWildcard(wildcardMonitor);
    this.verifyIsNotWildcard(regularMonitor);
  }

  private createWildcardPath(): string {
    const segment1: string = "a";
    const segment2: string = "b";
    const wildcard: string = "*";
    const separator: string = ".";

    const path: string = this.buildWildcardPathFromSegments(
      segment1,
      segment2,
      wildcard,
      separator
    );

    return path;
  }

  private buildWildcardPathFromSegments(
    seg1: string,
    seg2: string,
    wildcard: string,
    separator: string
  ): string {
    const part1: string = seg1 + separator + seg2;
    const fullPath: string = part1 + separator + wildcard;
    return fullPath;
  }

  private createRegularPath(): string {
    const segment1: string = "a";
    const segment2: string = "b";
    const segment3: string = "c";
    const separator: string = ".";

    const path: string = this.joinPathSegments(segment1, segment2, segment3, separator);
    return path;
  }

  private verifyIsWildcard(monitorValue: MonitorValueV2<number>): void {
    const isWildcard: boolean = this.checkIfWildcard(monitorValue);
    const expectedResult: boolean = true;
    const errorMessage: string = "Path ending with .* should be wildcard";
    this.assertEquality(isWildcard, expectedResult, errorMessage);
  }

  private checkIfWildcard(monitorValue: MonitorValueV2<number>): boolean {
    const isWildcard: boolean = monitorValue.isWildcard();
    return isWildcard;
  }

  private verifyIsNotWildcard(monitorValue: MonitorValueV2<number>): void {
    const isWildcard: boolean = this.checkIfWildcard(monitorValue);
    const expectedResult: boolean = false;
    const errorMessage: string = "Regular path should not be wildcard";
    this.assertEquality(isWildcard, expectedResult, errorMessage);
  }

  public testMonitorValueWildcardPath(): void {
    const parentPath: string = this.createWildcardPath();
    const childPath: string = this.createRegularPath();

    const parentMonitor: MonitorValueV2<number> = this.createNumberMonitorValue(parentPath);
    const childMonitor: MonitorValueV2<number> = this.createNumberMonitorValue(childPath);

    this.performWildcardPathLinkingTest(parentMonitor, childMonitor);
  }

  private performWildcardPathLinkingTest(
    parentMonitor: MonitorValueV2<number>,
    childMonitor: MonitorValueV2<number>
  ): void {
    this.setWildcardPathOnParent(parentMonitor, childMonitor);
    this.verifyWildcardPathRetrieval(parentMonitor, childMonitor);
  }

  private setWildcardPathOnParent(
    parentMonitor: MonitorValueV2<number>,
    childMonitor: MonitorValueV2<number>
  ): void {
    parentMonitor.setWildcardPath(childMonitor);
  }

  private verifyWildcardPathRetrieval(
    parentMonitor: MonitorValueV2<number>,
    expectedChild: MonitorValueV2<number>
  ): void {
    const actualChild: MonitorValueV2<number> | undefined = parentMonitor.getWildcardPath();
    const errorMessage: string = "Should retrieve the set wildcard path";
    this.assertEquality(actualChild, expectedChild, errorMessage);
  }

  public testMonitorValueLastSureValuePath(): void {
    const monitorPath: string = this.createRegularPath();
    const lsvPath: string = this.createLsvPath();

    const monitor: MonitorValueV2<string> = this.createStringMonitorValue(monitorPath);
    const lsvMonitor: MonitorValueV2<string> = this.createStringMonitorValue(lsvPath);

    this.performLastSureValuePathTest(monitor, lsvMonitor);
  }

  private createLsvPath(): string {
    const segment1: string = "a";
    const segment2: string = "b";
    const separator: string = ".";
    const path: string = segment1 + separator + segment2;
    return path;
  }

  private performLastSureValuePathTest(
    monitor: MonitorValueV2<string>,
    lsvMonitor: MonitorValueV2<string>
  ): void {
    this.setLastSureValuePathOnMonitor(monitor, lsvMonitor);
    this.verifyLastSureValuePathRetrieval(monitor, lsvMonitor);
  }

  private setLastSureValuePathOnMonitor(
    monitor: MonitorValueV2<string>,
    lsvMonitor: MonitorValueV2<string>
  ): void {
    monitor.setLastSureValuePath(lsvMonitor);
  }

  private verifyLastSureValuePathRetrieval(
    monitor: MonitorValueV2<string>,
    expectedLsv: MonitorValueV2<string>
  ): void {
    const actualLsv: MonitorValueV2<string> | undefined = monitor.getLastSureValuePath();
    const errorMessage: string = "Should retrieve the set LSV path";
    this.assertEquality(actualLsv, expectedLsv, errorMessage);
  }

  public testMonitorValueSetReportedPath(): void {
    const originalPath: string = this.createOriginalPath();
    const customReportedPath: string = this.createCustomReportedPath();

    const monitorValue: MonitorValueV2<number> = this.createNumberMonitorValue(originalPath);

    this.performReportedPathTest(monitorValue, originalPath, customReportedPath);
  }

  private createOriginalPath(): string {
    const segment1: string = "original";
    const segment2: string = "path";
    const separator: string = ".";
    const path: string = segment1 + separator + segment2;
    return path;
  }

  private createCustomReportedPath(): string {
    const segment1: string = "custom";
    const segment2: string = "reported";
    const segment3: string = "path";
    const separator: string = ".";

    const part1: string = segment1 + separator + segment2;
    const fullPath: string = part1 + separator + segment3;
    return fullPath;
  }

  private performReportedPathTest(
    monitorValue: MonitorValueV2<number>,
    originalPath: string,
    customPath: string
  ): void {
    this.setReportedPathOnMonitor(monitorValue, customPath);
    this.verifyReportedPathUpdated(monitorValue, customPath);
    this.verifyOriginalPathUnchanged(monitorValue, originalPath);
  }

  private setReportedPathOnMonitor(
    monitorValue: MonitorValueV2<number>,
    reportedPath: string
  ): void {
    monitorValue.setReportedPath(reportedPath);
  }

  private verifyReportedPathUpdated(
    monitorValue: MonitorValueV2<number>,
    expectedPath: string
  ): void {
    const actualReportedPath: string = monitorValue.getReportedPath();
    const errorMessage: string = "Reported path should be updated";
    this.assertEquality(actualReportedPath, expectedPath, errorMessage);
  }

  private verifyOriginalPathUnchanged(
    monitorValue: MonitorValueV2<number>,
    expectedPath: string
  ): void {
    const actualPath: string = monitorValue.path;
    const errorMessage: string = "Original path should remain unchanged";
    this.assertEquality(actualPath, expectedPath, errorMessage);
  }

  public testMonitorValueMultipleUpdates(): void {
    const path: string = this.createCounterPath();
    const monitorValue: MonitorValueV2<number> = this.createNumberMonitorValue(path);

    this.performMultipleUpdatesTest(monitorValue);
  }

  private createCounterPath(): string {
    const path: string = "counter";
    return path;
  }

  private performMultipleUpdatesTest(monitorValue: MonitorValueV2<number>): void {
    this.performFirstUpdate(monitorValue);
    this.performSecondUpdate(monitorValue);
    this.performThirdUpdateWithSameValue(monitorValue);
  }

  private performFirstUpdate(monitorValue: MonitorValueV2<number>): void {
    const isInitialSet: boolean = true;
    const firstValue: number = 1;
    this.setValueOnMonitor(monitorValue, isInitialSet, firstValue);
    this.resetMonitorValue(monitorValue);
  }

  private performSecondUpdate(monitorValue: MonitorValueV2<number>): void {
    const isInitialSet: boolean = false;
    const secondValue: number = 2;
    this.setValueOnMonitor(monitorValue, isInitialSet, secondValue);

    this.verifyDirtyAfterSecondUpdate(monitorValue);
    this.resetMonitorValue(monitorValue);
  }

  private verifyDirtyAfterSecondUpdate(monitorValue: MonitorValueV2<number>): void {
    const isDirty: boolean = this.checkIfMonitorIsDirty(monitorValue);
    const expectedDirtyState: boolean = true;
    const errorMessage: string = "Should be dirty after second setValue";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  private performThirdUpdateWithSameValue(monitorValue: MonitorValueV2<number>): void {
    const isInitialSet: boolean = false;
    const sameValue: number = 2;
    this.setValueOnMonitor(monitorValue, isInitialSet, sameValue);

    this.verifyNotDirtyWhenValueUnchanged(monitorValue);
  }

  private verifyNotDirtyWhenValueUnchanged(monitorValue: MonitorValueV2<number>): void {
    const isDirty: boolean = this.checkIfMonitorIsDirty(monitorValue);
    const expectedDirtyState: boolean = false;
    const errorMessage: string = "Should not be dirty when value unchanged";
    this.assertEquality(isDirty, expectedDirtyState, errorMessage);
  }

  public testMonitorValuePropsArray(): void {
    const path: string = this.createMultiSegmentPath();
    const monitorValue: MonitorValueV2<string> = this.createStringMonitorValue(path);

    this.verifyPropsIsArray(monitorValue);
    this.verifyPropsArrayLength(monitorValue);
  }

  private createMultiSegmentPath(): string {
    const segment1: string = "a";
    const segment2: string = "b";
    const segment3: string = "c";
    const segment4: string = "d";
    const separator: string = ".";

    const path: string = this.buildPathFromFourSegments(
      segment1,
      segment2,
      segment3,
      segment4,
      separator
    );

    return path;
  }

  private buildPathFromFourSegments(
    seg1: string,
    seg2: string,
    seg3: string,
    seg4: string,
    separator: string
  ): string {
    const part1: string = seg1 + separator + seg2;
    const part2: string = part1 + separator + seg3;
    const fullPath: string = part2 + separator + seg4;
    return fullPath;
  }

  private verifyPropsIsArray(monitorValue: MonitorValueV2<string>): void {
    const propsArray: string[] = this.getPropsFromMonitor(monitorValue);
    const isArray: boolean = Array.isArray(propsArray);
    const expectedResult: boolean = true;
    const errorMessage: string = "Props should be an array";
    this.assertEquality(isArray, expectedResult, errorMessage);
  }

  private getPropsFromMonitor(monitorValue: MonitorValueV2<string>): string[] {
    const props: string[] = monitorValue.props;
    return props;
  }

  private verifyPropsArrayLength(monitorValue: MonitorValueV2<string>): void {
    const propsArray: string[] = this.getPropsFromMonitor(monitorValue);
    const actualLength: number = this.getArrayLength(propsArray);
    const expectedLength: number = 4;
    const errorMessage: string = "Props array should not be empty";
    this.assertEquality(actualLength, expectedLength, errorMessage);
  }

  private getArrayLength<T>(array: T[]): number {
    const length: number = array.length;
    return length;
  }
}

/**
 * Test suite for SyncMonitor functionality in MonitorV2
 * This class contains comprehensive tests for synchronous monitoring capabilities
 * including wildcard path handling, LSV (Last Sure Value) linking, and watch ID management
 */
export class SyncMonitorTestsV2 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagementTest: ${str}`)
    this.idString = str;
  }

  /**
   * Lifecycle hook: Executed before any tests begin
   * Used for test suite initialization
   */
  public beforeAll(): void {
    // Initialization logic can be added here
  }

  /**
   * Lifecycle hook: Executed before every individual test
   * Used for per-test setup
   */
  public beforeEach(): void {
    // Per-test setup logic can be added here
  }

  /**
   * Lifecycle hook: Executed after all tests complete
   * Used for test suite cleanup
   */
  public afterAll(): void {
    // Cleanup logic can be added here
  }

  /**
   * Lifecycle hook: Executed after every individual test
   * Used for per-test teardown
   */
  public afterEach(): void {
    // Per-test teardown logic can be added here
  }

  /**
   * Returns the unique identifier for this test suite
   */
  public getId(): string {
    return this.idString;
  }

  //
  // MonitorV2 test cases for SyncMonitor
  //

  /**
   * Test: Basic SyncMonitor Creation
   *
   * Verifies that a SyncMonitor can be instantiated correctly with multiple paths.
   * Checks that:
   * - The correct number of paths are added to the monitor
   * - Watch API IDs are incremented properly
   * - The monitor correctly identifies itself as a SyncMonitor decorator
   */
  public testBasicSyncMonitorCreation(): void {
    // Create test instance
    let testClass = new TestClass();

    // Capture starting watch ID
    const watchIdBegin = MonitorV2.nextSyncWatchApiId_;

    // Create monitor with multiple paths including duplicates
    let monitor = new MonitorV2(
      testClass,
      'testVar1 testVar2 testVar3 testVar3.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Verify path count (4 unique paths + 1 LSV)
    eq(
      monitor.values_.size,
      5,
      "added 4 paths + 1 LSV value"
    );

    // Verify watch ID incremented correctly (5 values + 1 monitor)
    eq(
      MonitorV2.nextSyncWatchApiId_ - watchIdBegin,
      6,
      "watch id increased by six, 5 values + Monitor"
    );

    // Verify decorator type identification
    eq(
      monitor.isSyncDecorator(),
      true,
      "check for SyncMonitor true"
    );

    eq(
      monitor.isMonitorDecorator(),
      false,
      "check for Monitor false"
    );
  }

  /**
   * Test: SyncMonitor Wildcard Path Linking
   *
   * Validates the bidirectional linking between wildcard paths and their
   * corresponding Last Sure Value (LSV) paths. This ensures that:
   * - Wildcard paths are created correctly
   * - LSV paths are automatically generated
   * - Proper linking exists between wildcard and LSV paths
   */
  public testSyncMonitorWildcardPathLinking(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with nested wildcard path
    let monitor = new MonitorV2(
      testClass,
      'obj.nested.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Retrieve wildcard and LSV paths
    const wildcardPath = monitor.values_.get('obj.nested.*');
    const lsvPath = monitor.values_.get(
      MonitorV2.LSV_PREFIX + 'obj.nested'
    );

    // Verify both paths exist
    eq(
      wildcardPath !== undefined,
      true,
      "wildcard path should exist"
    );

    eq(
      lsvPath !== undefined,
      true,
      "LSV path should exist"
    );

    // Verify bidirectional linking
    eq(
      wildcardPath.getLastSureValuePath(),
      lsvPath,
      "wildcard should link to LSV"
    );

    eq(
      lsvPath.getWildcardPath(),
      wildcardPath,
      "LSV should link to wildcard"
    );
  }

  /**
   * Test: SyncMonitor Reported Path Behavior
   *
   * Ensures that LSV paths correctly report their associated wildcard path
   * while maintaining their actual path without the wildcard suffix.
   * This is important for proper change notification and path resolution.
   */
  public testSyncMonitorReportedPath(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with data items wildcard
    let monitor = new MonitorV2(
      testClass,
      'data.items.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Retrieve LSV path
    const lsvPath = monitor.values_.get(
      MonitorV2.LSV_PREFIX + 'data.items'
    );

    // Verify reported path includes wildcard
    eq(
      lsvPath.getReportedPath(),
      'data.items.*',
      "LSV reported path should be wildcard path"
    );

    // Verify actual path excludes wildcard
    eq(
      lsvPath.path,
      'data.items',
      "LSV actual path should be without wildcard"
    );
  }

  /**
   * Test: SyncMonitor Multiple Wildcard Paths
   *
   * Validates that multiple wildcard paths can be monitored simultaneously.
   * Checks that:
   * - Multiple wildcard paths are created correctly
   * - Each wildcard has its corresponding LSV path
   * - All paths are properly registered in the monitor
   */
  public testSyncMonitorMultipleWildcardPaths(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with two wildcard paths
    let monitor = new MonitorV2(
      testClass,
      'obj1.* obj2.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Verify total path count
    eq(
      monitor.values_.size,
      4,
      "should have 2 wildcard paths + 2 LSV paths"
    );

    // Verify first wildcard path
    eq(
      monitor.values_.has('obj1.*'),
      true,
      "first wildcard path exists"
    );

    // Verify second wildcard path
    eq(
      monitor.values_.has('obj2.*'),
      true,
      "second wildcard path exists"
    );

    // Verify first LSV path
    eq(
      monitor.values_.has(MonitorV2.LSV_PREFIX + 'obj1'),
      true,
      "first LSV path exists"
    );

    // Verify second LSV path
    eq(
      monitor.values_.has(MonitorV2.LSV_PREFIX + 'obj2'),
      true,
      "second LSV path exists"
    );
  }

  /**
   * Test: SyncMonitor Dynamic Path Addition with Wildcard
   *
   * Tests the ability to add wildcard paths dynamically after monitor creation.
   * Verifies:
   * - Paths can be added post-initialization
   * - Both wildcard and LSV paths are created
   * - Watch IDs are properly incremented for new paths
   */
  public testSyncMonitorAddPathWithWildcard(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create empty monitor
    let monitor = new MonitorV2(
      testClass,
      '',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Capture watch ID before adding path
    const watchIdBefore = MonitorV2.nextSyncWatchApiId_;

    // Dynamically add wildcard path
    const result = monitor.addPath('config.settings.*');

    // Verify path was added successfully
    eq(
      result !== undefined,
      true,
      "addPath should return MonitorValueV2"
    );

    // Verify both wildcard and LSV were added
    eq(
      monitor.values_.size,
      3,
      "should add wildcard path and LSV path"
    );

    // Verify watch ID incremented for both paths
    eq(
      MonitorV2.nextSyncWatchApiId_ - watchIdBefore,
      2,
      "should increment watch ID twice"
    );
  }

  /**
   * Test: SyncMonitor Type Identification
   *
   * Validates that a SyncMonitor correctly identifies itself as a sync monitor
   * and returns the appropriate decorator name for debugging and introspection.
   */
  public testSyncMonitorIsSync(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create sync monitor
    let monitor = new MonitorV2(
      testClass,
      'var1',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Verify sync type
    eq(
      monitor.isSync(),
      true,
      "monitor should be sync"
    );

    // Verify decorator name
    eq(
      monitor.getDecoratorName(),
      '@SyncMonitor',
      "decorator name should be @SyncMonitor"
    );
  }

  /**
   * Test: SyncMonitor Path Removal
   *
   * Tests the ability to remove paths from an active monitor.
   * Ensures:
   * - Paths can be removed successfully
   * - The values map size decreases appropriately
   * - Removed paths are no longer accessible
   */
  public testSyncMonitorRemovePath(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with multiple paths
    let monitor = new MonitorV2(
      testClass,
      'path1 path2.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Capture initial size
    const initialSize = monitor.values_.size;

    // Remove first path
    const removed = monitor.removePath('path1');

    // Verify removal was successful
    eq(
      removed,
      true,
      "should successfully remove path"
    );

    // Verify size decreased
    eq(
      monitor.values_.size,
      initialSize - 1,
      "size should decrease by one"
    );

    // Verify path no longer exists
    eq(
      monitor.values_.has('path1'),
      false,
      "path1 should not exist"
    );
  }

  /**
   * Test: SyncMonitor Get Values Map
   *
   * Validates the getValues() method returns the correct data structure
   * containing all monitored paths including wildcards and LSV paths.
   */
  public testSyncMonitorGetValues(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with mixed paths
    let monitor = new MonitorV2(
      testClass,
      'a b.* c',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Retrieve values map
    const values = monitor.getValues();

    // Verify return type
    eq(
      values instanceof Map,
      true,
      "getValues should return Map"
    );

    // Verify size (3 paths + 1 LSV)
    eq(
      values.size,
      4,
      "should have 3 for paths + 1 LSV path"
    );

    // Verify specific paths exist
    eq(
      values.has('a'),
      true,
      "should contain path a"
    );

    eq(
      values.has('b.*'),
      true,
      "should contain wildcard path"
    );
  }

  /**
   * Test: SyncMonitor Invalid Path Validation
   *
   * Ensures that SyncMonitor properly validates wildcard placement.
   * Only wildcards at the end of paths are valid for SyncMonitor.
   * Wildcards in the middle of paths should be rejected.
   */
  public testSyncMonitorInvalidPathValidation(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create empty monitor
    let monitor = new MonitorV2(
      testClass,
      '',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Attempt to add valid wildcard ending
    const result1 = monitor.addPath('valid.path.*');

    // Attempt to add invalid wildcard in middle
    const result2 = monitor.addPath('invalid.*.middle');

    // Verify valid path succeeds
    eq(
      result1 !== undefined,
      true,
      "valid wildcard ending should succeed"
    );

    // Verify invalid path fails
    eq(
      result2,
      undefined,
      "wildcard in middle should fail for SyncMonitor"
    );
  }

  /**
   * Test: SyncMonitor Watch ID Range Validation
   *
   * Verifies that watch IDs assigned to SyncMonitor instances fall within
   * the designated range for synchronous monitors. This ensures proper
   * ID allocation and prevents conflicts with async monitor IDs.
   */
  public testSyncMonitorWatchIdRange(): void {
    // Create test instance
    let testClass = new TestClass();

    // Capture watch ID before creation
    const watchIdBefore = MonitorV2.nextSyncWatchApiId_;

    // Create monitor with wildcard path
    let monitor = new MonitorV2(
      testClass,
      'test.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Get assigned watch ID
    const watchId = monitor.getWatchId();

    // Verify ID is in sync range
    eq(
      watchId >= MonitorV2.MIN_SYNC_WATCH_FROM_API_ID,
      true,
      "watch ID should be in sync range"
    );

    // Verify ID incremented
    eq(
      watchId > watchIdBefore,
      true,
      "watch ID should increment"
    );

    // Verify ID is within expected bounds
    eq(
      monitor.getWatchId() < MonitorV2.MIN_WATCH_FROM_API_ID + 0x1000000000000,
      true,
      "watch ID in expected range"
    );
  }

  /**
   * Test: SyncMonitor Callback Invocation
   *
   * Verifies that the monitor's callback function is properly stored
   * and can be retrieved. Tests callback handling mechanism for
   * change notifications in synchronous monitoring scenarios.
   */
  public testSyncMonitorCallbackHandling(): void {
    // Create test instance
    let testClass = new TestClass();

    // Flag to track callback invocation
    let callbackInvoked = false;

    // Create monitor with callback
    let monitor = new MonitorV2(
      testClass,
      'property1',
      (m: IMonitor) => {
        callbackInvoked = true;
      },
      true,
      true
    );

    // Verify callback exists
    const callback = monitor.monitorFunction;
    eq(
      callback !== undefined,
      true,
      "callback should be defined"
    );

    // Verify callback is a function
    eq(
      typeof callback === 'function',
      true,
      "callback should be a function"
    );
  }

  /**
   * Test: SyncMonitor Empty Path String Handling
   *
   * Validates that a SyncMonitor can be created with an empty path string
   * and that paths can be added dynamically afterward. This tests the
   * flexibility of monitor initialization patterns.
   */
  public testSyncMonitorEmptyPathInitialization(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with empty path string
    let monitor = new MonitorV2(
      testClass,
      '',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Verify initial state has no paths
    eq(
      monitor.values_.size,
      1,
      "empty monitor should have only the monitor itself"
    );

    // Add first path
    const path1 = monitor.addPath('first.path');
    eq(
      path1 !== undefined,
      true,
      "should successfully add first path"
    );

    // Add second path with wildcard
    const path2 = monitor.addPath('second.*');
    eq(
      path2 !== undefined,
      true,
      "should successfully add second path with wildcard"
    );

    // Verify both paths and LSV exist
    eq(
      monitor.values_.size,
      4,
      "should have 2 paths + 1 LSV + monitor"
    );
  }

  /**
   * Test: SyncMonitor Complex Nested Wildcard Paths
   *
   * Tests monitoring of deeply nested object structures with wildcards.
   * Ensures that complex path hierarchies are handled correctly and
   * that LSV paths are generated at the appropriate level.
   */
  public testSyncMonitorComplexNestedWildcards(): void {
    // Create test instance
    let testClass = new TestClass();

    // Create monitor with deeply nested wildcard
    let monitor = new MonitorV2(
      testClass,
      'root.level1.level2.level3.*',
      (m: IMonitor) => {
        // Callback handler
      },
      true,
      true
    );

    // Retrieve wildcard path
    const wildcardPath = monitor.values_.get(
      'root.level1.level2.level3.*'
    );

    // Retrieve corresponding LSV path
    const lsvPath = monitor.values_.get(
      MonitorV2.LSV_PREFIX + 'root.level1.level2.level3'
    );

    // Verify wildcard path exists
    eq(
      wildcardPath !== undefined,
      true,
      "deeply nested wildcard path should exist"
    );

    // Verify LSV path exists
    eq(
      lsvPath !== undefined,
      true,
      "deeply nested LSV path should exist"
    );

    // Verify linking is correct
    eq(
      wildcardPath.getLastSureValuePath(),
      lsvPath,
      "wildcard should link to correct LSV"
    );

    // Verify path structure
    eq(
      lsvPath.path,
      'root.level1.level2.level3',
      "LSV path should match expected structure"
    );
  }
}
