+/*
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

declare abstract class ViewBuildNodeBase {
}

declare class PUV2ViewBase extends ViewBuildNodeBase{
}

declare class ViewV2 extends PUV2ViewBase{
  resetConsumer<T>(varName: string, consumerVal: T): void;
  updateParam<Z>(paramVariableName: string, newValue: Z): void;
  resetParam<Z>(paramVariableName: string, newValue: Z): void;
  resetMonitorsOnReuse(): void;
}

declare class UIUtilsImpl {
  private static instance_;
  applySync<T>(task: () => T): T;
  flushUpdates(): void;
  flushUIUpdates(): void;
  static instance(): UIUtilsImpl;
}

export class ResetStateVarsOnReuseTestsV2 implements ITestFile {

  private idString : string = '';

  constructor(str : string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll () : void {}

  // Executed before every invidual tests. Can be empty
  public beforeEach () : void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}


  public getId() : string {
    return this.idString;
  }

  // Test cases start from here. All functions are run automatically except those starting with _
  /**
   * Verify resetConsumer
   */
  testResetConsumer(): void {
    const v2 = (this as Object as ViewV2);
    const varName1 = 'consumerWithAliasWithoutProvider';
    const varName2 = 'consumerWithoutAliasWithoutProvider';
    const varName3 = 'consumerWithAliasWithProvider';
    const varName4 = 'consumerWithoutAliasWithProvider';
    let consumer1: number = v2[varName1];
    let consumer2: number = v2[varName2];
    let consumer3: number = v2[varName3];
    let consumer4: number = v2[varName4];
    const valid1 = consumer1 === 1;
    eq(valid1, true);
    const valid2 = consumer2 === 2;
    eq(valid2, true);
    const valid3 = consumer3 === 100;
    eq(valid3, true);
    const valid4 = consumer4 === 101;
    eq(valid4, true);
    v2[varName1] = 1001;
    v2[varName2] = 1002;
    v2[varName3] = 1003;
    v2[varName4] = 1004;
    v2.resetConsumer(varName1, 1);
    v2.resetConsumer(varName2, 2);
    v2.resetConsumer(varName3, 3);
    v2.resetConsumer(varName4, 4);
    consumer1 = v2[varName1];
    consumer2 = v2[varName2];
    consumer3 = v2[varName3];
    consumer4 = v2[varName4];
    const valid11 = consumer1 === 1;
    eq(valid11, true);
    const valid22 = consumer2 === 2;
    eq(valid22, true);
    const valid33 = consumer3 === 1003;
    eq(valid33, true);
    const valid44 = consumer4 === 1004;
    eq(valid44, true);
  }
  /**
   * Verify resetParam
   */
  testResetParam(): void {
    const v2 = (this as Object as ViewV2);
    const varName1 = 'paramOut';
    const varName2 = 'paramIn';
    const varName3 = 'paramOnceOut';
    const varName4 = 'paramOnceIn';
    let param1: number = v2[varName1];
    let param2: number = v2[varName2];
    let param3: number = v2[varName3];
    let param4: number = v2[varName4];
    const valid1 = param1 === 9;
    eq(valid1, true);
    const valid2 = param2 === 10;
    eq(valid2, true);
    const valid3 = param3 === 9;
    eq(valid3, true);
    const valid4 = param4 === 11;
    eq(valid4, true);
    // varName1 simulate update from parent
    v2.updateParam(varName1, 1001);
    // varName2 has no outer value and no update
    // varName3&4 can be assigned value
    v2[varName3] = 1003;
    v2[varName4] = 1004;
    v2.resetParam(varName1, 100); // simulate outer value change
    v2.resetParam(varName2, 10); // use local init value
    v2.resetParam(varName3, 101); // simulate outer value change
    v2.resetParam(varName4, 11); // use local init value
    param1 = v2[varName1];
    param2 = v2[varName2];
    param3 = v2[varName3];
    param4 = v2[varName4];
    const valid5 = param1 === 100;
    eq(valid5, true);
    const valid6 = param2 === 10;
    eq(valid6, true);
    const valid7 = param3 === 101;
    eq(valid7, true);
    const valid8 = param4 === 11;
    eq(valid8, true);
  }
  /**
   * Verify resetComputed
   */
  testResetComputed(): void {
    const v2 = (this as Object as ViewV2);
    const computedName = 'computed';
    const localName = 'local';
    let computedResult: number = v2[computedName];
    const valid1 = computedResult === 111;
    eq(valid1, true);
    v2[localName] = 112;
    UIUtilsImpl.instance().flushUpdates(); // update computed immediately
    computedResult = v2[computedName];
    const valid2 = computedResult === 112;
    eq(valid2, true);
  }
  /**
   * Verify resetMonitorsOnReuse
   */
  testResetMonitorsOnReuse(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'val';
    const beforeName = 'before';
    const afterName = 'after';
    v2[varName] = 210;
    UIUtilsImpl.instance().flushUpdates();
    const beforeValue0 = v2[beforeName];
    const valid0 = beforeValue0 === 20;
    eq(valid0, true);
    const afterValue0 = v2[afterName];
    const valid1 = afterValue0 === 210;
    eq(valid1, true);
    v2[varName] = 215;
    UIUtilsImpl.instance().flushUpdates();
    const beforeValue1 = v2[beforeName];
    const valid2 = beforeValue1 === 210;
    eq(valid2, true);
    const afterValue1 = v2[afterName];
    const valid3 = afterValue1 === 215;
    eq(valid3, true);
    // simulate value reset on reuse
    v2[varName] = 20;
    // reset before value and now value
    v2.resetMonitorsOnReuse();
    // simulate aboutToReuse change value
    v2[varName] = 22;
    UIUtilsImpl.instance().flushUpdates();
    const beforeValue2 = v2[beforeName];
    const valid4 = beforeValue2 === 20;
    eq(valid4, true);
    const afterValue2 = v2[afterName];
    const valid5 = afterValue2 === 22;
    eq(valid5, true);
  }
}