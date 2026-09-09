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

interface IPropertySubscriber {
  id__(): number;
  aboutToBeDeleted(owningView?: IPropertySubscriber): void;
}

interface ISinglePropertyChangeSubscriber<T> extends IPropertySubscriber {
  hasChanged(newValue: T): void;
}

interface IMultiPropertiesChangeSubscriber extends IPropertySubscriber {
  propertyHasChanged(info?: string): void;
}

interface ObservedObjectEventsPUReceiver<T> extends IPropertySubscriber {
  onTrackedObjectPropertyCompatModeHasChangedPU(eventSource: T, propName: string): void;
}

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare abstract class SubscribableAbstract {
  constructor();
  protected notifyPropertyHasChanged(propName: string, newValue: any): void;
  numberOfSubscribers(): number;
  addOwningProperty(subscriber: IPropertySubscriber): void;
  removeOwningProperty(property: IPropertySubscriber): void;
  removeOwningPropertyById(subscriberId: number): void;
  clearOwningProperties(): void;
}

// class name with typo kept for backward compatibility
declare abstract class SubscribaleAbstract extends SubscribableAbstract {
}

declare class SubscriberManager {
  static Has(id: number): boolean;
  static Find(id: number): IPropertySubscriber;
  static Delete(id: number): boolean;
  static Add(newSubscriber: IPropertySubscriber): boolean;
  static MakeId(): number;
}

/**
 * Subscriber that implements the FU (full update) notification interfaces,
 * notifyPropertyHasChanged calls hasChanged() and propertyHasChanged() on it.
 */
class FuPathSubscriber implements ISinglePropertyChangeSubscriber<number>, IMultiPropertiesChangeSubscriber {
  private id_: number;
  public hasChangedCount: number = 0;
  public lastNewValue: number | undefined = undefined;
  public propertyHasChangedCount: number = 0;
  public lastChangedPropName: string | undefined = undefined;

  constructor(id: number) {
    this.id_ = id;
  }

  id__(): number {
    return this.id_;
  }

  aboutToBeDeleted(owningView?: IPropertySubscriber): void {
  }

  hasChanged(newValue: number): void {
    this.hasChangedCount++;
    this.lastNewValue = newValue;
  }

  propertyHasChanged(info?: string): void {
    this.propertyHasChangedCount++;
    this.lastChangedPropName = info;
  }
}

/**
 * Subscriber that implements the PU (partial update) compat mode interface,
 * notifyPropertyHasChanged calls onTrackedObjectPropertyCompatModeHasChangedPU() on it.
 */
class PuPathSubscriber implements ObservedObjectEventsPUReceiver<SubscribableAbstract> {
  private id_: number;
  public notifyCount: number = 0;
  public lastPropName: string | undefined = undefined;
  public lastEventSource: SubscribableAbstract | undefined = undefined;

  constructor(id: number) {
    this.id_ = id;
  }

  id__(): number {
    return this.id_;
  }

  aboutToBeDeleted(owningView?: IPropertySubscriber): void {
  }

  onTrackedObjectPropertyCompatModeHasChangedPU(eventSource: SubscribableAbstract, propName: string): void {
    this.notifyCount++;
    this.lastPropName = propName;
    this.lastEventSource = eventSource;
  }
}

/**
 * Subscriber that implements neither notification interface.
 */
class SilentSubscriber implements IPropertySubscriber {
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

/** concrete subclass to access the protected notify function */
class TestSubscribable extends SubscribableAbstract {
  public value: number = 0;

  constructor(val: number = 0) {
    super();
    this.value = val;
  }

  public firePropertyHasChanged(propName: string, newValue: any): void {
    this.notifyPropertyHasChanged(propName, newValue);
  }
}

/** subclass of the typo class SubscribaleAbstract */
class TestTypoSubscribable extends SubscribaleAbstract {
}

/**
 * SubscribableAbstract Unit Tests
 *
 * This test suite validates SubscribableAbstract functionality:
 * - Constructor initial state
 * - addOwningProperty / removeOwningProperty / removeOwningPropertyById
 * - clearOwningProperties
 * - notifyPropertyHasChanged notification to FU and PU subscribers
 * - Notification robustness for unknown subscriber ids
 * - Backward-compat typo class SubscribaelAbstract
 */
export class SubscribableAbstractTestsV1 implements ITestFile {
  private idString: string = '';
  private addedIds_: number[] = [];

  constructor(str: string) {
    console.log(`Creating SubscribableAbstractTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('SubscribableAbstractTestsV1: Setting up test suite');
  }

  public beforeEach(): void {
    this.addedIds_ = [];
  }

  public afterAll(): void {
    console.log('SubscribableAbstractTestsV1: Tearing down test suite');
  }

  public afterEach(): void {
    this.addedIds_.forEach((id: number) => SubscriberManager.Delete(id));
    this.addedIds_ = [];
  }

  public getId(): string {
    return this.idString;
  }

  // helper: create an FuPathSubscriber with a fresh id, registered in SubscriberManager
  private _makeFuSubscriber(): FuPathSubscriber {
    const subscriber = new FuPathSubscriber(SubscriberManager.MakeId());
    this.addedIds_.push(subscriber.id__());
    SubscriberManager.Add(subscriber);
    return subscriber;
  }

  // helper: create a PuPathSubscriber with a fresh id, registered in SubscriberManager
  private _makePuSubscriber(): PuPathSubscriber {
    const subscriber = new PuPathSubscriber(SubscriberManager.MakeId());
    this.addedIds_.push(subscriber.id__());
    SubscriberManager.Add(subscriber);
    return subscriber;
  }

  // helper: create a SilentSubscriber with a fresh id, registered in SubscriberManager
  private _makeSilentSubscriber(): SilentSubscriber {
    const subscriber = new SilentSubscriber(SubscriberManager.MakeId());
    this.addedIds_.push(subscriber.id__());
    SubscriberManager.Add(subscriber);
    return subscriber;
  }

  // =========================================================================
  // SECTION 1: Constructor and subscriber bookkeeping tests
  // =========================================================================

  public testConstructorStartsWithZeroSubscribers(): void {
    const subscribable = new TestSubscribable();

    eq(subscribable.numberOfSubscribers(), 0,
      'a fresh SubscribableAbstract must have no subscribers');
  }

  public testAddOwningPropertyIncreasesCount(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeSilentSubscriber();

    subscribable.addOwningProperty(subscriber);

    eq(subscribable.numberOfSubscribers(), 1,
      'addOwningProperty must increase subscriber count to 1');
  }

  public testAddSameSubscriberTwiceKeepsCountAtOne(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeSilentSubscriber();

    subscribable.addOwningProperty(subscriber);
    subscribable.addOwningProperty(subscriber);

    eq(subscribable.numberOfSubscribers(), 1,
      'subscriber ids are kept in a Set, adding twice must not increase count');
  }

  public testAddMultipleDifferentSubscribers(): void {
    const subscribable = new TestSubscribable();
    const subscriber1 = this._makeSilentSubscriber();
    const subscriber2 = this._makeSilentSubscriber();
    const subscriber3 = this._makeSilentSubscriber();

    subscribable.addOwningProperty(subscriber1);
    subscribable.addOwningProperty(subscriber2);
    subscribable.addOwningProperty(subscriber3);

    eq(subscribable.numberOfSubscribers(), 3,
      'three different subscribers must be counted');
  }

  public testRemoveOwningPropertyDecreasesCount(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeSilentSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.removeOwningProperty(subscriber);

    eq(subscribable.numberOfSubscribers(), 0,
      'removeOwningProperty must remove the subscriber');
  }

  public testRemoveOwningPropertyOnlyRemovesGivenSubscriber(): void {
    const subscribable = new TestSubscribable();
    const subscriber1 = this._makeSilentSubscriber();
    const subscriber2 = this._makeSilentSubscriber();
    subscribable.addOwningProperty(subscriber1);
    subscribable.addOwningProperty(subscriber2);

    subscribable.removeOwningProperty(subscriber1);

    eq(subscribable.numberOfSubscribers(), 1,
      'only the removed subscriber must be gone');
  }

  public testRemoveUnknownSubscriberNoThrow(): void {
    const subscribable = new TestSubscribable();
    const unknownSubscriber = new SilentSubscriber(SubscriberManager.MakeId());

    subscribable.removeOwningProperty(unknownSubscriber);

    eq(subscribable.numberOfSubscribers(), 0,
      'removing an unknown subscriber must not throw and not change count');
  }

  public testRemoveOwningPropertyById(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeSilentSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.removeOwningPropertyById(subscriber.id__());

    eq(subscribable.numberOfSubscribers(), 0,
      'removeOwningPropertyById must remove by id');
  }

  public testRemoveOwningPropertyByIdUnknownIdNoThrow(): void {
    const subscribable = new TestSubscribable();
    const unknownId = SubscriberManager.MakeId();

    subscribable.removeOwningPropertyById(unknownId);

    eq(subscribable.numberOfSubscribers(), 0,
      'removing an unknown id must not throw and not change count');
  }

  public testClearOwningPropertiesRemovesAll(): void {
    const subscribable = new TestSubscribable();
    subscribable.addOwningProperty(this._makeSilentSubscriber());
    subscribable.addOwningProperty(this._makeSilentSubscriber());
    eq(subscribable.numberOfSubscribers(), 2, 'precondition: two subscribers');

    subscribable.clearOwningProperties();

    eq(subscribable.numberOfSubscribers(), 0,
      'clearOwningProperties must remove all subscribers');
  }

  public testClearOwningPropertiesOnEmptyNoThrow(): void {
    const subscribable = new TestSubscribable();

    subscribable.clearOwningProperties();

    eq(subscribable.numberOfSubscribers(), 0,
      'clearOwningProperties on empty object must not throw');
  }

  public testAddAfterClearWorks(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeSilentSubscriber();
    subscribable.addOwningProperty(subscriber);
    subscribable.clearOwningProperties();

    subscribable.addOwningProperty(subscriber);

    eq(subscribable.numberOfSubscribers(), 1,
      'addOwningProperty must work again after clearOwningProperties');
  }

  // =========================================================================
  // SECTION 2: notifyPropertyHasChanged tests
  // =========================================================================

  public testNotifyCallsHasChangedWithNewValue(): void {
    const subscribable = new TestSubscribable(10);
    const subscriber = this._makeFuSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.firePropertyHasChanged('value', 42);

    eq(subscriber.hasChangedCount, 1, 'hasChanged must be called once');
    eq(subscriber.lastNewValue, 42, 'hasChanged must receive the new value');
  }

  public testNotifyCallsPropertyHasChangedWithPropName(): void {
    const subscribable = new TestSubscribable(10);
    const subscriber = this._makeFuSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.firePropertyHasChanged('value', 42);

    eq(subscriber.propertyHasChangedCount, 1, 'propertyHasChanged must be called once');
    eq(subscriber.lastChangedPropName, 'value',
      'propertyHasChanged must receive the changed property name');
  }

  public testNotifyCallsPuCompatModeReceiver(): void {
    const subscribable = new TestSubscribable(7);
    const subscriber = this._makePuSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.firePropertyHasChanged('value', 8);

    eq(subscriber.notifyCount, 1,
      'onTrackedObjectPropertyCompatModeHasChangedPU must be called once');
    eq(subscriber.lastPropName, 'value',
      'PU receiver must receive the changed property name');
    eq(subscriber.lastEventSource, subscribable,
      'PU receiver must receive the SubscribableAbstract object as event source');
  }

  public testNotifyWithoutSubscribersNoThrow(): void {
    const subscribable = new TestSubscribable();

    subscribable.firePropertyHasChanged('value', 1);

    eq(subscribable.numberOfSubscribers(), 0,
      'notify without any subscriber must not throw');
  }

  public testNotifyAllSubscribers(): void {
    const subscribable = new TestSubscribable();
    const fuSubscriber = this._makeFuSubscriber();
    const puSubscriber = this._makePuSubscriber();
    const silentSubscriber = this._makeSilentSubscriber();
    subscribable.addOwningProperty(fuSubscriber);
    subscribable.addOwningProperty(puSubscriber);
    subscribable.addOwningProperty(silentSubscriber);

    subscribable.firePropertyHasChanged('counter', 99);

    eq(fuSubscriber.hasChangedCount, 1, 'FU subscriber must be notified');
    eq(puSubscriber.notifyCount, 1, 'PU subscriber must be notified');
  }

  public testNotifyEachChangeCallsSubscribersAgain(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeFuSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.firePropertyHasChanged('value', 1);
    subscribable.firePropertyHasChanged('value', 2);
    subscribable.firePropertyHasChanged('value', 3);

    eq(subscriber.hasChangedCount, 3, 'hasChanged must be called for each change');
    eq(subscriber.lastNewValue, 3, 'hasChanged must receive the latest value');
    eq(subscriber.propertyHasChangedCount, 3,
      'propertyHasChanged must be called for each change');
  }

  public testNotifyUnknownSubscriberIdDoesNotThrow(): void {
    const subscribable = new TestSubscribable();
    // register an owning property whose id is NOT registered in SubscriberManager:
    // the id was never Add()ed, Find() returns undefined -> error log path
    const ghost = new SilentSubscriber(SubscriberManager.MakeId());
    subscribable.addOwningProperty(ghost);
    const healthySubscriber = this._makeFuSubscriber();
    subscribable.addOwningProperty(healthySubscriber);

    subscribable.firePropertyHasChanged('value', 5);

    eq(healthySubscriber.hasChangedCount, 1,
      'healthy subscriber must still be notified although another subscriber id is unknown');
  }

  public testRemovedSubscriberIsNoLongerNotified(): void {
    const subscribable = new TestSubscribable();
    const subscriber = this._makeFuSubscriber();
    subscribable.addOwningProperty(subscriber);

    subscribable.firePropertyHasChanged('value', 1);
    eq(subscriber.hasChangedCount, 1, 'precondition: subscriber was notified');

    subscribable.removeOwningProperty(subscriber);
    subscribable.firePropertyHasChanged('value', 2);

    eq(subscriber.hasChangedCount, 1,
      'a removed subscriber must not be notified anymore');
  }

  // =========================================================================
  // SECTION 3: typo class SubscribaelAbstract tests
  // =========================================================================

  public testTypoClassIsInstanceOfSubscribableAbstract(): void {
    const typoSubscribable = new TestTypoSubscribable();

    neq(typoSubscribable, undefined, 'SubscribaelAbstract subclass can be created');
    eq(typoSubscribable instanceof SubscribableAbstract, true,
      'SubscribaelAbstract extends SubscribableAbstract');
  }

  public testTypoClassInheritsSubscriberManagement(): void {
    const typoSubscribable = new TestTypoSubscribable();
    const subscriber = this._makeSilentSubscriber();

    typoSubscribable.addOwningProperty(subscriber);
    eq(typoSubscribable.numberOfSubscribers(), 1,
      'typo class must inherit addOwningProperty');

    typoSubscribable.removeOwningProperty(subscriber);
    eq(typoSubscribable.numberOfSubscribers(), 0,
      'typo class must inherit removeOwningProperty');

    typoSubscribable.clearOwningProperties();
    eq(typoSubscribable.numberOfSubscribers(), 0,
      'typo class must inherit clearOwningProperties');
  }
}
