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

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class Utils {
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
  static currentAppApiVersion: number;
}

declare class PUV2ViewBase {
  protected get isViewV2(): boolean;
}

declare class ViewPU extends PUV2ViewBase{
  public debugInfoStateVars(): string;
  declareWatch(propStr: string, callback: (propName: string) => void): void;
  watchedProps: Map<string, (propName: string) => void>;
  get localStorage_(): LocalStorage;
  set localStorage_(instance: LocalStorage);
  get isViewV2(): boolean;

  // Add more

}

export class CommonTestsV2 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll(): void {}

  // Executed before every invidual tests. Can be empty
  public beforeEach(): void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}

  public getId(): string {
    return this.idString;
  }

  /// -- Test cases

  /* Verify that Utils API version check is working
  * Calls getApiVersion and isApiVersionEQAbove
  */
  public verifyAPIVersion(): void {
    const atLeast: number = 14;
    const apiVer: number = Utils.getApiVersion();
    console.log(`API Ver: ${apiVer}`)
    gt(apiVer, 0, 'Api version exists');
    eq(Utils.isApiVersionEQAbove(atLeast), true, 'Api version big enough');
  }

  /* Verify that detections of V1 vs. V2 works
  * Calls: isViewV2 - expects false;
  */
  public verifyThisIsV1Object(): void {
    const bIsV2: boolean = (this as any as ViewPU)?.isViewV2;
    eq(bIsV2, false);
  }
}