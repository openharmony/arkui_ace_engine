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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner'

interface IPropertySubscriber {
  id__(): number;
  aboutToBeDeleted(owningView?: IPropertySubscriber): void;
}

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class SubscriberManager {
  static Has(id: number): boolean;
  static Find(id: number): IPropertySubscriber;
  static Delete(id: number): boolean;
  static Add(newSubscriber: IPropertySubscriber): boolean;
  static UpdateRecycleElmtId(oldId: number, newId: number): boolean;
  static MakeId(): number;
  static MakeStateVariableId(): number;
  static NumberOfSubscribers(): number;
  static Get(): SubscriberManager;
  static DumpSubscriberInfo(): void;
  has(id: number): boolean;
  get(id: number): IPropertySubscriber;
  delete(id: number): boolean;
  add(newSubscriber: IPropertySubscriber): boolean;
  updateRecycleElmtId(oldId: number, newId: number): boolean;
  numberOfSubscribers(): number;
  dumpSubscriberInfo(): void;
}

/**
 * A subscriber that offers an info() function, SubscriberManager.dumpSubscriberInfo
 * prints the result of info() for such subscribers.
 */
class SubscriberWithInfo implements IPropertySubscriber {
  private id_: number;
  private infoText_: string;

  constructor(id: number, infoText: string) {
    this.id_ = id;
    this.infoText_ = infoText;
  }

  id__(): number {
    return this.id_;
  }

  aboutToBeDeleted(owningView?: IPropertySubscriber): void {
  }

  info(): string {
    return this.infoText_;
  }
}

/**
 * A subscriber without info() function, dumpSubscriberInfo prints
 * 'unknown' for such subscribers.
 */
class SubscriberWithoutInfo implements IPropertySubscriber {
  private id_: number;

  constructor(id: number) {
    this.id_ = id;
  }

  id__(): number {
    return this.id_;
  }

  aboutToBeDeleted(owningView?: IPropertySubscriber): void {
  }
}

/**
 * SubscriberManager Unit Tests
 *
 * This test suite validates SubscriberManager functionality:
 * - Id creation (MakeId / MakeStateVariableId)
 * - Singleton access
 * - Add / Has / Find / Delete operations
 * - NumberOfSubscribers bookkeeping
 * - updateRecycleElmtId behavior
 * - Instance (non-static) API mirrors static API
 * - dumpSubscriberInfo for both subscriber flavors
 */
export class SubscriberManagerTestsV1 implements ITestFile {
  private idString: string = '';
  private addedIds_: number[] = [];

  constructor(str: string) {
    console.log(`Creating SubscriberManagerTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('SubscriberManagerTestsV1: Setting up test suite');
  }

  public beforeEach(): void {
    this.addedIds_ = [];
  }

  public afterAll(): void {
    console.log('SubscriberManagerTestsV1: Tearing down test suite');
  }

  public afterEach(): void {
    // remove all subscribers this test added to not affect other tests
    // and the running application
    this.addedIds_.forEach((id: number) => SubscriberManager.Delete(id));
    this.addedIds_ = [];
  }

  public getId(): string {
    return this.idString;
  }

  // helper: create a subscriber with a fresh id and remember the id for cleanup
  private _makeSubscriber(infoText?: string): IPropertySubscriber {
    const id = SubscriberManager.MakeId();
    this.addedIds_.push(id);
    return infoText !== undefined ?
      new SubscriberWithInfo(id, infoText) : new SubscriberWithoutInfo(id);
  }

  // helper: create, add to SubscriberManager and return the subscriber
  private _makeAndAddSubscriber(infoText?: string): IPropertySubscriber {
    const subscriber = this._makeSubscriber(infoText);
    SubscriberManager.Add(subscriber);
    return subscriber;
  }

  // =========================================================================
  // SECTION 1: Id creation tests
  // =========================================================================

  public testMakeIdReturnsUniqueIds(): void {
    const id1 = SubscriberManager.MakeId();
    const id2 = SubscriberManager.MakeId();
    const id3 = SubscriberManager.MakeId();

    neq(id1, id2, 'two MakeId() results must differ');
    neq(id2, id3, 'two MakeId() results must differ');
    neq(id1, id3, 'two MakeId() results must differ');
    eq(typeof id1, 'number', 'MakeId() must return a number');
  }

  public testMakeStateVariableIdReturnsStrictlyDecreasingIds(): void {
    const id1 = SubscriberManager.MakeStateVariableId();
    const id2 = SubscriberManager.MakeStateVariableId();
    const id3 = SubscriberManager.MakeStateVariableId();

    gt(id1, id2, 'MakeStateVariableId() must decrease (post-fix decrement)');
    gt(id2, id3, 'MakeStateVariableId() must decrease (post-fix decrement)');
    eq(id1 - id2, 1, 'consecutive MakeStateVariableId() results differ by 1');
    eq(id2 - id3, 1, 'consecutive MakeStateVariableId() results differ by 1');
  }

  public testMakeIdAndMakeStateVariableIdDoNotCollide(): void {
    const stateVariableId = SubscriberManager.MakeStateVariableId();
    const elementId = SubscriberManager.MakeId();
    this.addedIds_.push(elementId);

    neq(stateVariableId, elementId,
      'ids from MakeId and MakeStateVariableId must not be equal');
  }

  // =========================================================================
  // SECTION 2: Singleton tests
  // =========================================================================

  public testGetReturnsSameSingletonInstance(): void {
    const instance1 = SubscriberManager.Get();
    const instance2 = SubscriberManager.Get();

    eq(instance1, instance2, 'Get() must always return the same singleton');
    neq(instance1, undefined, 'Get() must never return undefined');
  }

  // =========================================================================
  // SECTION 3: Add / Has / Find tests
  // =========================================================================

  public testAddRegistersSubscriber(): void {
    const subscriber = this._makeSubscriber('add-test');

    eq(SubscriberManager.Add(subscriber), true, 'Add() must succeed for fresh id');
    eq(SubscriberManager.Has(subscriber.id__()), true, 'Has() must find added subscriber');
  }

  public testAddSameSubscriberTwiceReturnsFalse(): void {
    const subscriber = this._makeSubscriber('dup-test');
    eq(SubscriberManager.Add(subscriber), true, 'first Add() must succeed');

    eq(SubscriberManager.Add(subscriber), false,
      'second Add() with same id must fail');
  }

  public testAddTwoSubscribersWithSameIdReturnsFalse(): void {
    const id = SubscriberManager.MakeId();
    this.addedIds_.push(id);
    const first = new SubscriberWithInfo(id, 'first');
    const second = new SubscriberWithInfo(id, 'second');

    eq(SubscriberManager.Add(first), true, 'first Add() must succeed');
    eq(SubscriberManager.Add(second), false,
      'Add() for an already used id must fail');
    eq(SubscriberManager.Find(id), first,
      'Find() must return the subscriber that was added first');
  }

  public testHasReturnsFalseForUnknownId(): void {
    const unknownId = SubscriberManager.MakeId();
    // note: id is not registered on purpose, do not clean it up via Add

    eq(SubscriberManager.Has(unknownId), false,
      'Has() must return false for never added id');
  }

  public testFindReturnsUndefinedForUnknownId(): void {
    const unknownId = SubscriberManager.MakeId();

    eq(SubscriberManager.Find(unknownId), undefined,
      'Find() must return undefined for never added id');
  }

  public testFindReturnsAddedSubscriber(): void {
    const subscriber = this._makeAndAddSubscriber('find-test');

    eq(SubscriberManager.Find(subscriber.id__()), subscriber,
      'Find() must return exactly the added subscriber object');
  }

  // =========================================================================
  // SECTION 4: Delete tests
  // =========================================================================

  public testDeleteRemovesSubscriber(): void {
    const subscriber = this._makeAndAddSubscriber('delete-test');
    eq(SubscriberManager.Has(subscriber.id__()), true, 'precondition: subscriber added');

    eq(SubscriberManager.Delete(subscriber.id__()), true, 'Delete() must succeed');
    eq(SubscriberManager.Has(subscriber.id__()), false,
      'Has() must not find deleted subscriber');
    eq(SubscriberManager.Find(subscriber.id__()), undefined,
      'Find() must return undefined for deleted subscriber');
  }

  public testDeleteUnknownIdReturnsFalse(): void {
    const unknownId = SubscriberManager.MakeId();

    eq(SubscriberManager.Delete(unknownId), false,
      'Delete() for unknown id must return false');
  }

  public testDeleteSameIdTwiceReturnsFalseSecondTime(): void {
    const subscriber = this._makeAndAddSubscriber('delete-twice-test');

    eq(SubscriberManager.Delete(subscriber.id__()), true, 'first Delete() must succeed');
    eq(SubscriberManager.Delete(subscriber.id__()), false,
      'second Delete() for same id must fail');
  }

  public testReAddAfterDeleteSucceeds(): void {
    const subscriber = this._makeSubscriber('re-add-test');
    eq(SubscriberManager.Add(subscriber), true, 'first Add() must succeed');
    eq(SubscriberManager.Delete(subscriber.id__()), true, 'Delete() must succeed');

    eq(SubscriberManager.Add(subscriber), true,
      'Add() must succeed again after Delete()');
    eq(SubscriberManager.Find(subscriber.id__()), subscriber,
      'Find() must return re-added subscriber');
  }

  // =========================================================================
  // SECTION 5: NumberOfSubscribers tests
  // =========================================================================

  public testNumberOfSubscribersFollowsAddAndDelete(): void {
    const countBefore = SubscriberManager.NumberOfSubscribers();
    const subscriber1 = this._makeAndAddSubscriber('count-1');
    const subscriber2 = this._makeAndAddSubscriber('count-2');

    eq(SubscriberManager.NumberOfSubscribers(), countBefore + 2,
      'two Add() must increase count by 2');

    SubscriberManager.Delete(subscriber1.id__());
    eq(SubscriberManager.NumberOfSubscribers(), countBefore + 1,
      'one Delete() must decrease count by 1');

    SubscriberManager.Delete(subscriber2.id__());
    eq(SubscriberManager.NumberOfSubscribers(), countBefore,
      'count must be back to initial value');
  }

  public testNumberOfSubscribersUnchangedByDuplicateAdd(): void {
    const countBefore = SubscriberManager.NumberOfSubscribers();
    const subscriber = this._makeSubscriber('count-dup');

    SubscriberManager.Add(subscriber);
    SubscriberManager.Add(subscriber);

    eq(SubscriberManager.NumberOfSubscribers(), countBefore + 1,
      'duplicate Add() must not change the count');
  }

  // =========================================================================
  // SECTION 6: updateRecycleElmtId tests
  // =========================================================================

  public testUpdateRecycleElmtIdMovesSubscriberToNewId(): void {
    const subscriber = this._makeAndAddSubscriber('recycle-test');
    const oldId = subscriber.id__();
    const newId = SubscriberManager.MakeId();
    this.addedIds_.push(newId);

    eq(SubscriberManager.UpdateRecycleElmtId(oldId, newId), true,
      'UpdateRecycleElmtId() must succeed for known old id');
    eq(SubscriberManager.Has(oldId), false, 'old id must no longer be known');
    eq(SubscriberManager.Has(newId), true, 'new id must be known');
    eq(SubscriberManager.Find(newId), subscriber,
      'Find() by new id must return the moved subscriber');
    eq(SubscriberManager.Find(oldId), undefined,
      'Find() by old id must return undefined');
  }

  public testUpdateRecycleElmtIdUnknownOldIdReturnsFalse(): void {
    const unknownOldId = SubscriberManager.MakeId();
    const newId = SubscriberManager.MakeId();
    this.addedIds_.push(newId);

    eq(SubscriberManager.UpdateRecycleElmtId(unknownOldId, newId), false,
      'UpdateRecycleElmtId() must fail for unknown old id');
    eq(SubscriberManager.Has(newId), false,
      'new id must not be registered when old id is unknown');
  }

  public testUpdateRecycleElmtIdToExistingIdReplacesIt(): void {
    const movedSubscriber = this._makeAndAddSubscriber('recycle-moved');
    const replacedSubscriber = this._makeAndAddSubscriber('recycle-replaced');
    const oldId = movedSubscriber.id__();
    const existingId = replacedSubscriber.id__();

    eq(SubscriberManager.UpdateRecycleElmtId(oldId, existingId), true,
      'UpdateRecycleElmtId() must succeed for known old id');
    eq(SubscriberManager.Find(existingId), movedSubscriber,
      'Find() by new id must return the moved subscriber, replacing the old entry');
  }

  public testUpdateRecycleElmtIdKeepsTotalCount(): void {
    const countBefore = SubscriberManager.NumberOfSubscribers();
    const subscriber = this._makeAndAddSubscriber('recycle-count');
    const newId = SubscriberManager.MakeId();
    this.addedIds_.push(newId);

    SubscriberManager.UpdateRecycleElmtId(subscriber.id__(), newId);

    eq(SubscriberManager.NumberOfSubscribers(), countBefore + 1,
      'moving an id must not change the total count');
  }

  // =========================================================================
  // SECTION 7: instance (non-static) API tests
  // =========================================================================

  public testInstanceAddHasGetDeleteMirrorStaticApi(): void {
    const instance = SubscriberManager.Get();
    const subscriber = this._makeSubscriber('instance-api-test');
    const id = subscriber.id__();

    eq(instance.add(subscriber), true, 'instance add() must succeed');
    eq(instance.has(id), true, 'instance has() must find subscriber');
    eq(instance.get(id), subscriber, 'instance get() must return subscriber');

    eq(instance.delete(id), true, 'instance delete() must succeed');
    eq(instance.has(id), false, 'instance has() must not find deleted subscriber');
  }

  public testInstanceNumberOfSubscribersEqualsStaticResult(): void {
    const instance = SubscriberManager.Get();

    eq(instance.numberOfSubscribers(), SubscriberManager.NumberOfSubscribers(),
      'instance and static NumberOfSubscribers must match');
  }

  public testInstanceDeleteUnknownIdReturnsFalse(): void {
    const instance = SubscriberManager.Get();
    const unknownId = SubscriberManager.MakeId();

    eq(instance.delete(unknownId), false,
      'instance delete() for unknown id must return false');
  }

  // =========================================================================
  // SECTION 8: dumpSubscriberInfo tests
  // =========================================================================

  public testDumpSubscriberInfoWithInfoMethodNoThrow(): void {
    const subscriber = this._makeAndAddSubscriber('dump-info-test');

    SubscriberManager.DumpSubscriberInfo();
    SubscriberManager.Get().dumpSubscriberInfo();

    eq(SubscriberManager.Has(subscriber.id__()), true,
      'dump must not modify registered subscribers');
  }

  public testDumpSubscriberInfoWithoutInfoMethodNoThrow(): void {
    const subscriber = this._makeAndAddSubscriber();

    SubscriberManager.DumpSubscriberInfo();

    eq(SubscriberManager.Has(subscriber.id__()), true,
      'dump must not modify registered subscribers');
  }

  public testDumpSubscriberInfoEmptyAndMixedNoThrow(): void {
    // dump also works when only subscribers without info() exist
    const plainSubscriber = this._makeAndAddSubscriber();
    const infoSubscriber = this._makeAndAddSubscriber('mixed-info');

    SubscriberManager.DumpSubscriberInfo();

    eq(SubscriberManager.Has(plainSubscriber.id__()), true,
      'dump must not modify registered subscribers');
    eq(SubscriberManager.Has(infoSubscriber.id__()), true,
      'dump must not modify registered subscribers');
  }
}
