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

declare class MonitorValueV2<T> {
  before?: T;
  now?: T;
  path: string;
  props: string[];
  private dirty;
  constructor(path: string);
  setValue(isInit: boolean, newValue: T): boolean;
  reset(): void;
  isDirty(): boolean;
}

declare class MonitorV2 {
  static readonly WATCH_PREFIX;
  static readonly WATCH_INSTANCE_PREFIX;
  static readonly MIN_WATCH_ID;
  static nextWatchId_: number;

  // Changed to public in this file to enable UT
  //private values_;
  public values_;

  private target_;
  private monitorFunction;
  private watchId_;
  constructor(target: object, pathsString: string, func: (m: IMonitor) => void, isDecorator: boolean, isSync: boolean)
  getTarget(): Object;
  getMonitorFuncName(): string;
  /**
   Return array of those monitored paths
   that changed since previous invocation
   */
  get dirty(): Array<string>;
  /**
   * return IMonitorValue for given path
   * or if no path is specified any dirty (changed) monitor value
   */
  value<T>(path?: String): IMonitorValue<T>;
  InitRun(): MonitorV2;
  notifyChange(): void;
  notifyChangeOnReuse(): void;
  private resetMonitor;
  private bindRun;
  private analysisProp;
  static clearWatchesFromTarget(target: Object): void;
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