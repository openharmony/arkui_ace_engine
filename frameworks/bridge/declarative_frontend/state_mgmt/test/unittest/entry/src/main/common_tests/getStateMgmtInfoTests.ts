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
declare function getStateMgmtInfo(nodeIds: Array<number>, propertyName: string, jsonPath: string): Array<string | undefined>;

interface IView {
}

declare abstract class ViewBuildNodeBase {
  childrenWeakrefMap_: Map<number, WeakRef<IView>>;
}

declare class PUV2ViewBase extends ViewBuildNodeBase {
    id__(): number;
    __isEntry__Internal(): boolean;
}


export class getStateMgmtInfoTests implements ITestFile {

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
   * Test get path from Entry Component
   */
  public testEntry(): void {
    eq((this as Object as PUV2ViewBase).__isEntry__Internal(), true);
    const id = [(this as Object as PUV2ViewBase).id__() - 1];
    const result = getStateMgmtInfo(id, 'val', 'groupId');
    const expected = ['7578'];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get path with nested object value
   */
  public testDeepPath(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const result = getStateMgmtInfo(id, 'nestedVal', '/a/b/groupId');
    const expected = ['888'];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get path with regular variable
   */
  public testRegularVar(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const result = getStateMgmtInfo(id, 'regularVar', '/groupId');
    const expected = [undefined];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get path with wrong PropertyName
   */
  public testWrongPropertyName(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const result = getStateMgmtInfo(id, 'stateVar', '/groupId');
    const expected = [undefined];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get wrong path
   */
  public testWrongPath(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const result = getStateMgmtInfo(id, 'nestedVal', '/groupId');
    const expected = [undefined];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get paths with multiple Component Ids
   */
  public testMultipleIds(): void {
    const childrenMap = (this as Object as PUV2ViewBase).childrenWeakrefMap_;
    const keys = Array.from(childrenMap.keys());
    const result = getStateMgmtInfo(keys, 'childVar', '/groupId');
    const expected = [undefined, '7578', undefined, '123'];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get path with root
   */
  public testRoot(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const result = getStateMgmtInfo(id, 'rootVal', '/');
    const expected = ['321'];
    eq(JSON.stringify(result), JSON.stringify(expected));
  }

  /**
   * Test get path with number/boolean/null/undefined/circular object
   */
  public testNonString(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const numberResult = getStateMgmtInfo(id, 'val', '/comment_group_id');
    const numberExpected = ['7577'];
    eq(JSON.stringify(numberResult), JSON.stringify(numberExpected));
    const booleanResult = getStateMgmtInfo(id, 'val', '/isCommonRequest');
    const booleanExpected = ['true'];
    eq(JSON.stringify(booleanResult), JSON.stringify(booleanExpected));
    const nullResult = getStateMgmtInfo(id, 'val', '/userId');
    const nullExpected = ['null'];
    eq(JSON.stringify(nullResult), JSON.stringify(nullExpected));
    const undefinedResult = getStateMgmtInfo(id, 'undefinedVal', '/');
    const undefinedExpected = [undefined];
    eq(JSON.stringify(undefinedResult), JSON.stringify(undefinedExpected));
    const circularResult = getStateMgmtInfo(id, 'circularVal', '/');
    const circularExpected = [undefined];
    eq(JSON.stringify(circularResult), JSON.stringify(circularExpected));
  }

  /**
   * Test get path with array
   */
  public testArray(): void {
    const id = [(this as Object as PUV2ViewBase).id__()];
    const result = getStateMgmtInfo(id, 'arrayVal', '/a/1/c');
    const expected = ['4'];
    eq(JSON.stringify(result), JSON.stringify(expected));
    const undefinedResult = getStateMgmtInfo(id, 'arrayVal', '/a/-1/c');
    const undefinedExpected = [undefined];
    eq(JSON.stringify(undefinedResult), JSON.stringify(undefinedExpected));
    const undefinedResult1 = getStateMgmtInfo(id, 'arrayVal', '/a/2/b');
    eq(JSON.stringify(undefinedResult1), JSON.stringify(undefinedExpected));
    const objectResult = getStateMgmtInfo(id, 'objectVal', '/a/1/c');
    const objectExpected = ['2'];
    eq(JSON.stringify(objectResult), JSON.stringify(objectExpected));
  }
}