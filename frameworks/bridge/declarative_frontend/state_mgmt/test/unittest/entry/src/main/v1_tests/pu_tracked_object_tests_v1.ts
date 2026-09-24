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

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class TrackedObject {
  static readonly ___IS_TRACKED_OPTIMISED: string;
  static readonly ___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY: string;
  static readonly ___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY: string;
  static readonly ___TRACKED_PREFIX: string;
  static isCompatibilityMode(obj: Object): boolean;
  static needsPropertyReadCb(obj: Object): boolean;
  static notifyObjectValueAssignment(obj1: Object, obj2: Object,
    notifyPropertyChanged: (isFromSource: boolean) => void,
    notifyTrackedPropertyChange: (propName: string) => void,
    obSelf: Object): boolean;
}

// @Track class property decorator
declare function Track(target: Object, property: string): void;

declare class ObservedObject {
  static GetRawObject<T extends Object>(obj: T): T;
}

/** test class with properties used in @Track optimisation tests */
class TrackTestClass {
  public propA: number = 0;
  public propB: number = 0;
  public propC: number = 0;

  constructor(propA: number = 0, propB: number = 0, propC: number = 0) {
    this.propA = propA;
    this.propB = propB;
    this.propC = propC;
  }
}

/** another class, used to test constructor mismatch in notifyObjectValueAssignment */
class OtherTrackTestClass {
  public propA: number = 0;

  constructor(propA: number = 0) {
    this.propA = propA;
  }
}

/**
 * TrackedObject / Track decorator Unit Tests
 *
 * This test suite validates TrackedObject functionality:
 * - Protocol constant values
 * - Track decorator: marking properties and the optimised flag
 * - isCompatibilityMode
 * - needsPropertyReadCb
 * - notifyObjectValueAssignment non-optimised path
 * - notifyObjectValueAssignment optimised path
 */
export class PuTrackedObjectTestsV1 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating PuTrackedObjectTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('PuTrackedObjectTestsV1: Setting up test suite');
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
    console.log('PuTrackedObjectTestsV1: Tearing down test suite');
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // helper: object with @Track'ed propA and propB
  private _makeTrackedObject(propA: number, propB: number, propC: number): TrackTestClass {
    const obj = new TrackTestClass(propA, propB, propC);
    Track(obj, 'propA');
    Track(obj, 'propB');
    return obj;
  }

  // =========================================================================
  // SECTION 1: protocol constants tests
  // =========================================================================

  public testProtocolConstantsHaveExpectedValues(): void {
    eq(TrackedObject.___IS_TRACKED_OPTIMISED, '___IS_TRACKED_OPTIMISED',
      'optimised mode flag property name');
    eq(TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY,
      '___OPTI_TRACKED_ASSIGNMENT_FAKE_PROP_PROPERTY',
      '@Prop assignment fake property name');
    eq(TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY,
      '___OPTI_TRACKED_ASSIGNMENT_FAKE_OBJLINK_PROPERTY',
      '@ObjectLink assignment fake property name');
    eq(TrackedObject.___TRACKED_PREFIX, '___TRACKED_',
      '@Track property prefix');
  }

  // =========================================================================
  // SECTION 2: Track decorator tests
  // =========================================================================

  public testTrackMarksPropertyAsTracked(): void {
    const obj = new TrackTestClass();

    Track(obj, 'propA');

    eq(Reflect.get(obj, `${TrackedObject.___TRACKED_PREFIX}propA`), true,
      'Track must set the ___TRACKED_<property> marker to true');
  }

  public testTrackSetsOptimisedModeFlag(): void {
    const obj = new TrackTestClass();
    eq(TrackedObject.isCompatibilityMode(obj), true,
      'precondition: plain object is in compatibility mode');

    Track(obj, 'propA');

    eq(Reflect.get(obj, TrackedObject.___IS_TRACKED_OPTIMISED), true,
      'Track must set the optimised mode flag to true');
    eq(TrackedObject.isCompatibilityMode(obj), false,
      'object with @Track is no longer in compatibility mode');
  }

  public testTrackSecondPropertyKeepsFlags(): void {
    const obj = new TrackTestClass();
    Track(obj, 'propA');

    Track(obj, 'propB');

    eq(Reflect.get(obj, `${TrackedObject.___TRACKED_PREFIX}propA`), true,
      'first @Track marker must remain');
    eq(Reflect.get(obj, `${TrackedObject.___TRACKED_PREFIX}propB`), true,
      'second @Track marker must be set');
    eq(Reflect.get(obj, TrackedObject.___IS_TRACKED_OPTIMISED), true,
      'optimised flag must remain set');
  }

  public testTrackDoesNotChangePropertyValue(): void {
    const obj = new TrackTestClass(11, 22, 33);

    Track(obj, 'propA');

    eq(obj.propA, 11, 'Track must not modify the property value itself');
    eq(obj.propB, 22, 'Track must not modify other property values');
  }

  // =========================================================================
  // SECTION 3: isCompatibilityMode tests
  // =========================================================================

  public testIsCompatibilityModeForNullAndUndefined(): void {
    eq(TrackedObject.isCompatibilityMode(null as unknown as Object), true,
      'null is treated as compatibility mode');
    eq(TrackedObject.isCompatibilityMode(undefined as unknown as Object), true,
      'undefined is treated as compatibility mode');
  }

  public testIsCompatibilityModeForNonObjects(): void {
    eq(TrackedObject.isCompatibilityMode(5 as unknown as Object), true,
      'number is treated as compatibility mode');
    eq(TrackedObject.isCompatibilityMode('text' as unknown as Object), true,
      'string is treated as compatibility mode');
  }

  public testIsCompatibilityModeForPlainObject(): void {
    const obj = new TrackTestClass();

    eq(TrackedObject.isCompatibilityMode(obj), true,
      'object without any @Track property is in compatibility mode');
  }

  public testIsCompatibilityModeForTrackedObject(): void {
    const obj = this._makeTrackedObject(1, 2, 3);

    eq(TrackedObject.isCompatibilityMode(obj), false,
      'object with @Track property is not in compatibility mode');
  }

  // =========================================================================
  // SECTION 4: needsPropertyReadCb tests
  // =========================================================================

  public testNeedsPropertyReadCbForNullAndNonObjects(): void {
    eq(TrackedObject.needsPropertyReadCb(null as unknown as Object), false,
      'null never needs a property read callback');
    eq(TrackedObject.needsPropertyReadCb(5 as unknown as Object), false,
      'number never needs a property read callback');
  }

  public testNeedsPropertyReadCbForPlainObject(): void {
    const obj = new TrackTestClass();

    eq(TrackedObject.needsPropertyReadCb(obj), false,
      'object in compatibility mode does not need a property read callback');
  }

  public testNeedsPropertyReadCbForTrackedObject(): void {
    const obj = this._makeTrackedObject(1, 2, 3);

    eq(TrackedObject.needsPropertyReadCb(obj), true,
      '@Track optimised object needs a property read callback');
  }

  // =========================================================================
  // SECTION 5: notifyObjectValueAssignment non-optimised path tests
  // =========================================================================

  public testNotifyNullOldValueUsesNonOptimisedPath(): void {
    let assignmentNotifyCount = 0;
    const trackedNotifyNames: string[] = [];
    const newValue = this._makeTrackedObject(1, 2, 3);

    const result = TrackedObject.notifyObjectValueAssignment(null as unknown as Object, newValue,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(result, false, 'must report non-optimised notification');
    eq(assignmentNotifyCount, 1, 'assignment notification must be sent exactly once');
    eq(trackedNotifyNames.length, 0, 'no per-property notification in non-optimised path');
  }

  public testNotifyUndefinedNewValueUsesNonOptimisedPath(): void {
    let assignmentNotifyCount = 0;
    const oldValue = this._makeTrackedObject(1, 2, 3);

    const result = TrackedObject.notifyObjectValueAssignment(oldValue, undefined as unknown as Object,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => {},
      this);

    eq(result, false, 'must report non-optimised notification');
    eq(assignmentNotifyCount, 1, 'assignment notification must be sent exactly once');
  }

  public testNotifyNonObjectsUseNonOptimisedPath(): void {
    let assignmentNotifyCount = 0;

    const result = TrackedObject.notifyObjectValueAssignment(1 as unknown as Object, 2 as unknown as Object,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => {},
      this);

    eq(result, false, 'must report non-optimised notification');
    eq(assignmentNotifyCount, 1, 'assignment notification must be sent exactly once');
  }

  public testNotifyDifferentConstructorsUseNonOptimisedPath(): void {
    let assignmentNotifyCount = 0;
    const trackedNotifyNames: string[] = [];
    const obj1 = new OtherTrackTestClass(1);
    Track(obj1, 'propA');
    const obj2 = this._makeTrackedObject(1, 2, 3);

    const result = TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(result, false, 'constructor mismatch must use non-optimised path');
    eq(assignmentNotifyCount, 1, 'assignment notification must be sent exactly once');
    eq(trackedNotifyNames.length, 0, 'no per-property notification in non-optimised path');
  }

  public testNotifyCompatibilityModeObjectsUseNonOptimisedPath(): void {
    let assignmentNotifyCount = 0;
    const trackedNotifyNames: string[] = [];
    // same class, different values, but no @Track markers -> compatibility mode
    const obj1 = new TrackTestClass(1, 2, 3);
    const obj2 = new TrackTestClass(4, 5, 6);

    const result = TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(result, false, 'compatibility mode must use non-optimised path');
    eq(assignmentNotifyCount, 1, 'assignment notification must be sent exactly once');
    eq(trackedNotifyNames.length, 0, 'no per-property notification in non-optimised path');
  }

  // =========================================================================
  // SECTION 6: notifyObjectValueAssignment optimised path tests
  // =========================================================================

  public testNotifyOptimisedNoValueChangedNotifiesOnlyObjectLinkFakeProperty(): void {
    let assignmentNotifyCount = 0;
    const trackedNotifyNames: string[] = [];
    const obj1 = this._makeTrackedObject(1, 2, 3);
    const obj2 = this._makeTrackedObject(1, 2, 3);

    const result = TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(result, true, 'must report optimised notification');
    eq(assignmentNotifyCount, 0, 'no assignment notification in optimised path');
    eq(trackedNotifyNames.length, 1,
      'only the @ObjectLink fake property must be notified when nothing changed');
    eq(trackedNotifyNames[0], TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY,
      'the @ObjectLink fake property must be notified');
  }

  public testNotifyOptimisedTrackedPropertyChanged(): void {
    let assignmentNotifyCount = 0;
    const trackedNotifyNames: string[] = [];
    const obj1 = this._makeTrackedObject(1, 2, 3);
    const obj2 = this._makeTrackedObject(9, 2, 3); // propA changed

    const result = TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => { assignmentNotifyCount++; },
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(result, true, 'must report optimised notification');
    eq(assignmentNotifyCount, 0, 'no assignment notification in optimised path');
    eq(trackedNotifyNames.includes('propA'), true, 'changed @Track property must be notified');
    eq(trackedNotifyNames.includes(TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY), true,
      '@Prop fake property must be notified when a tracked property changed');
    eq(trackedNotifyNames.includes(TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY), true,
      '@ObjectLink fake property is always notified in optimised path');
    eq(trackedNotifyNames.length, 3, 'exactly propA + both fake properties must be notified');
  }

  public testNotifyOptimisedUntrackedPropertyChangedNotifiesOnlyObjectLink(): void {
    const trackedNotifyNames: string[] = [];
    const obj1 = this._makeTrackedObject(1, 2, 3);
    const obj2 = this._makeTrackedObject(1, 2, 9); // only propC (not @Track'ed) changed

    const result = TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => {},
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(result, true, 'must report optimised notification');
    eq(trackedNotifyNames.length, 1,
      'unchanged/untracked properties must not be notified');
    eq(trackedNotifyNames[0], TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY,
      'only the @ObjectLink fake property must be notified');
    eq(trackedNotifyNames.includes(TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY), false,
      '@Prop fake property must not be notified without tracked property change');
  }

  public testNotifyOptimisedMultipleTrackedPropertiesChanged(): void {
    const trackedNotifyNames: string[] = [];
    const obj1 = this._makeTrackedObject(1, 2, 3);
    const obj2 = this._makeTrackedObject(9, 8, 3); // propA and propB changed

    TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => {},
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(trackedNotifyNames.includes('propA'), true, 'changed @Track propA must be notified');
    eq(trackedNotifyNames.includes('propB'), true, 'changed @Track propB must be notified');
    eq(trackedNotifyNames.length, 4,
      'propA + propB + both fake properties must be notified');
  }

  public testNotifyOptimisedNewValueChangedBackNotifiesNothing(): void {
    const trackedNotifyNames: string[] = [];
    const obj1 = this._makeTrackedObject(1, 2, 3);
    const obj2 = this._makeTrackedObject(1, 2, 3);
    // same values: no tracked property changed

    TrackedObject.notifyObjectValueAssignment(obj1, obj2,
      (): void => {},
      (propName: string): void => { trackedNotifyNames.push(propName); },
      this);

    eq(trackedNotifyNames.includes(TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY), false,
      '@Prop fake property must not be notified when no tracked value changed');
  }
}
