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

import { eq, neq, ITestFile } from '../lib/testRunner'

// function type of partial update function
type UpdateFunc = (elmtId: number, isFirstRender: boolean, param?: Object) => void;

interface UIClassObject {
  prototype: Object;
  pop?: () => void;
  name?: string;
}

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class ArkComponent {
}

declare class UpdateFuncRecord {
  constructor(params: { updateFunc: UpdateFunc, classObject?: UIClassObject, node?: ArkComponent });
  getUpdateFunc(): UpdateFunc | undefined;
  getComponentClass(): UIClassObject | undefined;
  getComponentName(): string;
  getPopFunc(): () => void;
  getNode(): ArkComponent | undefined;
  setNode(node: ArkComponent | undefined): void;
  isPending(): boolean;
  setPending(isPending: boolean): void;
  isChanged(): boolean;
  setIsChanged(isChanged: boolean): void;
}

declare class UpdateFuncsByElmtId {
  delete(elmtId: number): boolean;
  set(elmtId: number, params: UpdateFunc |
    { updateFunc: UpdateFunc, classObject?: UIClassObject, node?: ArkComponent }): void;
  get(elmtId: number): UpdateFuncRecord | undefined;
  has(elmtId: number): boolean;
  keys(): IterableIterator<number>;
  clear(): void;
  get size(): number;
  forEach(callbackfn: (value: UpdateFuncRecord, key: number,
    map: Map<number, UpdateFuncRecord>) => void): void;
  debugInfoRegisteredElmtIds(): string;
  debugInfoElmtId(elmtId: number): string;
}

/** emulates a static JS interface class such as Text or Column */
class TextUIClass implements UIClassObject {
  public static create(label: string): void {
  }

  public static pop(): void {
  }

  prototype: Object = TextUIClass.prototype;

  constructor() {
  }
}

/**
 * UpdateFuncsByElmtId / UpdateFuncRecord Unit Tests
 *
 * This test suite validates UpdateFuncsByElmtId functionality:
 * - set / get / has / delete / size / keys / forEach / clear
 * - set with full params object vs. bare update function
 * - UpdateFuncRecord accessors (updateFunc, classObject, node, name, pop)
 * - UpdateFuncRecord pending / changed flags
 * - debugInfoRegisteredElmtIds / debugInfoElmtId output
 */
export class UpdateFuncsByElmtIdTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating UpdateFuncsByElmtIdTestsV2: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('UpdateFuncsByElmtIdTestsV2: Setting up test suite');
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
    console.log('UpdateFuncsByElmtIdTestsV2: Tearing down test suite');
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // helper: a no-op update function
  private _makeUpdateFunc(): UpdateFunc {
    return (elmtId: number, isFirstRender: boolean, param?: Object): void => {
    };
  }

  // helper: class object with name 'Text' and a pop function
  private _makeTextClassObject(): UIClassObject {
    const classObject: UIClassObject = {
      prototype: {},
      name: 'Text',
      pop: (): void => {
      }
    };
    return classObject;
  }

  // =========================================================================
  // SECTION 1: set / get / has tests
  // =========================================================================

  public testSetWithParamsObjectAndGetValue(): void {
    const map = new UpdateFuncsByElmtId();
    const updateFunc = this._makeUpdateFunc();
    const classObject = this._makeTextClassObject();

    map.set(1, { updateFunc: updateFunc, classObject: classObject });

    eq(map.has(1), true, 'elmtId must be registered after set()');
    const record = map.get(1);
    neq(record, undefined, 'get() must return the UpdateFuncRecord');
    eq(record!.getUpdateFunc(), updateFunc, 'record must hold the given update function');
    eq(record!.getComponentClass(), classObject, 'record must hold the given class object');
  }

  public testSetWithBareUpdateFunction(): void {
    const map = new UpdateFuncsByElmtId();
    const updateFunc = this._makeUpdateFunc();

    map.set(2, updateFunc);

    const record = map.get(2);
    neq(record, undefined, 'get() must return the UpdateFuncRecord');
    eq(record!.getUpdateFunc(), updateFunc, 'record must hold the given update function');
    eq(record!.getComponentClass(), undefined,
      'no class object was given, must be undefined');
  }

  public testSetWithNode(): void {
    const map = new UpdateFuncsByElmtId();
    const node = { nodeId: 42 } as unknown as ArkComponent;

    map.set(3, { updateFunc: this._makeUpdateFunc(), node: node });

    eq(map.get(3)!.getNode(), node, 'record must hold the given node');
  }

  public testSetOverwritesExistingEntry(): void {
    const map = new UpdateFuncsByElmtId();
    const firstFunc = this._makeUpdateFunc();
    const secondFunc = this._makeUpdateFunc();
    map.set(4, { updateFunc: firstFunc });

    map.set(4, { updateFunc: secondFunc });

    eq(map.size, 1, 'overwriting must not add a new entry');
    eq(map.get(4)!.getUpdateFunc(), secondFunc, 'entry must hold the second function');
  }

  public testHasReturnsFalseForUnknownElmtId(): void {
    const map = new UpdateFuncsByElmtId();

    eq(map.has(9999), false, 'has() must return false for unknown elmtId');
  }

  public testGetReturnsUndefinedForUnknownElmtId(): void {
    const map = new UpdateFuncsByElmtId();

    eq(map.get(9999), undefined, 'get() must return undefined for unknown elmtId');
  }

  // =========================================================================
  // SECTION 2: delete / clear / size tests
  // =========================================================================

  public testDeleteRemovesEntry(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(5, { updateFunc: this._makeUpdateFunc() });

    eq(map.delete(5), true, 'delete() must return true for known elmtId');
    eq(map.has(5), false, 'entry must be removed');
    eq(map.size, 0, 'size must be 0 after delete');
  }

  public testDeleteUnknownElmtIdReturnsFalse(): void {
    const map = new UpdateFuncsByElmtId();

    eq(map.delete(9999), false, 'delete() must return false for unknown elmtId');
  }

  public testSizeFollowsSetAndDelete(): void {
    const map = new UpdateFuncsByElmtId();
    eq(map.size, 0, 'new map must be empty');

    map.set(10, { updateFunc: this._makeUpdateFunc() });
    map.set(11, { updateFunc: this._makeUpdateFunc() });
    map.set(12, { updateFunc: this._makeUpdateFunc() });
    eq(map.size, 3, 'three entries must be counted');

    map.delete(11);
    eq(map.size, 2, 'two entries must remain after one delete');
  }

  public testClearRemovesAllEntries(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(20, { updateFunc: this._makeUpdateFunc() });
    map.set(21, { updateFunc: this._makeUpdateFunc() });

    map.clear();

    eq(map.size, 0, 'clear() must remove all entries');
    eq(map.has(20), false, 'entries must be gone');
    eq(map.has(21), false, 'entries must be gone');
  }

  // =========================================================================
  // SECTION 3: keys / forEach tests
  // =========================================================================

  public testKeysReturnsAllRegisteredElmtIds(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(30, { updateFunc: this._makeUpdateFunc() });
    map.set(31, { updateFunc: this._makeUpdateFunc() });
    map.set(32, { updateFunc: this._makeUpdateFunc() });

    const keys = Array.from(map.keys()).sort((a: number, b: number): number => a - b);

    eq(JSON.stringify(keys), JSON.stringify([30, 31, 32]),
      'keys() must return all registered elmtIds');
  }

  public testForEachVisitsAllEntries(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(40, { updateFunc: this._makeUpdateFunc() });
    map.set(41, { updateFunc: this._makeUpdateFunc() });
    const visitedKeys: number[] = [];
    let visitedRecords: number = 0;

    map.forEach((record: UpdateFuncRecord, key: number,
      mapParam: Map<number, UpdateFuncRecord>): void => {
      visitedKeys.push(key);
      if (record) {
        visitedRecords++;
      }
    });

    eq(visitedKeys.length, 2, 'forEach must visit each entry once');
    eq(visitedRecords, 2, 'forEach must pass a record for each entry');
    eq(JSON.stringify(visitedKeys.sort((a: number, b: number): number => a - b)),
      JSON.stringify([40, 41]), 'forEach must pass all keys');
  }

  public testKeysOfEmptyMapIsEmpty(): void {
    const map = new UpdateFuncsByElmtId();

    eq(Array.from(map.keys()).length, 0, 'keys() of empty map must be empty');
  }

  // =========================================================================
  // SECTION 4: UpdateFuncRecord tests
  // =========================================================================

  public testRecordGetComponentNameWithNamedClass(): void {
    const record = new UpdateFuncRecord(
      { updateFunc: this._makeUpdateFunc(), classObject: this._makeTextClassObject() });

    eq(record.getComponentName(), 'Text', 'component name must be read from class object');
  }

  public testRecordGetComponentNameWithoutName(): void {
    const record = new UpdateFuncRecord(
      { updateFunc: this._makeUpdateFunc(), classObject: { prototype: {} } });

    eq(record.getComponentName(), 'unspecified UINode',
      'class object without name must report unspecified UINode');
  }

  public testRecordGetComponentNameWithoutClassObject(): void {
    const record = new UpdateFuncRecord({ updateFunc: this._makeUpdateFunc() });

    eq(record.getComponentName(), 'unspecified UINode',
      'missing class object must report unspecified UINode');
  }

  public testRecordGetPopFuncWithPop(): void {
    let popCalled = false;
    const record = new UpdateFuncRecord({
      updateFunc: this._makeUpdateFunc(),
      classObject: { prototype: {}, pop: (): void => { popCalled = true; } }
    });

    const popFunc = record.getPopFunc();
    neq(popFunc, undefined, 'pop function must be returned');
    popFunc();

    eq(popCalled, true, 'returned pop function must be the given one');
  }

  public testRecordGetPopFuncWithoutPopIsNoOp(): void {
    const record = new UpdateFuncRecord({
      updateFunc: this._makeUpdateFunc(),
      classObject: { prototype: {} }
    });

    record.getPopFunc()();

    // no throw and no crash is the expected behavior for a missing pop function
    eq(record.isPending(), false, 'record must still be usable');
  }

  public testRecordNodeSetAndGet(): void {
    const record = new UpdateFuncRecord({ updateFunc: this._makeUpdateFunc() });
    eq(record.getNode(), undefined, 'node must initially be undefined');

    const node = { nodeId: 77 } as unknown as ArkComponent;
    record.setNode(node);
    eq(record.getNode(), node, 'setNode must store the node');

    record.setNode(undefined);
    eq(record.getNode(), undefined, 'setNode(undefined) must clear the node');
  }

  public testRecordPendingFlagDefaultsFalseAndIsSettable(): void {
    const record = new UpdateFuncRecord({ updateFunc: this._makeUpdateFunc() });

    eq(record.isPending(), false, 'pending must default to false');

    record.setPending(true);
    eq(record.isPending(), true, 'setPending(true) must set the flag');

    record.setPending(false);
    eq(record.isPending(), false, 'setPending(false) must reset the flag');
  }

  public testRecordChangedFlagDefaultsFalseAndIsSettable(): void {
    const record = new UpdateFuncRecord({ updateFunc: this._makeUpdateFunc() });

    eq(record.isChanged(), false, 'changed must default to false');

    record.setIsChanged(true);
    eq(record.isChanged(), true, 'setIsChanged(true) must set the flag');

    record.setIsChanged(false);
    eq(record.isChanged(), false, 'setIsChanged(false) must reset the flag');
  }

  public testRecordGetUpdateFuncReturnsGivenFunction(): void {
    let callObserved = false;
    const updateFunc = (elmtId: number, isFirstRender: boolean, param?: Object): void => {
      callObserved = true;
    };
    const record = new UpdateFuncRecord({ updateFunc: updateFunc });

    const storedFunc = record.getUpdateFunc();
    eq(storedFunc, updateFunc, 'getUpdateFunc must return exactly the given function');

    storedFunc!(1, true);
    eq(callObserved, true, 'calling the stored function must run the given function');
  }

  // =========================================================================
  // SECTION 5: debug info tests
  // =========================================================================

  public testDebugInfoRegisteredElmtIds(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(50, { updateFunc: this._makeUpdateFunc(), classObject: this._makeTextClassObject() });
    map.set(51, { updateFunc: this._makeUpdateFunc(), classObject: { prototype: {} } });

    const info = map.debugInfoRegisteredElmtIds();

    eq(info.includes('Text[50]'), true, 'info must list named component with its elmtId');
    eq(info.includes('unspecified UINode[51]'), true,
      'info must list unnamed component as unspecified UINode');
    eq(info.includes(', '), true, 'entries must be separated by ", "');
  }

  public testDebugInfoElmtIdKnownAndUnknown(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(60, { updateFunc: this._makeUpdateFunc(), classObject: this._makeTextClassObject() });

    eq(map.debugInfoElmtId(60), 'Text[60]', 'known elmtId must dump name and id');
    eq(map.debugInfoElmtId(9999), 'unknown component type[9999]',
      'unknown elmtId must dump unknown component type');
  }

  public testDebugInfoRegisteredElmtIdsEmptyMap(): void {
    const map = new UpdateFuncsByElmtId();

    eq(map.debugInfoRegisteredElmtIds(), '', 'empty map must dump an empty string');
  }

  // =========================================================================
  // SECTION 6: usage pattern tests
  // =========================================================================

  public testSetUpdateFunctionViaBareFunctionThenReadThroughRecord(): void {
    const map = new UpdateFuncsByElmtId();
    const updateFunc = this._makeUpdateFunc();

    map.set(70, updateFunc);
    map.set(71, { updateFunc: updateFunc, classObject: this._makeTextClassObject() });

    eq(map.get(70)!.getComponentName(), 'unspecified UINode',
      'bare function entry has no class object');
    eq(map.get(71)!.getComponentName(), 'Text',
      'object params entry keeps its class object');
    eq(map.size, 2, 'both entries must be registered');
  }

  public testEntryIndependentRecords(): void {
    const map = new UpdateFuncsByElmtId();
    map.set(80, { updateFunc: this._makeUpdateFunc() });
    map.set(81, { updateFunc: this._makeUpdateFunc() });
    map.get(80)!.setPending(true);

    eq(map.get(80)!.isPending(), true, 'flag of first entry must be set');
    eq(map.get(81)!.isPending(), false, 'flag of second entry must be unaffected');
  }

  public testRealStaticClassObjectPattern(): void {
    // mimic the framework pattern: static JS interface class object with name and pop
    const map = new UpdateFuncsByElmtId();
    const textClass = TextUIClass as unknown as UIClassObject;

    map.set(90, { updateFunc: this._makeUpdateFunc(), classObject: textClass });

    eq(map.get(90)!.getComponentName(), 'TextUIClass',
      'component name must be the static class name');
    neq(map.get(90)!.getPopFunc(), undefined, 'static class pop must be found');
  }
}
