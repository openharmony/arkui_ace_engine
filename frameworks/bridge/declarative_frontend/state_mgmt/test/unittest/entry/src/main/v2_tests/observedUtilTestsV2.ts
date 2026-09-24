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

interface ObservedResult {
  isObserved: boolean;
  reason: string;
  decoratorInfo: Array<DecoratorInfo>;
}

interface DecoratorInfo {
  decoratorName: string;
  stateVariableName: string;
  owningComponentOrClassName: string;
  owningComponentId: number;
  dependentInfo: Array<Object>;
}

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class ObservedUtil {
  static canBeObserved<T extends Object>(source: T): ObservedResult;
}

declare class UIUtilsImpl {
  static instance(): UIUtilsImpl;
  canBeObserved<T extends Object>(source: T): ObservedResult;
  getTarget<T extends Object>(source: T): T;
  makeBinding<T>(getter: () => T): Binding<T>;
  makeBinding<T>(getter: () => T, setter: (newValue: T) => void): MutableBinding<T>;
}

declare class Binding<T> {
  constructor(getter: () => T);
  get value(): T;
}

declare class MutableBinding<T> {
  constructor(getter: () => T, setter: (newValue: T) => void);
  get value(): T;
  set value(newValue: T);
}

declare class ObservedObject {
  static IsObservedObject(obj: any): boolean;
  static createNew<T extends Object>(rawObject: T, owningProperty: any): T;
  static GetRawObject<T extends Object>(obj: T): T;
}

declare const ObservedV2: (target: any) => any;
declare const Trace: (target: any, propertyKey: string) => void;
declare const Local: (target: any, propertyKey: string) => void;

@ObservedV2
class ObservedUtilTraceClass {
  @Trace traceValue: number = 1;
  @Trace traceText: string = 'text';
}

@ObservedV2
class ObservedUtilLocalClass {
  @Local localValue: number = 2;
}

class ObservedUtilPlainClass {
  public plainValue: number = 3;
}

/**
 * ObservedUtil / UIUtilsImpl Unit Tests
 *
 * This test suite validates ObservedUtil.canBeObserved and UIUtilsImpl:
 * - canBeObserved for not observed data (plain object, primitive, null, collections)
 * - canBeObserved for V2 @ObservedV2 + @Trace / @Local class objects (no UI usage)
 * - canBeObserved for V1 ObservedObject (no UI usage)
 * - DecoratorInfo content for V2 observed objects
 * - UIUtilsImpl.instance singleton
 * - UIUtilsImpl.getTarget for plain, primitive and V1 proxied objects
 * - UIUtilsImpl.makeBinding Binding / MutableBinding factories
 */
export class ObservedUtilTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating ObservedUtilTestsV2: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('ObservedUtilTestsV2: Setting up test suite');
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
    console.log('ObservedUtilTestsV2: Tearing down test suite');
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1: canBeObserved for not observed data
  // =========================================================================

  public testCanBeObservedPlainObject(): void {
    const result = ObservedUtil.canBeObserved({ someProp: 1 });

    eq(result.isObserved, false, 'plain object can not be observed');
    eq(result.reason, 'The object data is not an observable object',
      'reason must report not observed');
    eq(result.decoratorInfo.length, 0, 'decoratorInfo must be empty');
  }

  public testCanBeObservedClassInstanceWithoutDecorator(): void {
    const result = ObservedUtil.canBeObserved(new ObservedUtilPlainClass());

    eq(result.isObserved, false, 'instance of a plain class can not be observed');
    eq(result.reason, 'The object data is not an observable object',
      'reason must report not observed');
    eq(result.decoratorInfo.length, 0, 'decoratorInfo must be empty');
  }

  public testCanBeObservedPrimitives(): void {
    const numberResult = ObservedUtil.canBeObserved(5 as unknown as Object);
    eq(numberResult.isObserved, false, 'number can not be observed');

    const stringResult = ObservedUtil.canBeObserved('text' as unknown as Object);
    eq(stringResult.isObserved, false, 'string can not be observed');

    const boolResult = ObservedUtil.canBeObserved(true as unknown as Object);
    eq(boolResult.isObserved, false, 'boolean can not be observed');
  }

  public testCanBeObservedNullAndUndefined(): void {
    const nullResult = ObservedUtil.canBeObserved(null as unknown as Object);
    eq(nullResult.isObserved, false, 'null can not be observed');

    const undefinedResult = ObservedUtil.canBeObserved(undefined as unknown as Object);
    eq(undefinedResult.isObserved, false, 'undefined can not be observed');
  }

  public testCanBeObservedPlainCollections(): void {
    const arrayResult = ObservedUtil.canBeObserved([1, 2, 3] as unknown as Object);
    eq(arrayResult.isObserved, false, 'plain Array can not be observed');

    const mapResult = ObservedUtil.canBeObserved(new Map<string, number>() as unknown as Object);
    eq(mapResult.isObserved, false, 'plain Map can not be observed');

    const setResult = ObservedUtil.canBeObserved(new Set<number>() as unknown as Object);
    eq(setResult.isObserved, false, 'plain Set can not be observed');

    const dateResult = ObservedUtil.canBeObserved(new Date(2026, 0, 1) as unknown as Object);
    eq(dateResult.isObserved, false, 'plain Date can not be observed');
  }

  // =========================================================================
  // SECTION 2: canBeObserved for V2 @ObservedV2 objects (no UI usage)
  // =========================================================================

  public testCanBeObservedV2TraceClass(): void {
    const result = ObservedUtil.canBeObserved(new ObservedUtilTraceClass());

    eq(result.isObserved, true, '@ObservedV2 + @Trace object can be observed');
    eq(result.reason,
      'The object data is decorated with V2 @ObservedV2 and @Trace, but not used in UI',
      'without UI dependency the V2_NO_UI reason must be reported');
  }

  public testCanBeObservedV2TraceDecoratorInfo(): void {
    const result = ObservedUtil.canBeObserved(new ObservedUtilTraceClass());

    eq(result.decoratorInfo.length, 2,
      'one DecoratorInfo entry per @Trace variable must be reported');
    const names = result.decoratorInfo
      .map((info: DecoratorInfo): string => info.stateVariableName).sort();
    eq(JSON.stringify(names), JSON.stringify(['traceText', 'traceValue']),
      'DecoratorInfo must list both @Trace variables');
    result.decoratorInfo.forEach((info: DecoratorInfo): void => {
      eq(info.decoratorName, '@Trace', 'decorator name must be @Trace');
      eq(info.owningComponentOrClassName, 'ObservedUtilTraceClass',
        'owning class name must be the @ObservedV2 class name');
      eq(info.owningComponentId, -1,
        'V2 decorator info always reports component id -1');
      eq(info.dependentInfo.length, 0,
        'no dependent elements without UI usage');
    });
  }

  public testCanBeObservedV2LocalClass(): void {
    const result = ObservedUtil.canBeObserved(new ObservedUtilLocalClass());

    eq(result.isObserved, true, '@ObservedV2 + @Local object can be observed');
    eq(result.decoratorInfo.length, 1,
      'one DecoratorInfo entry for the @Local variable');
    eq(result.decoratorInfo[0].decoratorName, '@Local', 'decorator name must be @Local');
    eq(result.decoratorInfo[0].stateVariableName, 'localValue',
      'state variable name must match');
    eq(result.decoratorInfo[0].owningComponentOrClassName, 'ObservedUtilLocalClass',
      'owning class name must be the @ObservedV2 class name');
  }

  public testCanBeObservedResultIsFreshObject(): void {
    const source = new ObservedUtilTraceClass();

    const first = ObservedUtil.canBeObserved(source);
    const second = ObservedUtil.canBeObserved(source);

    neq(first, second, 'each call must return a fresh result object');
    eq(first.isObserved, second.isObserved, 'results must be equal in content');
    eq(first.reason, second.reason, 'results must be equal in content');
  }

  // =========================================================================
  // SECTION 3: canBeObserved for V1 ObservedObject (no UI usage)
  // =========================================================================

  public testCanBeObservedV1ObservedObject(): void {
    const observed = ObservedObject.createNew(new ObservedUtilPlainClass(), undefined);

    eq(ObservedObject.IsObservedObject(observed), true,
      'precondition: createNew result is a V1 ObservedObject');

    const result = ObservedUtil.canBeObserved(observed);
    eq(result.isObserved, true, 'V1 ObservedObject can be observed');
    eq(result.reason,
      'The object data is decorated with @Observed or wrapped by makeV1Observed, but not used in UI',
      'without owning property and UI the V1_NO_UI reason must be reported');
  }

  public testCanBeObservedViaUIUtilsImplMatchesObservedUtil(): void {
    const v2Source = new ObservedUtilTraceClass();
    const viaUtils = UIUtilsImpl.instance().canBeObserved(v2Source);
    const direct = ObservedUtil.canBeObserved(v2Source);

    eq(viaUtils.isObserved, direct.isObserved, 'UIUtilsImpl must forward to ObservedUtil');
    eq(viaUtils.reason, direct.reason, 'UIUtilsImpl must forward to ObservedUtil');
    eq(viaUtils.decoratorInfo.length, direct.decoratorInfo.length,
      'UIUtilsImpl must forward to ObservedUtil');

    const plainResult = UIUtilsImpl.instance().canBeObserved({ value: 1 });
    eq(plainResult.isObserved, false, 'plain object via UIUtilsImpl can not be observed');
  }

  // =========================================================================
  // SECTION 4: UIUtilsImpl.instance singleton tests
  // =========================================================================

  public testUIUtilsImplInstanceIsSingleton(): void {
    const first = UIUtilsImpl.instance();
    const second = UIUtilsImpl.instance();

    eq(first, second, 'instance() must always return the same singleton');
    neq(first, undefined, 'instance() must never return undefined');
  }

  // =========================================================================
  // SECTION 5: UIUtilsImpl.getTarget tests
  // =========================================================================

  public testGetTargetReturnsPlainObjectItself(): void {
    const plain = { value: 1 };

    eq(UIUtilsImpl.instance().getTarget(plain), plain,
      'getTarget must return the plain object itself');
  }

  public testGetTargetReturnsNullAndPrimitivesAsIs(): void {
    eq(UIUtilsImpl.instance().getTarget(null as unknown as Object), null,
      'getTarget must return null as-is');
    eq(UIUtilsImpl.instance().getTarget(5 as unknown as Object), 5,
      'getTarget must return a primitive as-is');
    eq(UIUtilsImpl.instance().getTarget('text' as unknown as Object), 'text',
      'getTarget must return a string as-is');
  }

  public testGetTargetUnwrapsV1ObservedObject(): void {
    const raw = new ObservedUtilPlainClass();
    const observed = ObservedObject.createNew(raw, undefined);

    neq(observed, raw, 'precondition: proxy must differ from raw object');
    const target = UIUtilsImpl.instance().getTarget(observed);

    eq(target, raw, 'getTarget must return the raw object inside the V1 proxy');
    eq(target, ObservedObject.GetRawObject(observed),
      'getTarget must match ObservedObject.GetRawObject');
    eq((target as ObservedUtilPlainClass).plainValue, 3,
      'unwrapped object must give access to raw properties');
  }

  public testGetTargetV2ObservedObject(): void {
    const v2Source = new ObservedUtilTraceClass();

    // a @ObservedV2 class instance is not a V1 proxy:
    // getTarget returns it unchanged (no V2 collection proxy involved)
    eq(UIUtilsImpl.instance().getTarget(v2Source), v2Source,
      'getTarget must return the @ObservedV2 class instance itself');
  }

  // =========================================================================
  // SECTION 6: UIUtilsImpl.makeBinding tests
  // =========================================================================

  public testMakeBindingGetterOnlyReturnsBinding(): void {
    let stored = 10;
    const binding = UIUtilsImpl.instance().makeBinding((): number => stored);

    neq(binding, undefined, 'makeBinding must return a Binding');
    eq(binding.value, 10, 'value must come from the getter');

    stored = 20;
    eq(binding.value, 20, 'value must always re-evaluate the getter');
  }

  public testMakeBindingWithSetterReturnsMutableBinding(): void {
    let stored = 1;
    let setterCalls = 0;
    const mutable = UIUtilsImpl.instance().makeBinding(
      (): number => stored,
      (newValue: number): void => { stored = newValue; setterCalls++; });

    neq(mutable, undefined, 'makeBinding must return a MutableBinding');
    eq(mutable.value, 1, 'value must come from the getter');

    mutable.value = 5;
    eq(setterCalls, 1, 'assignment must call the setter exactly once');
    eq(stored, 5, 'assignment must store the new value');
    eq(mutable.value, 5, 'reading after write must reflect the new value');
  }

  public testMakeBindingMultipleWrites(): void {
    let stored = 0;
    const mutable = UIUtilsImpl.instance().makeBinding(
      (): number => stored,
      (newValue: number): void => { stored = newValue; });

    mutable.value = 1;
    mutable.value = 2;
    mutable.value = 3;

    eq(stored, 3, 'last write must win');
    eq(mutable.value, 3, 'reading must reflect the last write');
  }

  public testMakeBindingReturnsIndependentInstances(): void {
    const first = UIUtilsImpl.instance().makeBinding((): number => 1);
    const second = UIUtilsImpl.instance().makeBinding((): number => 2);

    neq(first, second, 'each makeBinding call must return a new instance');
    eq(first.value, 1, 'first binding keeps its own getter');
    eq(second.value, 2, 'second binding keeps its own getter');
  }

  public testMakeBindingObjectValue(): void {
    const obj = { key: 'value' };
    const binding = UIUtilsImpl.instance().makeBinding((): Object => obj);

    eq(binding.value, obj, 'object references must pass through the binding');
  }
}
