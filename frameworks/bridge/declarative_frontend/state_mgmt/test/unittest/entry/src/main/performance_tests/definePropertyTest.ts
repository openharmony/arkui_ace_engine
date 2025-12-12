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
import { lt, ITestFile } from '../lib/testRunner'

declare class ArkTools {
  static timeInUs(): number;
}
const runTimes = 10000;
class TestObj {

}
export class DefinePropertyTest implements ITestFile {
  private idString: string = '';

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
  public testDefineProperty(): void {
    const obj = Object.getPrototypeOf(new TestObj);
    let t1: number = ArkTools.timeInUs();
    for (let i = 0; i < runTimes; i++) {
        i.toString();
    }
    let t2: number = ArkTools.timeInUs();
    for (let i = 0; i < runTimes; i++) {
        Reflect.defineProperty(obj, i.toString(), { get() {}, set(val) {}, enumerable: true });
    }
    let t3: number = ArkTools.timeInUs();
    const result = ((t3 - t2) - (t2 - t1)) / runTimes;
    console.log('PerformanceTest case: defineProperty', result);
    lt(result, 10); // defineProperty
  }

}