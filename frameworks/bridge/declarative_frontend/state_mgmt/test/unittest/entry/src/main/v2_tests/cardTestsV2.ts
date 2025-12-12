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
import { eq, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare abstract class ViewBuildNodeBase {
}

declare class PUV2ViewBase extends ViewBuildNodeBase {
  __isV2__Internal(): boolean;
}

declare class ViewV2 extends PUV2ViewBase{
  __setTSCard__Internal(property: string, value: Object): void;
  __checkValidDecorator__Internal(property: string): boolean;
}


export class CardTestsV2 implements ITestFile {

  private idString : string = "";

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
   * Verify whether input instance is a V2 component
   * Call __isV2__Internal;
   */
  public testIsV2Internal(): void {
    const isV2 = (this as Object as ViewV2).__isV2__Internal();
    eq(isV2, true);
    const notV2 = ({} as Object as ViewV2)?.__isV2__Internal?.();
    eq(notV2, undefined);
  }

  /**
   * Verify checkValidDecorator
   * Call __checkValidDecorator__Internal
   * It allows @Local/@Param@Once/@Provider/@Consumer, which return true
   * Otherwise, return false
   */
  public testCheckValidDecorator(): void {
    const v2 = (this as Object as ViewV2);
    const valid0 = v2.__checkValidDecorator__Internal('local');
    eq(valid0, true);
    const valid1 = v2.__checkValidDecorator__Internal('param');
    eq(valid1, false);
    const valid2 = v2.__checkValidDecorator__Internal('paramOnce');
    eq(valid2, true);
    const valid3 = v2.__checkValidDecorator__Internal('event');
    eq(valid3, false);
    const valid4 = v2.__checkValidDecorator__Internal('provider');
    eq(valid4, true);
    const valid5 = v2.__checkValidDecorator__Internal('providerNoAlias');
    eq(valid5, true);
    const valid6 = v2.__checkValidDecorator__Internal('consumer');
    eq(valid6, true);
    const valid7 = v2.__checkValidDecorator__Internal('consumerNoAlias');
    eq(valid7, true);
    const valid8 = v2.__checkValidDecorator__Internal('regular');
    eq(valid8, false);
    const valid9 = v2.__checkValidDecorator__Internal('nonsense');
    eq(valid9, false);
    const valid10 = v2.__checkValidDecorator__Internal('computed');
    eq(valid10, false);
    const valid11 = v2.__checkValidDecorator__Internal('monitor');
    eq(valid11, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Local is allowed to update
   */
  public testSetTSCardInternalForLocal(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'local';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Param is not allowed to set value
   */
  public testSetTSCardInternalForParam(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'param';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, true);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Param @Once is allowed to update
   */
  public testSetTSCardInternalForParamOnce(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'paramOnce';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Event is not allowed to update by form
   */
  public testSetTSCardInternalForEvent(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'event';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, ()=>{});
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, true);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Provider is allowed to update
   */
  public testSetTSCardInternalForProvider(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'provider';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Provider no alias is allowed to update
   */
  public testSetTSCardInternalForProviderNoAlias(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'providerNoAlias';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Consumer is allowed to update
   */
  public testSetTSCardInternalForConsumer(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'consumer';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Consumer no alias is allowed to update
   */
  public testSetTSCardInternalForConsumerNoAlias(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'consumerNoAlias';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * Regular value is not allowed to update by form
   */
  public testSetTSCardInternalForRegular(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'regular';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, true);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * NonSense(means not existed) is not allowed to update by form
   */
  public testSetTSCardInternalForNonSense(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'nonsense';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, false);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const valid2 = nowValue !== undefined;
    eq(valid2, false);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Computed is readonly
   */
  public testSetTSCardInternalForComputed(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'computed';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, true);
  }

  /**
   * Verify SetTSCardInternal
   * Call __setTSCard__Internal
   * @Computed is readonly
   */
  public testSetTSCardInternalForMonitor(): void {
    const v2 = (this as Object as ViewV2);
    const varName = 'monitor';
    const oldValue = v2[varName];
    const valid = oldValue !== undefined;
    eq(valid, true);
    v2.__setTSCard__Internal(varName, 0);
    const nowValue = v2[varName];
    const compare = oldValue === nowValue;
    eq(compare, true);
  }
}