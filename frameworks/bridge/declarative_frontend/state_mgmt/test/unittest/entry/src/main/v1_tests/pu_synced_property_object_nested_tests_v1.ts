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

type PropertyInfo = string;

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class SynchedPropertyNestedObjectPU<C extends Object> {
  constructor(obsObject: C, owningChildView: IPropertySubscriber, propertyName: PropertyInfo);
  staticWatchFunc?: Object;
  aboutToBeDeleted(): void;
  getUnmonitored(): C;
  get(): C;
  set(newValue: C): void;
  id__(): number;
}

// class name with typo kept for backward compatibility
declare class SynchedPropertyNesedObjectPU<C extends Object> extends SynchedPropertyNestedObjectPU<C> {
}

declare class ObservedObject {
  static IsObservedObject(obj: any): boolean;
  static countSubscribers(obj: Object): number | false;
  static createNew<T extends Object>(rawObject: T, owningProperty: IPropertySubscriber): T;
}

declare class ObserveV2 {
  static IsObservedObjectV2(value: any): boolean;
}

declare class SubscriberManager {
  static Has(id: number): boolean;
  static Delete(id: number): boolean;
}

declare abstract class SubscribableAbstract {
  numberOfSubscribers(): number;
  addOwningProperty(subscriber: IPropertySubscriber): void;
  removeOwningProperty(property: IPropertySubscriber): void;
}

class NestedObservedClassA {
  public valueA: number = 1;

  constructor(valueA: number = 1) {
    this.valueA = valueA;
  }
}

class NestedObservedClassB {
  public valueB: string = 'b';

  constructor(valueB: string = 'b') {
    this.valueB = valueB;
  }
}

/** concrete SubscribableAbstract to observe SubscribableAbstract values */
class NestedTestSubscribable extends SubscribableAbstract {
  public value: number = 0;

  constructor(val: number = 0) {
    super();
    this.value = val;
  }
}

/**
 * Child view substitute: counted syncPeerHasChanged notifications are the
 * PU code path reaction to SynchedPropertyNestedObjectPU value changes.
 */
class NestedChildSubscriber implements IPropertySubscriber {
  private id_: number;
  public syncPeerCount: number = 0;

  constructor(id: number) {
    this.id_ = id;
  }

  id__(): number {
    return this.id_;
  }

  aboutToBeDeleted(owningView?: IPropertySubscriber): void {
  }

  syncPeerHasChanged(eventSource: Object, isSync?: boolean): void {
    this.syncPeerCount++;
  }
}

/**
 * SynchedPropertyNestedObjectPU Unit Tests (@ObjectLink implementation)
 *
 * This test suite validates SynchedPropertyNestedObjectPU functionality:
 * - Constructor and get / getUnmonitored
 * - set with unchanged / changed plain object values
 * - set with undefined and illegal values
 * - Registration / unregistration on @Observed objects
 * - Registration / unregistration on SubscribableAbstract objects
 * - aboutToBeDeleted lifecycle
 * - Typo subclass SynchedPropertyNesedObjectPU
 */
export class PuSyncedPropertyObjectNestedTestsV1 implements ITestFile {
  private idString: string = '';
  private propertiesToCleanup_: SynchedPropertyNestedObjectPU<Object>[] = [];

  constructor(str: string) {
    console.log(`Creating PuSyncedPropertyObjectNestedTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('PuSyncedPropertyObjectNestedTestsV1: Setting up test suite');
  }

  public beforeEach(): void {
    this.propertiesToCleanup_ = [];
  }

  public afterAll(): void {
    console.log('PuSyncedPropertyObjectNestedTestsV1: Tearing down test suite');
  }

  public afterEach(): void {
    // unregister every property created by a test from SubscriberManager
    this.propertiesToCleanup_.forEach((property: SynchedPropertyNestedObjectPU<Object>) => {
      property.aboutToBeDeleted();
    });
    this.propertiesToCleanup_ = [];
  }

  public getId(): string {
    return this.idString;
  }

  // helper: create a SynchedPropertyNestedObjectPU and remember it for cleanup
  private _makeProperty<C extends Object>(obsObject: C, subscriber: IPropertySubscriber,
    propertyName: string): SynchedPropertyNestedObjectPU<C> {
    const property = new SynchedPropertyNestedObjectPU<C>(obsObject, subscriber, propertyName);
    this.propertiesToCleanup_.push(property as SynchedPropertyNestedObjectPU<Object>);
    return property;
  }

  // =========================================================================
  // SECTION 1: Constructor and get tests
  // =========================================================================

  public testConstructorWithPlainObject(): void {
    const subscriber = new NestedChildSubscriber(1000);
    const plainObject = { someProp: 'someValue' };

    const property = this._makeProperty<Object>(plainObject, subscriber, 'objectLinkVar');

    neq(property, undefined, 'property must be created for a plain object');
    eq(property.get(), plainObject, 'get() must return the object given to constructor');
    eq(property.getUnmonitored(), plainObject,
      'getUnmonitored() must return the object given to constructor');
  }

  public testConstructorRegistersItselfInSubscriberManager(): void {
    const subscriber = new NestedChildSubscriber(1001);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    eq(SubscriberManager.Has(property.id__()), true,
      'property must register itself in SubscriberManager upon construction');
  }

  public testConstructorWithObservedObject(): void {
    const subscriber = new NestedChildSubscriber(1002);
    const observedObject = ObservedObject.createNew(new NestedObservedClassA(5), undefined as unknown as IPropertySubscriber);

    const property = this._makeProperty<NestedObservedClassA>(observedObject, subscriber, 'objectLinkVar');

    eq(ObservedObject.IsObservedObject(observedObject), true,
      'precondition: createNew result is an ObservedObject');
    eq(property.get(), observedObject, 'get() must return the observed object');
    eq(property.getUnmonitored(), observedObject,
      'getUnmonitored() must return the observed object');
  }

  public testConstructorRegistersOnObservedObject(): void {
    const subscriber = new NestedChildSubscriber(1003);
    const observedObject = ObservedObject.createNew(new NestedObservedClassA(1), undefined as unknown as IPropertySubscriber);
    const countBefore = ObservedObject.countSubscribers(observedObject) as number;

    this._makeProperty<NestedObservedClassA>(observedObject, subscriber, 'objectLinkVar');

    eq(ObservedObject.countSubscribers(observedObject), countBefore + 1,
      'constructor must register the property as owning property of the observed object');
  }

  public testStaticWatchFuncInitiallyUndefined(): void {
    const subscriber = new NestedChildSubscriber(1004);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    eq(property.staticWatchFunc, undefined,
      'staticWatchFunc is only set in interop mode, must be undefined otherwise');
  }

  // =========================================================================
  // SECTION 2: set tests with plain objects
  // =========================================================================

  public testSetSameObjectDoesNotNotify(): void {
    const subscriber = new NestedChildSubscriber(1005);
    const plainObject = { value: 1 };
    const property = this._makeProperty<Object>(plainObject, subscriber, 'objectLinkVar');

    property.set(plainObject);

    eq(subscriber.syncPeerCount, 0,
      'setting the identical object must not notify subscribers');
    eq(property.get(), plainObject, 'value must be unchanged');
  }

  public testSetDifferentObjectNotifiesOnce(): void {
    const subscriber = new NestedChildSubscriber(1006);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    property.set({ value: 2 });

    eq(subscriber.syncPeerCount, 1,
      'setting a different object must notify subscribers exactly once');
    eq((property.get() as any).value, 2, 'get() must return the new object');
  }

  public testSetUndefinedNotifiesAndStoresUndefined(): void {
    const subscriber = new NestedChildSubscriber(1007);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    property.set(undefined);

    eq(subscriber.syncPeerCount, 1, 'setting undefined must notify subscribers');
    eq(property.get(), undefined, 'get() must return undefined after set(undefined)');
  }

  public testSetNullNotifiesAndStoresNull(): void {
    const subscriber = new NestedChildSubscriber(1008);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    property.set(null);

    eq(subscriber.syncPeerCount, 1, 'setting null must notify subscribers');
    eq(property.get(), null, 'get() must return null after set(null)');
  }

  public testSetIllegalPrimitiveThrowsAndKeepsOldValue(): void {
    const subscriber = new NestedChildSubscriber(1009);
    const oldObject = { value: 1 };
    const property = this._makeProperty<Object>(oldObject, subscriber, 'objectLinkVar');
    let hasThrown = false;

    try {
      property.set(5 as unknown as Object);
    } catch (err) {
      hasThrown = true;
    }

    eq(hasThrown, true, 'assigning a primitive must throw BusinessError');
    eq(property.get(), oldObject, 'value must be unchanged after illegal assignment');
    eq(subscriber.syncPeerCount, 0, 'no notification must happen for illegal assignment');
  }

  public testSetFunctionThrowsAndKeepsOldValue(): void {
    const subscriber = new NestedChildSubscriber(1010);
    const oldObject = { value: 1 };
    const property = this._makeProperty<Object>(oldObject, subscriber, 'objectLinkVar');
    let hasThrown = false;

    try {
      property.set(((): void => {}) as unknown as Object);
    } catch (err) {
      hasThrown = true;
    }

    eq(hasThrown, true, 'assigning a function must throw BusinessError');
    eq(property.get(), oldObject, 'value must be unchanged after illegal assignment');
  }

  public testSetV2ObservedObjectThrowsAndKeepsOldValue(): void {
    const subscriber = new NestedChildSubscriber(1011);
    const oldObject = { value: 1 };
    const property = this._makeProperty<Object>(oldObject, subscriber, 'objectLinkVar');
    let hasThrown = false;
    // make a plain object look like a V2 observed object to the checkIsObject guard
    const v2LikeObject = { valueV2: 1 };
    ObserveV2.IsObservedObjectV2 = (value: any): boolean => value === v2LikeObject;

    try {
      property.set(v2LikeObject);
    } catch (err) {
      hasThrown = true;
    }

    eq(hasThrown, true,
      'assigning a V2 @ObservedV2 object must throw BusinessError');
    eq(property.get(), oldObject, 'value must be unchanged after illegal assignment');

    // restore the stub to a safe default
    ObserveV2.IsObservedObjectV2 = (value: any): boolean => false;
  }

  public testSetEachChangeNotifiesAgain(): void {
    const subscriber = new NestedChildSubscriber(1012);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    property.set({ value: 2 });
    property.set({ value: 3 });
    property.set({ value: 4 });

    eq(subscriber.syncPeerCount, 3, 'each real change must notify subscribers');
    eq((property.get() as any).value, 4, 'get() must return the latest object');
  }

  // =========================================================================
  // SECTION 3: set tests with @Observed objects
  // =========================================================================

  public testSetObservedObjectRegistersAndUnregisters(): void {
    const subscriber = new NestedChildSubscriber(1013);
    const observedA = ObservedObject.createNew(new NestedObservedClassA(1), undefined as unknown as IPropertySubscriber);
    const observedB = ObservedObject.createNew(new NestedObservedClassB('x'), undefined as unknown as IPropertySubscriber);
    const property = this._makeProperty<Object>(observedA, subscriber, 'objectLinkVar');
    const countAAfterInit = ObservedObject.countSubscribers(observedA) as number;
    const countBBefore = ObservedObject.countSubscribers(observedB) as number;

    property.set(observedB);

    eq(ObservedObject.countSubscribers(observedA), countAAfterInit - 1,
      'old observed object must be unregistered');
    eq(ObservedObject.countSubscribers(observedB), countBBefore + 1,
      'new observed object must be registered');
    eq(property.get(), observedB, 'get() must return the new observed object');
  }

  public testSetSameObservedObjectDoesNotNotify(): void {
    const subscriber = new NestedChildSubscriber(1014);
    const observedObject = ObservedObject.createNew(new NestedObservedClassA(1), undefined as unknown as IPropertySubscriber);
    const property = this._makeProperty<NestedObservedClassA>(observedObject, subscriber, 'objectLinkVar');

    property.set(observedObject);

    eq(subscriber.syncPeerCount, 0,
      'setting the identical observed object must not notify subscribers');
  }

  public testSetPlainObjectAfterObservedObjectUnregisters(): void {
    const subscriber = new NestedChildSubscriber(1015);
    const observedObject = new NestedObservedClassA(1);
    const property = this._makeProperty<Object>(observedObject, subscriber, 'objectLinkVar');
    const countAfterInit = ObservedObject.countSubscribers(observedObject) as number;

    property.set({ value: 2 });

    eq(ObservedObject.countSubscribers(observedObject), countAfterInit - 1,
      'observed object must be unregistered when replaced by a plain object');
    eq(ObservedObject.IsObservedObject(property.get()), false,
      'get() must return the plain object');
  }

  // =========================================================================
  // SECTION 4: set tests with SubscribableAbstract values
  // =========================================================================

  public testConstructorRegistersOnSubscribableAbstract(): void {
    const subscriber = new NestedChildSubscriber(1016);
    const subscribable = new NestedTestSubscribable(1);

    this._makeProperty<Object>(subscribable, subscriber, 'objectLinkVar');

    eq(subscribable.numberOfSubscribers(), 1,
      'constructor must register the property on the SubscribableAbstract value');
  }

  public testSetSubscribableAbstractSwitchesRegistration(): void {
    const subscriber = new NestedChildSubscriber(1017);
    const subscribable1 = new NestedTestSubscribable(1);
    const subscribable2 = new NestedTestSubscribable(2);
    const property = this._makeProperty<Object>(subscribable1, subscriber, 'objectLinkVar');

    property.set(subscribable2);

    eq(subscribable1.numberOfSubscribers(), 0,
      'old SubscribableAbstract must be unregistered');
    eq(subscribable2.numberOfSubscribers(), 1,
      'new SubscribableAbstract must be registered');
    eq(property.get(), subscribable2, 'get() must return the new SubscribableAbstract');
  }

  public testSetSubscribableAbstractNotifiesOnce(): void {
    const subscriber = new NestedChildSubscriber(1018);
    const property = this._makeProperty<Object>(new NestedTestSubscribable(1), subscriber, 'objectLinkVar');

    property.set(new NestedTestSubscribable(2));

    eq(subscriber.syncPeerCount, 1,
      'switching SubscribableAbstract value must notify subscribers exactly once');
  }

  public testSetSameSubscribableAbstractDoesNotNotify(): void {
    const subscriber = new NestedChildSubscriber(1019);
    const subscribable = new NestedTestSubscribable(1);
    const property = this._makeProperty<Object>(subscribable, subscriber, 'objectLinkVar');

    property.set(subscribable);

    eq(subscriber.syncPeerCount, 0,
      'setting the identical SubscribableAbstract must not notify subscribers');
  }

  public testSetPlainObjectAfterSubscribableAbstractUnregisters(): void {
    const subscriber = new NestedChildSubscriber(1020);
    const subscribable = new NestedTestSubscribable(1);
    const property = this._makeProperty<Object>(subscribable, subscriber, 'objectLinkVar');

    property.set({ value: 2 });

    eq(subscribable.numberOfSubscribers(), 0,
      'SubscribableAbstract must be unregistered when replaced by a plain object');
  }

  // =========================================================================
  // SECTION 5: aboutToBeDeleted lifecycle tests
  // =========================================================================

  public testAboutToBeDeletedUnregistersFromSubscriberManager(): void {
    const subscriber = new NestedChildSubscriber(1021);
    const property = this._makeProperty<Object>({ value: 1 }, subscriber, 'objectLinkVar');

    property.aboutToBeDeleted();
    // avoid double cleanup for this property
    this.propertiesToCleanup_ = this.propertiesToCleanup_.filter(
      (item: SynchedPropertyNestedObjectPU<Object>) => item !== property);

    eq(SubscriberManager.Has(property.id__()), false,
      'aboutToBeDeleted must unregister the property from SubscriberManager');
  }

  public testAboutToBeDeletedUnregistersFromObservedObject(): void {
    const subscriber = new NestedChildSubscriber(1022);
    const observedObject = ObservedObject.createNew(new NestedObservedClassA(1), undefined as unknown as IPropertySubscriber);
    const property = this._makeProperty<NestedObservedClassA>(observedObject, subscriber, 'objectLinkVar');
    const countAfterInit = ObservedObject.countSubscribers(observedObject) as number;

    property.aboutToBeDeleted();
    this.propertiesToCleanup_ = this.propertiesToCleanup_.filter(
      (item: SynchedPropertyNestedObjectPU<Object>) => item !== property);

    eq(ObservedObject.countSubscribers(observedObject), countAfterInit - 1,
      'aboutToBeDeleted must unregister from the observed object');
  }

  public testAboutToBeDeletedUnregistersFromSubscribableAbstract(): void {
    const subscriber = new NestedChildSubscriber(1023);
    const subscribable = new NestedTestSubscribable(1);
    const property = this._makeProperty<Object>(subscribable, subscriber, 'objectLinkVar');

    property.aboutToBeDeleted();
    this.propertiesToCleanup_ = this.propertiesToCleanup_.filter(
      (item: SynchedPropertyNestedObjectPU<Object>) => item !== property);

    eq(subscribable.numberOfSubscribers(), 0,
      'aboutToBeDeleted must unregister from the SubscribableAbstract value');
  }

  // =========================================================================
  // SECTION 6: typo subclass SynchedPropertyNesedObjectPU tests
  // =========================================================================

  public testTypoSubclassIsInstanceOfBaseClass(): void {
    const subscriber = new NestedChildSubscriber(1024);
    const property = new SynchedPropertyNesedObjectPU<Object>({ value: 1 }, subscriber, 'objectLinkVar');
    this.propertiesToCleanup_.push(property as SynchedPropertyNestedObjectPU<Object>);

    eq(property instanceof SynchedPropertyNestedObjectPU, true,
      'SynchedPropertyNesedObjectPU must extend SynchedPropertyNestedObjectPU');
  }

  public testTypoSubclassConstructorAndGet(): void {
    const subscriber = new NestedChildSubscriber(1025);
    const observedObject = ObservedObject.createNew(new NestedObservedClassA(7), undefined as unknown as IPropertySubscriber);
    const property = new SynchedPropertyNesedObjectPU<NestedObservedClassA>(
      observedObject, subscriber, 'objectLinkVar');
    this.propertiesToCleanup_.push(property as SynchedPropertyNestedObjectPU<Object>);

    eq(property.get(), observedObject, 'get() must return the observed object');
    eq(SubscriberManager.Has(property.id__()), true,
      'typo subclass must register in SubscriberManager');
  }

  public testTypoSubclassSetNotifies(): void {
    const subscriber = new NestedChildSubscriber(1026);
    const property = new SynchedPropertyNesedObjectPU<Object>({ value: 1 }, subscriber, 'objectLinkVar');
    this.propertiesToCleanup_.push(property as SynchedPropertyNestedObjectPU<Object>);

    property.set({ value: 2 });

    eq(subscriber.syncPeerCount, 1, 'set() of typo subclass must notify subscribers');
    eq((property.get() as any).value, 2, 'get() must return the new value');
  }
}
