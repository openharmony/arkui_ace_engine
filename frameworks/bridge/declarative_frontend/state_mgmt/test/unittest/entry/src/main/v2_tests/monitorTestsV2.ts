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
}

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

export class SyncMonitorTestsV2 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagementTest: ${str}`)
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

  //
  // MonitorPathHelper tests
  //
  public testPathHelperWildcardEnding() {
    eq(MonitorPathHelper.hasWildcardEnding('a.b.*'), true, "Check for wildcard ending");
    eq(MonitorPathHelper.hasWildcardEnding('a.b.c'), false, "No wildcard ending");
    eq(MonitorPathHelper.hasWildcardEnding('*'), false, "Single wildcard is not ending");
    eq(MonitorPathHelper.hasWildcardEnding(''), false, "Empty string has no wildcard ending");
  }

  public testPathHelperValidForMonitor() {
    eq(MonitorPathHelper.isValidForMonitor('a.b'), true, "Check for wildcard ending");
    eq(MonitorPathHelper.isValidForMonitor('a.b.*'), false, "Check for wildcard ending");
    eq(MonitorPathHelper.isValidForMonitor('*'), false, "Single wildcard not valid");
    eq(MonitorPathHelper.isValidForMonitor('a.*.b'), false, "Wildcard in middle not valid");
    eq(MonitorPathHelper.isValidForMonitor(''), true, "Empty path is valid");
  }

  public testPathHelperIsWildcardSubPath() {
    eq(MonitorPathHelper.isWildcardSubPath('*'), true, "Single asterisk is wildcard subpath");
    eq(MonitorPathHelper.isWildcardSubPath('a.*'), false, "Path with wildcard ending is not wildcard subpath");
    eq(MonitorPathHelper.isWildcardSubPath('a.b.c'), false, "Regular path is not wildcard subpath");
  }

  public testPathHelperPathBeforeWildcard() {
    eq(MonitorPathHelper.pathBeforeWildcard('a.b.c.*'), 'a.b.c', "Extract path before wildcard");
    eq(MonitorPathHelper.pathBeforeWildcard('a.b'), 'a.b', "Path without wildcard returns unchanged");
    eq(MonitorPathHelper.pathBeforeWildcard('x.*'), 'x', "Single segment before wildcard");
    eq(MonitorPathHelper.pathBeforeWildcard('deep.nested.path.*'), 'deep.nested.path', "Deep nested path before wildcard");
  }

  public testPathHelperIsValidForSyncMonitor() {
    eq(MonitorPathHelper.isValidForSyncMonitor('a.b.c'), true, "Path with no wildcards is valid");
    eq(MonitorPathHelper.isValidForSyncMonitor('a.b.*'), true, "Path with ending wildcard is valid");
    eq(MonitorPathHelper.isValidForSyncMonitor('a.*.b'), false, "Wildcard in middle is invalid");
    eq(MonitorPathHelper.isValidForSyncMonitor('*.*'), false, "Multiple wildcards are invalid");
    eq(MonitorPathHelper.isValidForSyncMonitor('*'), false, "Single wildcard with no dots is not valid");
    eq(MonitorPathHelper.isValidForMonitor(''), true, "Empty path is valid");
  }

  public testPathHelperEdgeCases() {
    eq(MonitorPathHelper.hasWildcardEnding('.*'), true, "Just dot and wildcard");
    eq(MonitorPathHelper.pathBeforeWildcard('.*'), '', "Empty path before wildcard");
    eq(MonitorPathHelper.isValidForSyncMonitor(''), true, "Empty string has no wildcards");
  }

  public testPathHelperComplexPaths() {
    eq(MonitorPathHelper.isValidForMonitor('root.module.component.prop'), true, "Deep path without wildcards");
    eq(MonitorPathHelper.isValidForSyncMonitor('root.module.*'), true, "Valid sync monitor with wildcard ending");
    eq(MonitorPathHelper.pathBeforeWildcard('very.long.nested.path.structure.*'), 'very.long.nested.path.structure', "Long path extraction");
  }

  //
  // MonitorValueV2 tests
  //
  public testMonitorValueReturnPath() {
    let monitorValue = new MonitorValueV2<number>('a.b.c.*');
    eq(monitorValue.getReportedPath(), 'a.b.c.*', 'Check for reported path');
    eq(monitorValue.path, 'a.b.c.*', 'Check for path property');
  }

  public testMonitorValueSetValue() {
    let monitorValue = new MonitorValueV2<number>('a.b.c');
    let isDirty = monitorValue.setValue(true, 42);
    eq(isDirty, false, 'Setting initial value should not mark as dirty');
    eq(monitorValue.now, 42, 'Value should be set to 42');
    isDirty = monitorValue.setValue(false, 84);
    eq(monitorValue.isDirty(), true, 'Monitor should be dirty after setValue with new value');
  }

  public testMonitorValueSetNotFound() {
    let monitorValue = new MonitorValueV2<string>('a.b.c');
    let isDirty = monitorValue.setNotFound(true);
    eq(isDirty, false, 'Setting not found with init should not mark as dirty');
    eq(monitorValue.now, undefined, 'Value should be undefined when not found');
  }

  public testMonitorValueReset() {
    let monitorValue = new MonitorValueV2<number>('x.y', 1);
    monitorValue.setValue(false, 100);
    eq(monitorValue.isDirty(), true, 'Should be dirty after setValue');
    monitorValue.reset();
    eq(monitorValue.isDirty(), false, 'Should not be dirty after reset');
  }

  public testMonitorValueBeforeAndNow() {
    let monitorValue = new MonitorValueV2<string>('test.path');
    monitorValue.setValue(true, 'initial');
    monitorValue.reset();
    monitorValue.setValue(false, 'updated');
    eq(monitorValue.before, 'initial', 'Before value should be initial');
    eq(monitorValue.now, 'updated', 'Now value should be updated');
  }

  public testMonitorValueIsWildcard() {
    let wildcardMonitor = new MonitorValueV2<number>('a.b.*');
    let regularMonitor = new MonitorValueV2<number>('a.b.c');
    eq(wildcardMonitor.isWildcard(), true, 'Path ending with .* should be wildcard');
    eq(regularMonitor.isWildcard(), false, 'Regular path should not be wildcard');
  }

  public testMonitorValueWildcardPath() {
    let parentMonitor = new MonitorValueV2<number>('a.b.*');
    let childMonitor = new MonitorValueV2<number>('a.b.c');
    parentMonitor.setWildcardPath(childMonitor);
    eq(parentMonitor.getWildcardPath(), childMonitor, 'Should retrieve the set wildcard path');
  }

  public testMonitorValueLastSureValuePath() {
    let monitor = new MonitorValueV2<string>('a.b.c');
    let lsvMonitor = new MonitorValueV2<string>('a.b');
    monitor.setLastSureValuePath(lsvMonitor);
    eq(monitor.getLastSureValuePath(), lsvMonitor, 'Should retrieve the set LSV path');
  }

  public testMonitorValueSetReportedPath() {
    let monitorValue = new MonitorValueV2<number>('original.path');
    monitorValue.setReportedPath('custom.reported.path');
    eq(monitorValue.getReportedPath(), 'custom.reported.path', 'Reported path should be updated');
    eq(monitorValue.path, 'original.path', 'Original path should remain unchanged');
  }

  public testMonitorValueMultipleUpdates() {
    let monitorValue = new MonitorValueV2<number>('counter');
    monitorValue.setValue(true, 1);
    monitorValue.reset();
    monitorValue.setValue(false, 2);
    eq(monitorValue.isDirty(), true, 'Should be dirty after second setValue');
    monitorValue.reset();
    monitorValue.setValue(false, 2);
    eq(monitorValue.isDirty(), false, 'Should not be dirty when value unchanged');
  }

  public testMonitorValuePropsArray() {
    let monitorValue = new MonitorValueV2<string>('a.b.c.d');
    eq(Array.isArray(monitorValue.props), true, 'Props should be an array');
    eq(monitorValue.props.length, 4, 'Props array should not be empty');
  }

  //
  // MonitorV2 test cases for SyncMonitor
  //
  public testBasicSyncMonitorCreation(): void {
    let testClass = new TestClass();
    const watchIdBegin = MonitorV2.nextSyncWatchApiId_;

    let monitor = new MonitorV2(testClass, 'testVar1 testVar2 testVar3 testVar3.*', (m: IMonitor) => {
    }, true, true);
    eq(monitor.values_.size, 5, "added 4 paths + 1 LSV value");
    eq(MonitorV2.nextSyncWatchApiId_ - watchIdBegin, 6, "watch id increased by six, 5 values + Monitor");
    eq(monitor.isSyncDecorator(), true, "check for SyncMonitor true");
    eq(monitor.isMonitorDecorator(), false, "check for Monitor false");
  }

  public testSyncMonitorWildcardPathLinking(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, 'obj.nested.*', (m: IMonitor) => {
    }, true, true);

    const wildcardPath = monitor.values_.get('obj.nested.*');
    const lsvPath = monitor.values_.get(MonitorV2.LSV_PREFIX + 'obj.nested');

    eq(wildcardPath !== undefined, true, "wildcard path should exist");
    eq(lsvPath !== undefined, true, "LSV path should exist");
    eq(wildcardPath.getLastSureValuePath(), lsvPath, "wildcard should link to LSV");
    eq(lsvPath.getWildcardPath(), wildcardPath, "LSV should link to wildcard");
  }

  public testSyncMonitorReportedPath(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, 'data.items.*', (m: IMonitor) => {
    }, true, true);

    const lsvPath = monitor.values_.get(MonitorV2.LSV_PREFIX + 'data.items');
    eq(lsvPath.getReportedPath(), 'data.items.*', "LSV reported path should be wildcard path");
    eq(lsvPath.path, 'data.items', "LSV actual path should be without wildcard");
  }

  public testSyncMonitorMultipleWildcardPaths(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, 'obj1.* obj2.*', (m: IMonitor) => {
    }, true, true);

    eq(monitor.values_.size, 4, "should have 2 wildcard paths + 2 LSV paths");
    eq(monitor.values_.has('obj1.*'), true, "first wildcard path exists");
    eq(monitor.values_.has('obj2.*'), true, "second wildcard path exists");
    eq(monitor.values_.has(MonitorV2.LSV_PREFIX + 'obj1'), true, "first LSV path exists");
    eq(monitor.values_.has(MonitorV2.LSV_PREFIX + 'obj2'), true, "second LSV path exists");
  }

  public testSyncMonitorAddPathWithWildcard(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, '', (m: IMonitor) => {
    }, true, true);

    const watchIdBefore = MonitorV2.nextSyncWatchApiId_;
    const result = monitor.addPath('config.settings.*');

    eq(result !== undefined, true, "addPath should return MonitorValueV2");
    eq(monitor.values_.size, 3, "should add wildcard path and LSV path");
    eq(MonitorV2.nextSyncWatchApiId_ - watchIdBefore, 2, "should increment watch ID twice");
  }

  public testSyncMonitorIsSync(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, 'var1', (m: IMonitor) => {
    }, true, true);

    eq(monitor.isSync(), true, "monitor should be sync");
    eq(monitor.getDecoratorName(), '@SyncMonitor', "decorator name should be @SyncMonitor");
  }

  public testSyncMonitorRemovePath(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, 'path1 path2.*', (m: IMonitor) => {
    }, true, true);

    const initialSize = monitor.values_.size;
    const removed = monitor.removePath('path1');

    eq(removed, true, "should successfully remove path");
    eq(monitor.values_.size, initialSize - 1, "size should decrease by one");
    eq(monitor.values_.has('path1'), false, "path1 should not exist");
  }

  public testSyncMonitorGetValues(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, 'a b.* c', (m: IMonitor) => {
    }, true, true);

    const values = monitor.getValues();
    eq(values instanceof Map, true, "getValues should return Map");
    eq(values.size, 4, "should have 3 for paths + 1 LSV path");
    eq(values.has('a'), true, "should contain path a");
    eq(values.has('b.*'), true, "should contain wildcard path");
  }

  public testSyncMonitorInvalidPathValidation(): void {
    let testClass = new TestClass();
    let monitor = new MonitorV2(testClass, '', (m: IMonitor) => {
    }, true, true);

    const result1 = monitor.addPath('valid.path.*');
    const result2 = monitor.addPath('invalid.*.middle');

    eq(result1 !== undefined, true, "valid wildcard ending should succeed");
    eq(result2, undefined, "wildcard in middle should fail for SyncMonitor");
  }

  public testSyncMonitorWatchIdRange(): void {
    let testClass = new TestClass();
    const watchIdBefore = MonitorV2.nextSyncWatchApiId_;

    let monitor = new MonitorV2(testClass, 'test.*', (m: IMonitor) => {
    }, true, true);

    const watchId = monitor.getWatchId();
    eq(watchId >= MonitorV2.MIN_SYNC_WATCH_FROM_API_ID, true, "watch ID should be in sync range");
    eq(watchId > watchIdBefore, true, "watch ID should increment");
    eq(monitor.getWatchId() < MonitorV2.MIN_WATCH_FROM_API_ID + 0x1000000000000, true, "watch ID in expected range");
  }
}
