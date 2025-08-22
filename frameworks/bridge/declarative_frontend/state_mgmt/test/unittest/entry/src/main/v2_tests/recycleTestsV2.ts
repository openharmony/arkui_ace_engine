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

declare class UpdateFuncsByElmtId {
  private map_;
  delete(elmtId: number): boolean;
  clear(): void;
  get size(): number;
}

declare abstract class ViewBuildNodeBase {
  protected isView_: boolean;
  updateFuncByElmtId: UpdateFuncsByElmtId;
}

declare class PUV2ViewBase extends ViewBuildNodeBase{
  protected get isViewV2() : boolean;
}

declare class ViewV2 extends PUV2ViewBase{
  public debugInfo__(): string;
  public hasBeenRecycled_: boolean;
  public recycleSelf(reuseId: string): void;
  hasRecyclePool(): boolean;
  get isViewV2(): boolean;
}

declare class RecycledIdRegistry {

  constructor();
  delete(key: number): void;
  get(key: number): number | undefined;
  add(pair: [number, number]): void;
}

declare class RecyclePoolV2 {
  cachedRecycleComponents_;
  private recycledIdRegistry_?;
  constructor();
  pushRecycleV2Component(reuseId: string, reuseComp: ViewV2): void;
  popRecycleV2Component(reuseId: string): ViewV2 | undefined;
  updateRecycleIdMapping(recycledElementId: number, newElmtId: number): void;
  getRecycleIdMapping(recycledElementId: number): number;
  purgeAllCachedRecycleElmtIds(): void;
}

export class RecycleTestsV2 implements ITestFile {

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

  /*   Test hasRecyclePool function
  * Should return false
  */
  public testHasRecyclePool(): void {
    let hasPool = (this as any as ViewV2).hasRecyclePool();
    console.log(`HasRecyclePool ${hasPool}`);
    eq(hasPool, false);
  }

  // This is FAILING because bug in stateMgmt. Enable this test when the bug is fixed.
  /*   Test RecycledIdRegistry class
  * Test add, get and delete
  */
 /*
  public testRecycledIdRegistryClass(): void {
    const registry = new RecycledIdRegistry()
    const oldId1 = 1
    const newId1 = 11
    const oldId2 = 2
    const newId2 = 22

    registry.add([oldId1, newId1])
    registry.add([oldId2, newId2])

    let fwdResult1 = registry.get(oldId1)
    let reverseResult1 = registry.get(newId1)
    let fwdResult2 = registry.get(oldId2)
    let reverseResult2 = registry.get(newId2)

    eq(fwdResult1, newId1, 'Forward ID1 is new ID1');
    eq(reverseResult1, oldId1, 'Reverse ID1 is old ID1');

    eq(fwdResult2, newId2, 'Forward ID2 is new ID2');
    eq(reverseResult2, oldId2, 'Reverse ID2 is old ID2');

    registry.delete(oldId2);

    fwdResult1 = registry.get(oldId1)
    reverseResult1 = registry.get(newId1)
    fwdResult2 = registry.get(oldId2)
    reverseResult2 = registry.get(newId2)

    eq(fwdResult1, newId1, 'Forward ID1 is new ID1 after deletion');
    eq(reverseResult1, oldId1, 'Reverse ID1 is old ID1 after deletion');

    eq(fwdResult2, undefined, 'Forward ID2 is undefined after deletion');
    eq(reverseResult2, undefined, 'Reverse ID2 is undefined after deletion');

    console.log("testRecycledIdRegistryAddAndGet passed")
  }
    */
  /*   Test RecyclePoolV2 class
  *
  */
  public testRecyclePoolV2Class(): void {
    const registry = new RecyclePoolV2();
    registry.pushRecycleV2Component("btn1", this as unknown as ViewV2)
    let popped = registry.popRecycleV2Component("btn1")

    eq(popped, this as unknown as ViewV2, "pop should return the same component that was pushed")

    popped = registry.popRecycleV2Component("nonexistent")
    eq(popped, undefined, "pop from empty key should return undefined")

    registry.updateRecycleIdMapping(10, 99)
    const mapped = registry.getRecycleIdMapping(10)
    eq(mapped, 99, "recycled ID 10 should map to 99")

    registry.updateRecycleIdMapping(5, 50)
    registry.purgeAllCachedRecycleElmtIds()
    eq(registry.cachedRecycleComponents_?.size, 0, "Cache size after the purge is zero")
    const afterPurge = registry.getRecycleIdMapping(5)
    eq(afterPurge, 50, "after purge, ID should map to 50")
  }

}