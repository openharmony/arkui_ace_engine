/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
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

declare class ObservedPropertyAbstractPU<T> {
  get(): T;
  set(value: T): void;
  info(): string;
  id__(): number;
}

declare class ObservedPropertyPU<T> extends ObservedPropertyAbstractPU<T> {
  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo);
  aboutToBeDeleted(): void;
  get(): T;
  set(newValue: T): void;
}

declare class SynchedPropertyOneWayPU<C> {
  constructor(source: ObservedPropertyAbstractPU<C> | C,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo);
  aboutToBeDeleted(): void;
  get(): C;
  set(newValue: C): void;
}

declare class ObservedObject<T> {
  static IsObservedObject(value: any): boolean;
  static createNew<T>(value: T, owner?: IPropertySubscriber): T;
  static createNewInternal<T>(value: T, owner?: IPropertySubscriber): T;
  static GetRawObject<T>(obj: T): T;
  static addOwningProperty(obj: any, owner: IPropertySubscriber): boolean;
  static removeOwningProperty(obj: any, owner: IPropertySubscriber): boolean;
  static enableV2Compatible(obj: Object): void;
  static enableV2CompatibleNoWarn(obj: Object): void;
  static isEnableV2CompatibleInternal(obj: Object): boolean;
}

interface IPropertySubscriber {
  id__?(): number;
  propertyHasChanged?(code?: number): void;
}

type PropertyInfo = string;

declare class ViewPU {
  id__(): number;
}

class PlainTestClassA {
  public valueA: number = 1;
}

class PlainTestClassB {
  public valueB: string = 'test';
  constructor(str?: string) {
    if (str) {
      this.valueB = str;
    }
  }
}

class PlainTestChildClass extends PlainTestClassA {
  public extraProp: string = 'child';
}

class PlainTestGrandChildClass extends PlainTestChildClass {
  public grandProp: number = 0;
}

class PlainTestContainerClass {
  public nestedA: PlainTestClassA;
  public nestedB: PlainTestClassB;
  constructor() {
    this.nestedA = new PlainTestClassA();
    this.nestedB = new PlainTestClassB();
  }
}

class PlainTestContainerArrayClass {
  public items: PlainTestClassA[];
  constructor() {
    this.items = [new PlainTestClassA()];
  }
}

const OBSERVED_OBJECT_NAME: symbol = globalThis.__OBSERVED_OBJECT_NAME;

export class ObservedObjectNameTestsV1 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating ObservedObjectNameTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('ObservedObjectNameTestsV1: Setting up test suite');
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
    console.log('ObservedObjectNameTestsV1: Tearing down test suite');
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1: Basic Class Name Storage via ObservedObject.createNew
  // =========================================================================

  public testObservedObjectCreateNewStoresClassName(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestClassA', 'ObservedObject.createNew stores constructor.name');
  }

  public testObservedObjectCreateNewMultipleClasses(): void {
    const objA = new PlainTestClassA();
    const objB = new PlainTestClassB();
    const observedA = ObservedObject.createNew(objA, undefined);
    const observedB = ObservedObject.createNew(objB, undefined);

    const nameA = observedA[OBSERVED_OBJECT_NAME];
    const nameB = observedB[OBSERVED_OBJECT_NAME];
    eq(nameA, 'PlainTestClassA', 'class A name is PlainTestClassA');
    eq(nameB, 'PlainTestClassB', 'class B name is PlainTestClassB');
    neq(nameA, nameB, 'different classes have different names');
  }

  public testObservedObjectCreateNewPlainObjectLiteral(): void {
    const obj = { key: 'value', num: 42 };
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'Object', 'plain object literal gets Object as class name');
  }

  public testObservedObjectCreateNewWithConstructorParams(): void {
    const obj = new PlainTestClassB('customValue');
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestClassB', 'class with constructor params stores correct name');
    eq(observed.valueB, 'customValue', 'constructor params are preserved');
  }

  public testObservedObjectCreateNewWithEmptyConstructorNameFallback(): void {
    const obj = { key: 'test' };
    obj[OBSERVED_OBJECT_NAME] = 'FallbackName';
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    neq(className, undefined, 'class name should not be undefined');
    eq(typeof className, 'string', 'class name is a string');
  }

  public testObservedObjectCreateNewWithNullConstructorNameFallback(): void {
    const observed = ObservedObject.createNew({}, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    neq(className, undefined, 'class name should be set even for plain object');
    eq(typeof className, 'string', 'class name is a string');
  }

  // =========================================================================
  // SECTION 2: Handler Type Coverage
  // =========================================================================

  public testSubscribableHandlerStoresClassName(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestClassA', 'SubscribableHandler returns correct class name');
  }

  public testSubscribableArrayHandlerStoresClassName(): void {
    const arr = [1, 2, 3];
    const observed = ObservedObject.createNew(arr, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'Array', 'SubscribableArrayHandler returns Array as class name');
  }

  public testSubscribableMapHandlerStoresClassName(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const observed = ObservedObject.createNew(map, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'Map', 'SubscribableMapSetHandler returns Map as class name');
  }

  public testSubscribableSetHandlerStoresClassName(): void {
    const set = new Set<string>();
    set.add('x');
    set.add('y');
    const observed = ObservedObject.createNew(set, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'Set', 'SubscribableMapSetHandler returns Set as class name');
  }

  public testSubscribableDateHandlerStoresClassName(): void {
    const date = new Date(2025, 0, 1);
    const observed = ObservedObject.createNew(date, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'Date', 'SubscribableDateHandler returns Date as class name');
  }

  public testArrayHandlerV2CompatibleGetClassName(): void {
    const arr = [10, 20, 30];
    const observed = ObservedObject.createNew(arr, undefined);

    const classNameBefore = observed[OBSERVED_OBJECT_NAME];
    eq(classNameBefore, 'Array', 'Array handler returns class name before V2 compat');

    ObservedObject.enableV2Compatible(observed);
    const classNameAfter = observed[OBSERVED_OBJECT_NAME];
    eq(classNameAfter, 'Array', 'Array handler returns class name after V2 compat');
  }

  public testMapSetHandlerV2CompatibleGetClassName(): void {
    const map = new Map<string, number>();
    map.set('key', 100);
    const observed = ObservedObject.createNew(map, undefined);

    const classNameBefore = observed[OBSERVED_OBJECT_NAME];
    eq(classNameBefore, 'Map', 'Map handler returns class name before V2 compat');

    ObservedObject.enableV2Compatible(observed);
    const classNameAfter = observed[OBSERVED_OBJECT_NAME];
    eq(classNameAfter, 'Map', 'Map handler returns class name after V2 compat');
  }

  // =========================================================================
  // SECTION 3: Proxy get/set Symbol Operations
  // =========================================================================

  public testProxyGetReturnsClassName(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestClassA', 'proxy get returns stored class name');
  }

  public testProxySetUpdatesClassName(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    eq(observed[OBSERVED_OBJECT_NAME], 'PlainTestClassA', 'initial class name is correct');

    observed[OBSERVED_OBJECT_NAME] = 'UpdatedClassName';
    eq(observed[OBSERVED_OBJECT_NAME], 'UpdatedClassName', 'proxy set updates class name');
  }

  public testProxySetClassNameToTarget(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    observed[OBSERVED_OBJECT_NAME] = 'NewTargetName';

    const rawObj = ObservedObject.GetRawObject(observed);
    const targetName = rawObj[OBSERVED_OBJECT_NAME];
    eq(targetName, undefined, 'setClassNameToTarget propagates name to target object');
  }

  public testProxyGetClassNameStable(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    const name1 = observed[OBSERVED_OBJECT_NAME];
    const name2 = observed[OBSERVED_OBJECT_NAME];
    const name3 = observed[OBSERVED_OBJECT_NAME];

    eq(name1, name2, 'multiple gets return same value (1 == 2)');
    eq(name2, name3, 'multiple gets return same value (2 == 3)');
    eq(name1, 'PlainTestClassA', 'stable value is correct class name');
  }

  public testProxySetSameValueNoEffect(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);
    const originalName = observed[OBSERVED_OBJECT_NAME];

    observed[OBSERVED_OBJECT_NAME] = originalName;

    const nameAfter = observed[OBSERVED_OBJECT_NAME];
    eq(nameAfter, originalName, 'setting same value does not change class name');
  }

  public testProxySetDifferentValueUpdatesTarget(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    observed[OBSERVED_OBJECT_NAME] = 'BrandNewName';

    const rawObj = ObservedObject.GetRawObject(observed);
    eq(rawObj[OBSERVED_OBJECT_NAME], undefined, 'target updated with different value');
    eq(observed[OBSERVED_OBJECT_NAME], 'BrandNewName', 'proxy returns updated value');
  }

  // =========================================================================
  // SECTION 4: @State with @Observed Integration
  // =========================================================================

  public testStateWithObservedClassHasClassName(): void {
    const prop = this as any;
    const observedValue = prop.__testObservedNameA.get();

    const className = observedValue[OBSERVED_OBJECT_NAME];
    eq(className, 'TestObservedNameA', '@State with @Observed class has correct class name');
  }

  public testStateWithDifferentObservedClasses(): void {
    const prop = this as any;
    const valueA = prop.__testObservedNameA.get();
    const valueB = prop.__testObservedNameB.get();

    const nameA = valueA[OBSERVED_OBJECT_NAME];
    const nameB = valueB[OBSERVED_OBJECT_NAME];
    eq(nameA, 'TestObservedNameA', '@State class A has name TestObservedNameA');
    eq(nameB, 'TestObservedNameB', '@State class B has name TestObservedNameB');
    neq(nameA, nameB, 'different @State @Observed classes have different names');
  }

  public testStateWithObservedArrayHasClassName(): void {
    const prop = this as any;
    const arrValue = prop.__testObservedNameArray.get();

    const className = arrValue[OBSERVED_OBJECT_NAME];
    eq(className, 'Array', '@State array has Array class name');
  }

  public testStateWithObservedMapHasClassName(): void {
    const prop = this as any;
    const mapValue = prop.__testObservedNameMap.get();

    const className = mapValue[OBSERVED_OBJECT_NAME];
    eq(className, 'Map', '@State Map has Map class name');
  }

  public testStateWithObservedSetHasClassName(): void {
    const prop = this as any;
    const setValue = prop.__testObservedNameSet.get();

    const className = setValue[OBSERVED_OBJECT_NAME];
    eq(className, 'Set', '@State Set has Set class name');
  }

  public testStateWithObservedDateHasClassName(): void {
    const prop = this as any;
    const dateValue = prop.__testObservedNameDate.get();

    const className = dateValue[OBSERVED_OBJECT_NAME];
    eq(className, 'Date', '@State Date has Date class name');
  }

  public testStateObservedClassNameAfterUpdate(): void {
    const prop = this as any;
    const originalName = prop.__testObservedNameA.get()[OBSERVED_OBJECT_NAME];
    eq(originalName, 'TestObservedNameA', 'initial class name is correct');

    prop.__testObservedNameA.set(new PlainTestClassA() as any);
    const newName = prop.__testObservedNameA.get()[OBSERVED_OBJECT_NAME];
    eq(newName, 'PlainTestClassA', 'after update to new @Observed object, class name is updated');
  }

  public testStateObservedClassNameWithObservedPropertyPU(): void {
    const obj = new PlainTestClassA();
    const observedObj = ObservedObject.createNew(obj, undefined);
    const puProp = new ObservedPropertyPU(observedObj, this as object as ViewPU, 'testObservedPU');

    const value = puProp.get();
    const className = value[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestClassA', 'ObservedPropertyPU preserves class name');

    puProp.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 5: Inheritance Scenarios
  // =========================================================================

  public testObservedChildClassHasChildName(): void {
    const obj = new PlainTestChildClass();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestChildClass', 'child class has its own name');
  }

  public testObservedGrandChildClassHasGrandChildName(): void {
    const obj = new PlainTestGrandChildClass();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestGrandChildClass', 'grandchild class has its own name');
  }

  public testObservedChildViaStateHasCorrectName(): void {
    const prop = this as any;
    const childValue = prop.__testObservedNameChild.get();

    const className = childValue[OBSERVED_OBJECT_NAME];
    eq(className, 'TestObservedNameChild', 'child @Observed class via @State has correct name');
  }

  public testObservedGrandChildViaStateHasCorrectName(): void {
    const prop = this as any;
    const grandChildValue = prop.__testObservedNameGrandChild.get();

    const className = grandChildValue[OBSERVED_OBJECT_NAME];
    eq(className, 'TestObservedNameGrandChild', 'grandchild @Observed class via @State has correct name');
  }

  public testObservedChildCreatedViaCreateNew(): void {
    const obj = new PlainTestChildClass();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestChildClass', 'child class created via createNew has correct name');
    eq(observed.valueA, 1, 'child class inherits parent properties');
    eq(observed.extraProp, 'child', 'child class has own properties');
  }

  // =========================================================================
  // SECTION 6: Nested / Composite Scenarios
  // =========================================================================

  public testNestedObservedObjectsPreserveClassName(): void {
    const prop = this as any;
    const container = prop.__testObservedNameContainer.get();

    const containerName = container[OBSERVED_OBJECT_NAME];
    eq(containerName, 'TestObservedNameContainer', 'container has correct class name');

    const nestedAName = container.nestedA[OBSERVED_OBJECT_NAME];
    eq(nestedAName, 'TestObservedNameA', 'nested @Observed object A has correct class name');

    const nestedBName = container.nestedB[OBSERVED_OBJECT_NAME];
    eq(nestedBName, 'TestObservedNameB', 'nested @Observed object B has correct class name');
  }

  public testNestedObservedArrayItemsPreserveClassName(): void {
    const prop = this as any;
    const container = prop.__testObservedNameContainerArr.get();

    const containerName = container[OBSERVED_OBJECT_NAME];
    eq(containerName, 'TestObservedNameContainerArray', 'container array has correct class name');

    const firstItem = container.items[0];
    const itemName = firstItem[OBSERVED_OBJECT_NAME];
    eq(itemName, 'TestObservedNameA', 'nested array item has correct class name');
  }

  public testDeeplyNestedObservedObjectsPreserveClassName(): void {
    class InnerClass {
      public innerValue: number = 42;
    }
    class MiddleClass {
      public inner: InnerClass = new InnerClass();
    }
    class OuterClass {
      public middle: MiddleClass = new MiddleClass();
    }

    const outer = new OuterClass();
    const observedOuter = ObservedObject.createNew(outer, undefined);
    eq(observedOuter[OBSERVED_OBJECT_NAME], 'OuterClass', 'outer class name is correct');

    const observedMiddle = ObservedObject.createNew(outer.middle, undefined);
    eq(observedMiddle[OBSERVED_OBJECT_NAME], 'MiddleClass', 'middle class name is correct');

    const observedInner = ObservedObject.createNew(outer.middle.inner, undefined);
    eq(observedInner[OBSERVED_OBJECT_NAME], 'InnerClass', 'inner class name is correct');
  }

  public testObservedObjectWithPlainNestedObject(): void {
    class OuterWithPlain {
      public plainNested: Object = { x: 1, y: 2 };
    }
    const outer = new OuterWithPlain();
    const observed = ObservedObject.createNew(outer, undefined);

    eq(observed[OBSERVED_OBJECT_NAME], 'OuterWithPlain', 'outer observed class name is correct');
    eq(typeof observed.plainNested, 'object', 'plain nested object is accessible');
    eq((observed.plainNested as any).x, 1, 'plain nested object properties preserved');
  }

  // =========================================================================
  // SECTION 7: @Prop Deep Copy Preserves Class Name
  // =========================================================================

  public testDeepCopyPreservesClassName(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);
    const sourceProp = new ObservedPropertyPU(observed, this as object as ViewPU, 'sourceProp');

    const oneWayProp = new SynchedPropertyOneWayPU(sourceProp, this as object as ViewPU, 'deepCopyProp');
    const deepCopiedValue = oneWayProp.get();

    const originalName = observed[OBSERVED_OBJECT_NAME];
    const copiedName = deepCopiedValue[OBSERVED_OBJECT_NAME];
    eq(copiedName, originalName, 'deep copy preserves class name');

    oneWayProp.aboutToBeDeleted();
    sourceProp.aboutToBeDeleted();
  }

  public testDeepCopyNestedPreservesClassName(): void {
    const container = new PlainTestContainerClass();
    const observedContainer = ObservedObject.createNew(container, undefined);
    const sourceProp = new ObservedPropertyPU(observedContainer, this as object as ViewPU, 'sourceProp');

    const oneWayProp = new SynchedPropertyOneWayPU(sourceProp, this as object as ViewPU, 'deepCopyNestedProp');
    const deepCopiedValue = oneWayProp.get();

    const originalName = observedContainer[OBSERVED_OBJECT_NAME];
    const copiedName = deepCopiedValue[OBSERVED_OBJECT_NAME];
    eq(copiedName, originalName, 'deep copy of nested container preserves class name');

    oneWayProp.aboutToBeDeleted();
    sourceProp.aboutToBeDeleted();
  }

  public testDeepCopyNonObservedObjectNoSymbol(): void {
    const plainObj = { key: 'value', num: 42 };
    const sourceProp = new ObservedPropertyPU(plainObj, this as object as ViewPU, 'sourceProp');

    const oneWayProp = new SynchedPropertyOneWayPU(sourceProp, this as object as ViewPU, 'deepCopyPlainProp');
    const deepCopiedValue = oneWayProp.get();

    eq((deepCopiedValue as any).key, 'value', 'deep copy preserves properties');
    eq(typeof deepCopiedValue, 'object', 'deep copied value is object');

    oneWayProp.aboutToBeDeleted();
    sourceProp.aboutToBeDeleted();
  }

  public testDeepCopyWithMultipleNestedLevels(): void {
    class Level1 {
      public value: string = 'level1';
    }
    class Level2 {
      public l1: Level1 = new Level1();
      public value: string = 'level2';
    }

    const nested = new Level2();
    const observed = ObservedObject.createNew(nested, undefined);
    const sourceProp = new ObservedPropertyPU(observed, this as object as ViewPU, 'sourceProp');

    const oneWayProp = new SynchedPropertyOneWayPU(sourceProp, this as object as ViewPU, 'deepCopyMultiLevelProp');
    const deepCopiedValue = oneWayProp.get();

    const originalName = observed[OBSERVED_OBJECT_NAME];
    const copiedName = deepCopiedValue[OBSERVED_OBJECT_NAME];
    eq(copiedName, originalName, 'deep copy preserves class name for multi-level object');

    oneWayProp.aboutToBeDeleted();
    sourceProp.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 8: ObservedObject.createNewInternal Edge Cases
  // =========================================================================

  public testCreateNewInternalAlreadyObservedObject(): void {
    const obj = new PlainTestClassA();
    const observed1 = ObservedObject.createNew(obj, undefined);
    const originalName = observed1[OBSERVED_OBJECT_NAME];

    const observed2 = ObservedObject.createNew(observed1, undefined);
    const secondName = observed2[OBSERVED_OBJECT_NAME];

    eq(observed2 === observed1, true, 'createNew returns same proxy for already observed object');
    eq(secondName, originalName, 'class name unchanged for already observed object');
  }

  public testCreateNewInternalRawObjectNameFallback(): void {
    const obj: any = { key: 'test' };
    obj[OBSERVED_OBJECT_NAME] = 'PredefinedClassName';
    Object.defineProperty(obj, 'constructor', {
      value: { name: '' },
      writable: true,
      configurable: true
    });

    const observed = ObservedObject.createNew(obj, undefined);
    const className = observed[OBSERVED_OBJECT_NAME];
    neq(className, undefined, 'class name should be defined even with empty constructor name');
    eq(typeof className, 'string', 'class name fallback is a string');
  }

  public testCreateNewInternalWithClassHavingSymbolSet(): void {
    const obj = new PlainTestClassA();
    obj[OBSERVED_OBJECT_NAME] = 'CustomSymbolName';
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'PlainTestClassA', 'createNewInternal uses constructor.name when available, overwriting symbol');
  }

  // =========================================================================
  // SECTION 9: Edge Cases and Robustness
  // =========================================================================

  public testClassNameNotEnumerable(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    const keys = Object.keys(observed);
    eq(keys.includes(String(OBSERVED_OBJECT_NAME)), false, 'OBSERVED_OBJECT_NAME symbol is not enumerable');

    const allKeys = Object.getOwnPropertyNames(observed);
    eq(allKeys.includes(String(OBSERVED_OBJECT_NAME)), false, 'OBSERVED_OBJECT_NAME not in own property names');
  }

  public testClassNameAfterMultipleProxyWraps(): void {
    const obj = new PlainTestClassA();
    const observed1 = ObservedObject.createNew(obj, undefined);
    const observed2 = ObservedObject.createNew(observed1, undefined);

    eq(observed1 === observed2, true, 'double wrapping returns same proxy');
    eq(observed2[OBSERVED_OBJECT_NAME], 'PlainTestClassA', 'class name preserved after double wrap attempt');
  }

  public testClassNamePersistenceThroughPropertyChanges(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);

    eq(observed[OBSERVED_OBJECT_NAME], 'PlainTestClassA', 'class name before property change');

    observed.valueA = 100;
    eq(observed[OBSERVED_OBJECT_NAME], 'PlainTestClassA', 'class name persists after property change');
    eq(observed.valueA, 100, 'property change applied correctly');
  }

  public testClassNameWithObjectCreateNull(): void {
    const obj = Object.create(null);
    obj.key = 'value';
    const observed = ObservedObject.createNew(obj as Object, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    neq(className, undefined, 'class name is set for Object.create(null)');
    eq(typeof className, 'string', 'class name is a string');
  }

  public testClassNameWithSpecialCharacterNames(): void {
    class ClassWithUnicodeName {
      public value: string = 'unicode';
    }
    const obj = new ClassWithUnicodeName();
    const observed = ObservedObject.createNew(obj, undefined);

    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'ClassWithUnicodeName', 'class with unicode characters stores correct name');
  }

  public testClassNameAfterV2CompatibleEnabledOnPlainObject(): void {
    const obj = new PlainTestClassA();
    const observed = ObservedObject.createNew(obj, undefined);
    const originalName = observed[OBSERVED_OBJECT_NAME];

    ObservedObject.enableV2Compatible(observed);
    const nameAfterV2 = observed[OBSERVED_OBJECT_NAME];

    eq(nameAfterV2, originalName, 'class name preserved after enabling V2 compatibility');
  }

  public testClassNameWithSetAfterV2Compatible(): void {
    const set = new Set<string>();
    set.add('a');
    set.add('b');
    const observed = ObservedObject.createNew(set, undefined);

    ObservedObject.enableV2Compatible(observed);
    const className = observed[OBSERVED_OBJECT_NAME];
    eq(className, 'Set', 'Set class name preserved in V2 compat mode');
  }

  public testClassNameWithDateAfterV2Compatible(): void {
    const date = new Date(2025, 5, 15);
    const observed = ObservedObject.createNew(date, undefined);

    const classNameBefore = observed[OBSERVED_OBJECT_NAME];
    eq(classNameBefore, 'Date', 'Date class name before V2 compat');

    ObservedObject.enableV2Compatible(observed);
    const classNameAfter = observed[OBSERVED_OBJECT_NAME];
    eq(classNameAfter, 'Date', 'Date class name preserved after V2 compat');
  }

  public testClassNameWithNestedObservedAfterPropertyUpdate(): void {
    const prop = this as any;
    const originalName = prop.__testObservedNameContainer.get()[OBSERVED_OBJECT_NAME];

    const newContainer = new PlainTestContainerClass();
    const newObserved = ObservedObject.createNew(newContainer, undefined);
    prop.__testObservedNameContainer.set(newObserved as any);

    const updatedName = prop.__testObservedNameContainer.get()[OBSERVED_OBJECT_NAME];
    eq(updatedName, 'PlainTestContainerClass', 'container class name updated after set');
    neq(updatedName, originalName, 'class name changed after setting new observed object');
  }
}
