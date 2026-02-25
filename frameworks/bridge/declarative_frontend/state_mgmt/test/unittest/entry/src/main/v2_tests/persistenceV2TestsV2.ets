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
import { PersistenceV2, Type } from '@kit.ArkUI';
import { collections } from '@kit.ArkTS';
import { mockStorage, unmockStorage, resetPersistenceV2 } from '../mocks/mock_persistence_v2';
import { eq, ITestFile } from '../lib/testRunner'

class CSimple<T> {
  prop?: T;
  constructor(prop?: T) {
    this.prop = prop;
  }
}

@Sendable
class CSendable<T> {
  prop?: T;
  constructor(prop?: T) {
    this.prop = prop;
  }
}

@Sendable
class CSendableWithObject {
  prop: CSendable<string> = new CSendable<string>('');
}

export class PersistenceV2TestsV2 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll () : void {}

  // Executed before every individual tests. Can be empty
  public beforeEach () : void {
    mockStorage();
    resetPersistenceV2();
  }

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {
    unmockStorage();
    resetPersistenceV2();
  }

  public getId(): string {
    return this.idString;
  }

  // Toplevel. Objects
  //

  testToplevelDate() {
    const ob1: Date = PersistenceV2.globalConnect({
      type: Date,
      defaultCreator: () => new Date('2023-01-01T00:00:00.000Z')
    })!;
    PersistenceV2.save(Date);

    // simulate app restart
    resetPersistenceV2();

    const ob2: Date = PersistenceV2.globalConnect({
      type: Date, defaultCreator: () => new Date()
    })!;

    eq(ob2 instanceof Date, true);
    eq(ob2.toISOString(), '2023-01-01T00:00:00.000Z');
  }

  testToplevelObject() {
    const ob1: CSimple<string> = PersistenceV2.globalConnect({
      type: CSimple<string>,
      defaultCreator: () => new CSimple<string>('value')
    })!;
    PersistenceV2.save(CSimple<string>);

    // simulate app restart
    resetPersistenceV2();

    const ob2: CSimple<string> = PersistenceV2.globalConnect({
      type: CSimple<string>,
      defaultCreator: () => new CSimple<string>()
    })!;
    eq(ob2.prop, 'value');
  }

  // Toplevel. Array/Map/Set
  //

  testToplevelArrayOfStrings() {
    const arr1: Array<string> = PersistenceV2.globalConnect({
      type: Array<string>,
      defaultCreator: () => new Array<string>()
    })!;

    // update and save
    arr1.push('a');
    arr1.push('b');
    PersistenceV2.save(Array);

    // simulate app restart
    resetPersistenceV2();

    const arr2: Array<string> = PersistenceV2.globalConnect({
      type: Array<string>,
      defaultCreator: () => new Array<string>()
    })!;
    eq(arr2[0], 'a');
    eq(arr2[1], 'b');
  }
  
  testToplevelSetOfStrings() {
    const set1: Set<string> = PersistenceV2.globalConnect({
      type: Set<string>,
      defaultCreator: () => new Set<string>()
    })!;

    // update and save
    set1.add('a');
    set1.add('b');
    PersistenceV2.save(Set);

    // simulate app restart
    resetPersistenceV2();

    const set2: Set<string> = PersistenceV2.globalConnect({
      type: Set<string>,
      defaultCreator: () => new Set<string>()
    })!;
    eq(Array.from(set2.values())[0], 'a');
    eq(Array.from(set2.values())[1], 'b');
  }

  testToplevelMapOfStrings() {
    const map1: Map<string, string> = PersistenceV2.globalConnect({
      type: Map<string, string>,
      defaultCreator: () => new Map<string, string>()
    })!;
    
    // update and save
    map1.set('key1', 'a');
    map1.set('key2', 'b');
    PersistenceV2.save(Map);

    // simulate app restart
    resetPersistenceV2();

    const map2: Map<string, string> = PersistenceV2.globalConnect({
      type: Map<string, string>,
      defaultCreator: () => new Map<string, string>()
    })!;
    eq(map2.size, 2);
    eq(map2.get('key1'), 'a');
    eq(map2.get('key2'), 'b');
  }

  testToplevelArrayOfObjects() {    
    const arr1: Array<CSimple<string>> = PersistenceV2.globalConnect({
      type: Array<CSimple<string>>,
      defaultCreator: () => new Array<CSimple<string>>(),
      defaultSubCreator: () => new CSimple<string>('')
    })!;

    // update and save
    arr1.push(new CSimple<string>('a'));
    arr1.push(new CSimple<string>('b'));
    PersistenceV2.save(Array);

    // simulate app restart
    resetPersistenceV2();

    const arr2: Array<CSimple<string>> = PersistenceV2.globalConnect({
      type: Array<CSimple<string>>,
      defaultCreator: () => new Array<CSimple<string>>(),
      defaultSubCreator: () => new CSimple<string>('')
    })!;

    eq(arr1[0] instanceof CSimple, true);
    eq(arr1[1] instanceof CSimple, true);
    eq(arr2[0].prop, 'a');
    eq(arr2[1].prop, 'b');
  }

  testToplevelSetOfObjects() {
    const set1: Set<CSimple<string>> = PersistenceV2.globalConnect({
      type: Set<CSimple<string>>,
      defaultCreator: () => new Set<CSimple<string>>(),
      defaultSubCreator: () => new CSimple<string>('')
    })!;

    // update and save
    set1.add(new CSimple<string>('a'));
    set1.add(new CSimple<string>('b'));
    PersistenceV2.save(Set);

    // simulate app restart
    resetPersistenceV2();

    const set2: Set<CSimple<string>> = PersistenceV2.globalConnect({
      type: Set<CSimple<string>>,
      defaultCreator: () => new Set<CSimple<string>>(),
      defaultSubCreator: () => new CSimple<string>('')
    })!;

    const values: Array<CSimple<string>> = Array.from(set2.values());
    eq(values[0] instanceof CSimple, true);
    eq(values[1] instanceof CSimple, true);
    eq(values[0]?.prop, 'a');
    eq(values[1]?.prop, 'b');
  }

  testToplevelMapOfObjects() {
    const map1: Map<string, CSimple<string>> = PersistenceV2.globalConnect({
      type: Map<string, CSimple<string>>,
      defaultCreator: () => new Map<string, CSimple<string>>(),
      defaultSubCreator: () => new CSimple<string>('')
    })!;

    // update and save
    map1.set('key1', new CSimple<string>('a'));
    map1.set('key2', new CSimple<string>('b'));
    PersistenceV2.save(Map);

    // simulate app restart
    resetPersistenceV2();

    const map2: Map<string, CSimple<string>> = PersistenceV2.globalConnect({
      type: Map<string, CSimple<string>>,
      defaultCreator: () => new Map<string, CSimple<string>>(),
      defaultSubCreator: () => new CSimple<string>('')
    })!;

    eq(map2.size, 2);
    eq(map2.get('key1') instanceof CSimple, true);
    eq(map2.get('key2') instanceof CSimple, true);
    eq(map2.get('key1')?.prop, 'a');
    eq(map2.get('key2')?.prop, 'b');
  }

  // Toplevel. Sendable and collections.Array/Map/Set
  //

  testToplevelSendableObject() {
    const ob1: CSendable<string> = PersistenceV2.globalConnect({
      type: CSendable<string>,
      defaultCreator: () => new CSendable<string>('value')
    })!;
    PersistenceV2.save(CSendable);

    // simulate app restart
    resetPersistenceV2();

    const ob2: CSendable<string> = PersistenceV2.globalConnect({
      type: CSendable<string>,
      defaultCreator: () => new CSendable<string>('')
    })!;

    eq(ob2.prop, 'value');
  }

  testToplevelCollectionArrayOfStrings() {
    const arr1: collections.Array<string> = PersistenceV2.globalConnect({
      type: collections.Array<string>,
      key: 'collections.Array',
      defaultCreator: () => new collections.Array<string>()
    })!;

    arr1.push('a');
    arr1.push('b');
    PersistenceV2.save('collections.Array');

    // simulate app restart
    resetPersistenceV2();

    const arr2: collections.Array<string> = PersistenceV2.globalConnect({
      type: collections.Array<string>,
      key: 'collections.Array',
      defaultCreator: () => new collections.Array<string>()
    })!;
    eq(arr2[0], 'a');
    eq(arr2[1], 'b');
  }

  testToplevelCollectionSetOfStrings() {
    const set1: collections.Set<string> = PersistenceV2.globalConnect({
      type: collections.Set<string>,
      key: 'collections.Set',
      defaultCreator: () => new collections.Set<string>()
    })!;
    set1.add('a');
    set1.add('b');
    PersistenceV2.save('collections.Set');

    // simulate app restart
    resetPersistenceV2();

    const set2: collections.Set<string> = PersistenceV2.globalConnect({
      type: collections.Set<string>,
      key: 'collections.Set',
      defaultCreator: () => new collections.Set<string>()
    })!;

    const values: Array<string> = Array.from(set2.values());
    eq(values[0], 'a');
    eq(values[1], 'b');
  }

  testToplevelCollectionMapOfStrings() {
    const map1: collections.Map<string, string> = PersistenceV2.globalConnect({
      type: collections.Map<string, string>,
      key: 'collections.Map',
      defaultCreator: () => new collections.Map<string, string>()
    })!;

    // update and save
    map1.set('key1', 'a');
    map1.set('key2', 'b');
    PersistenceV2.save('collections.Map');

    // simulate app restart
    resetPersistenceV2();

    const map2: collections.Map<string, string> = PersistenceV2.globalConnect({
      type: collections.Map<string, string>,
      key: 'collections.Map',
      defaultCreator: () => new collections.Map<string, string>()
    })!;

    eq(map2.size, 2);
    eq(map2.get('key1'), 'a');
    eq(map2.get('key2'), 'b');
  }

  testToplevelCollectionArrayOfSendables() {
    const arr1: collections.Array<CSendable<string>> = PersistenceV2.globalConnect({
      type: collections.Array<CSendable<string>>,
      key: 'collections.Array',
      defaultCreator: () => new collections.Array<CSendable<string>>(),
      defaultSubCreator: () => new CSendable<string>('')
    })!;

    // update and save
    arr1.push(new CSendable<string>('a'));
    arr1.push(new CSendable<string>('b'));
    PersistenceV2.save('collections.Array');

    // simulate app restart
    resetPersistenceV2();

    const arr2: collections.Array<CSendable<string>> = PersistenceV2.globalConnect({
      type: collections.Array<CSendable<string>>,
      key: 'collections.Array',
      defaultCreator: () => new collections.Array<CSendable<string>>(),
      defaultSubCreator: () => new CSendable<string>('')
    })!;

    eq(globalThis.isSendable(arr2[0]), true);
    eq(globalThis.isSendable(arr2[1]), true);
    eq(arr2[0] instanceof CSendable, false); // exact type can't be restored when using Sendable
    eq(arr2[1] instanceof CSendable, false); // exact type can't be restored when using Sendable
    eq(arr2[0].prop, 'a');
    eq(arr2[1].prop, 'b');
  }

  testToplevelCollectionSetOfSendables() {
    const set1: collections.Set<CSendable<string>> = PersistenceV2.globalConnect({
      type: collections.Set<CSendable<string>>,
      key: 'collections.Set',
      defaultCreator: () => new collections.Set<CSendable<string>>(),
      defaultSubCreator: () => new CSendable<string>('')
    })!;

    // update and save
    set1.add(new CSendable<string>('a'));
    set1.add(new CSendable<string>('b'));
    PersistenceV2.save('collections.Set');

    // simulate app restart
    resetPersistenceV2();

    const set2: collections.Set<CSendable<string>> = PersistenceV2.globalConnect({
      type: collections.Set<CSendable<string>>,
      key: 'collections.Set',
      defaultCreator: () => new collections.Set<CSendable<string>>(),
      defaultSubCreator: () => new CSendable<string>('')
    })!;

    const values: Array<CSendable<string>> = Array.from(set2.values());
    eq(globalThis.isSendable(values[0]), true);
    eq(globalThis.isSendable(values[1]), true);
    eq(values[0] instanceof CSendable, false); // exact type can't be restored when using Sendable
    eq(values[1] instanceof CSendable, false); // exact type can't be restored when using Sendable
    eq(values[0].prop, 'a');
    eq(values[1].prop, 'b');
  }

  testToplevelCollectionMapOfSendables() {
    const map1: collections.Map<string, CSendable<string>> = PersistenceV2.globalConnect({
      type: collections.Map<string, CSendable<string>>,
      key: 'collections.Map',
      defaultCreator: () => new collections.Map<string, CSendable<string>>(),
      defaultSubCreator: () => new CSendable<string>('')
    })!;

    // update and save
    map1.set('key1', new CSendable<string>('a'));
    map1.set('key2', new CSendable<string>('b'));
    PersistenceV2.save('collections.Map');

    // simulate app restart
    resetPersistenceV2();

    const map2: collections.Map<string, CSendable<string>> = PersistenceV2.globalConnect({
      type: collections.Map<string, CSendable<string>>,
      key: 'collections.Map',
      defaultCreator: () => new collections.Map<string, CSendable<string>>(),
      defaultSubCreator: () => new CSendable<string>('')
    })!;

    eq(map2.size, 2);
    eq(globalThis.isSendable(map2.get('key1')), true);
    eq(globalThis.isSendable(map2.get('key2')), true);
    eq(map2.get('key1') instanceof CSendable, false); // exact type can't be restored when using Sendable
    eq(map2.get('key2') instanceof CSendable, false); // exact type can't be restored when using Sendable
    eq(map2.get('key1')?.prop, 'a');
    eq(map2.get('key2')?.prop, 'b');
  }

  // Nested. Built-in types
  //

  testBoolean() {
    const data1: CSimple<Boolean> = PersistenceV2.globalConnect({
      type: CSimple<Boolean>,
      defaultCreator: () => new CSimple<Boolean>(new Boolean(true))
    })!;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<Boolean> = PersistenceV2.globalConnect({
      type: CSimple<Boolean>,
      defaultCreator: () => new CSimple<Boolean>(false)
    })!;

    eq(data2.prop instanceof Boolean, true);
    eq(data2.prop?.valueOf(), true);
  }

  testDate() {
    const data1: CSimple<Date> = PersistenceV2.globalConnect({
      type: CSimple<Date>,
      defaultCreator: () => new CSimple<Date>(new Date('2026-01-20T00:00:00.000Z'))
    })!;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<Date> = PersistenceV2.globalConnect({
      type: CSimple<Date>,
      defaultCreator: () => new CSimple<Date>(new Date())
    })!;

    eq(data2.prop instanceof Date, true);
    eq(data2.prop?.toISOString(), '2026-01-20T00:00:00.000Z');
  }

  testNumber() {
    const data1: CSimple<Number> = PersistenceV2.globalConnect({
      type: CSimple<Number>,
      defaultCreator: () => new CSimple<Number>(new Number(-Infinity))
    })!;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<Number> = PersistenceV2.globalConnect({
      type: CSimple<Number>,
      defaultCreator: () => new CSimple<Number>(new Number(0))
    })!;

    eq(data2.prop instanceof Number, true);
    eq(data2.prop?.valueOf(), -Infinity);
  }

  testString() {
    const data1: CSimple<String> = PersistenceV2.globalConnect({
      type: CSimple<String>,
      defaultCreator: () => new CSimple<String>(new String(''))
    })!;

    // update and save
    data1.prop = new String('test');
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<String> = PersistenceV2.globalConnect({
      type: CSimple<String>,
      defaultCreator: () => new CSimple<String>('')
    })!;

    eq(data2.prop instanceof String, true);
    eq(data2.prop?.valueOf(), 'test');
  }

  test_bigint() {
    const data1: CSimple<bigint> = PersistenceV2.globalConnect({
      type: CSimple<bigint>,
      defaultCreator: () => new CSimple<bigint>(123n)
    })!;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<bigint> = PersistenceV2.globalConnect({
      type: CSimple<bigint>,
      defaultCreator: () => new CSimple<bigint>(0n)
    })!;
    eq(data2.prop?.valueOf(), 123n);
  }

  test_boolean() {
    const data1: CSimple<boolean> = PersistenceV2.globalConnect({
      type: CSimple<boolean>,
      defaultCreator: () => new CSimple<boolean>(false)
    })!;

    // update and save
    data1.prop = true;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<boolean> = PersistenceV2.globalConnect({
      type: CSimple<boolean>,
      defaultCreator: () => new CSimple<boolean>(false)
    })!;
    eq(data2.prop?.valueOf(), true);
  }

  test_number() {
    const data1: CSimple<number> = PersistenceV2.globalConnect({
      type: CSimple<number>,
      defaultCreator: () => new CSimple<number>(42)
    })!;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<number> = PersistenceV2.globalConnect({
      type: CSimple<number>,
      defaultCreator: () => new CSimple<number>(0)
    })!;
    eq(data2.prop?.valueOf(), 42);
  }

  test_string() {
    const data1: CSimple<string> = PersistenceV2.globalConnect({
      type: CSimple<string>,
      defaultCreator: () => new CSimple<string>('test')
    })!;
    PersistenceV2.save(CSimple);

    // simulate app restart
    resetPersistenceV2();

    const data2: CSimple<string> = PersistenceV2.globalConnect({
      type: CSimple<string>,
      defaultCreator: () => new CSimple<string>('')
    })!;
    eq(data2.prop?.valueOf(), 'test');
  }

  testCircularRefs() {
    class A {
      // We can't use @Type(B) here as B is not yet defined, use 'object' type instead.
      refB?: object;
    }
    class B {
      // Use type 'object' that can be reconstructed without the @Type annotation.
      refA?: object;
    }
    class Data {
      // Use type 'object' that can be reconstructed without the @Type annotation.
      a?: object;
      b?: object;
    }

    const data1: Data = PersistenceV2.globalConnect({
      type: Data,
      defaultCreator: () => new Data()
    })!;

    // update and save
    data1.a = new A() as object;
    data1.b = new B() as object;
    (data1.a as A).refB = data1.b;
    (data1.b as B).refA = data1.a;
    PersistenceV2.save(Data);

    // simulate app restart
    resetPersistenceV2();

    const data2: Data = PersistenceV2.globalConnect({
      type: Data,
      defaultCreator: () => new Data()
    })!;

    eq(data2.a, (data2.b as B).refA);
    eq(data2.b, (data2.a as A).refB);
  }

  // Union types and optional properties
  //

  testOptionalNull() {
    class C {
      nullOrUndef: null|undefined;
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.nullOrUndef = null;
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    eq(data2.nullOrUndef, null);    
  }

  testOptionalString() {
    class C {
      stringOrUndef: string|undefined;
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.stringOrUndef = 'test';
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    eq(data2.stringOrUndef, 'test');    
  }

  testOptionalStringUseUndefined() {
    class C {
      prop: String | undefined = new String('value');
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.prop = undefined;
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    eq(data2.prop, undefined);
  }

  testUnionStringOrNumberUseString() {
    class C {
      prop: String | Number | undefined;
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.prop = new String('test');
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    eq(data2.prop instanceof String, true);
    eq(data2.prop?.valueOf(), 'test');
  }

  testUnionStringOrNumberUseNumber() {
    class C {
      prop: String | Number | undefined;
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.prop = new Number(-Infinity);
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;
    eq(data2.prop instanceof Number, true);
    eq(data2.prop?.valueOf(), -Infinity);
  }

  testUnionStringOrAppClassUseString() {
    class C {
      @Type(CSimple<string>)
      prop: String | CSimple<string> | undefined;
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.prop = new String('test');
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    eq(data2.prop instanceof String, true);
    eq((data2.prop as String).valueOf(), 'test');
  }

  testUnionStringOrAppClassUseAppClass() {
    class C {
      @Type(CSimple<string>)
      prop: String | CSimple<string> | undefined;
    }

    const data1: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    data1.prop = new CSimple<string>('test');
    PersistenceV2.save(C);

    // simulate app restart
    resetPersistenceV2();

    const data2: C = PersistenceV2.globalConnect({
      type: C,
      defaultCreator: () => new C()
    })!;

    eq(data2.prop instanceof CSimple, true);
    eq((data2.prop as CSimple<string>)?.prop, 'test');
  }

  // Errors and special cases
  //
  
  testErrorMismatchClasses() {
    const data1: Array<string> = PersistenceV2.globalConnect({
      type: Array<string>,
      key: 'data',
      defaultCreator: () => new Array<string>()
    })!;
    PersistenceV2.save('data');

    // simulate app restart
    resetPersistenceV2();

    PersistenceV2.notifyOnError((key: string, reason: string, msg: string) => {
      // Expected BusinessError here (...The class of target (Set) mismatches 'Array'...)
      eq(key, 'data');
      eq(reason, 'serialization');
    });

    // Restore an Array as a Set - should cause error
    const data2: Set<string> = PersistenceV2.globalConnect({
      type: Set<string>,
      key: 'data',
      defaultCreator: () => new Set<string>()
    })!;
  }

  testExtendedArray() {
    class CArray extends Array<string> {
      notPersistValue?: string;
    }

    const arr1: CArray = PersistenceV2.globalConnect({
      type: CArray,
      defaultCreator: () => new CArray()
    })!;

    arr1.push('a');
    arr1.push('b');
    arr1.notPersistValue = 'testValue';
    PersistenceV2.save(CArray);

    // simulate app restart
    resetPersistenceV2();

    const arr2: CArray = PersistenceV2.globalConnect({
      type: CArray,
      defaultCreator: () => new CArray()
    })!;

    eq(arr2[0], 'a');
    eq(arr2[1], 'b');
    // notPersistValue is non-persistent since it belongs to a Collection subclass
    eq(arr2.notPersistValue, undefined);
  }

  testExtendedMap() {
    class CMap extends Map<string, string> {
      notPersistValue?: string;
    }

    const map1: CMap = PersistenceV2.globalConnect({
      type: CMap,
      defaultCreator: () => new CMap()
    })!;

    // update and save
    map1.set('key1', 'a');
    map1.set('key2', 'b');
    map1.notPersistValue = 'testValue';
    PersistenceV2.save(CMap);

    // simulate app restart
    resetPersistenceV2();

    const map2: CMap = PersistenceV2.globalConnect({
      type: CMap,
      defaultCreator: () => new CMap()
    })!;

    eq(map2.get('key1'), 'a');
    eq(map2.get('key2'), 'b');
    // notPersistValue is non-persistent since it belongs to a Collection subclass
    eq(map2.notPersistValue, undefined);
  }

  testExtendedSet() {
    class CSet extends Set<string> {
      notPersistValue?: string;
    }

    const set1: CSet = PersistenceV2.globalConnect({
      type: CSet,
      defaultCreator: () => new CSet()
    })!;

    // update and save
    set1.add('a');
    set1.add('b');
    set1.notPersistValue = 'testValue';
    PersistenceV2.save(CSet);

    // simulate app restart
    resetPersistenceV2();

    const set2: CSet = PersistenceV2.globalConnect({
      type: CSet,
      defaultCreator: () => new CSet()
    })!;

    eq(set2.has('a'), true);
    eq(set2.has('b'), true);
    // notPersistValue is non-persistent since it belongs to a Collection subclass
    eq(set2.notPersistValue, undefined);
  }

  testErrorArrayOfArrays() {
    const arr1: Array<Array<string>> = PersistenceV2.globalConnect({
      type: Array<Array<string>>,
      defaultCreator: () => new Array<Array<string>>(),
      defaultSubCreator: () => new Array<string>()
    })!;

    // update and save
    arr1.push(new Array<string>('a1', 'a2'));
    arr1.push(new Array<string>('b1', 'b2'));
    PersistenceV2.save(Array);

    resetPersistenceV2();

    PersistenceV2.notifyOnError((key: string, reason: string, msg: string) => {
      // Expected BusinessError here (Array, Map, Set, or collections.Array/Map/Set cannot be used as collection item)
      // for the key 'Array'
      eq(key, 'Array');
      eq(reason, 'serialization');
    });

    const arr2: Array<Array<string>> = PersistenceV2.globalConnect({
      type: Array<Array<string>>,
      defaultCreator: () => new Array<Array<string>>(),
      defaultSubCreator: () => new Array<string>()
    })!;
  }

  testErrorSendableAllowsOnlyPlainProps() {
    PersistenceV2.notifyOnError((key: string, reason: string, msg: string) => {
      // Expected BusinessError here (...@Sendable only allows plain property types...)
      // for the key 'CSendableWithDate'
      eq(key, 'CSendableWithObject');
      eq(reason, 'serialization');
    });

    const data1: CSendableWithObject = PersistenceV2.globalConnect({
      type: CSendableWithObject,
      defaultCreator: () => new CSendableWithObject()
    })!;

    PersistenceV2.save(CSendableWithObject);
  }

  testErrorNullAndNoType() {
    class A {
      // @Type decorator intentionally missing here
      prop: null | CSimple<string> = null;
    }

    const data1: A = PersistenceV2.globalConnect({
      type: A,
      defaultCreator: () => new A()
    })!;
    // update and save
    data1.prop = new CSimple<string>('test');
    PersistenceV2.save(A);

    // simulate app restart
    resetPersistenceV2();

    PersistenceV2.notifyOnError((key: string, reason: string, msg: string) => {
      // Expected BusinessError here (...Miss @Type in object defined...)
      eq(key, 'A');
      eq(reason, 'serialization');
    });

    const data2: A = PersistenceV2.globalConnect({
      type: A,
      defaultCreator: () => new A()
    })!;
  }

  testErrorInvalidDefaultSubCreator() {
    const arr1: Array<CSimple<string>> = PersistenceV2.globalConnect({
      type: Array<CSimple<string>>,
      defaultCreator: () => new Array<CSimple<string>>(),
      // Invalid defaultSubCreator returning wrong type
      defaultSubCreator: () => undefined
    })!;

    arr1.push(new CSimple<string>('a'));
    arr1.push(new CSimple<string>('b'));
    PersistenceV2.save(Array);

    // simulate app restart
    resetPersistenceV2();

    PersistenceV2.notifyOnError((key: string, reason: string, msg: string) => {
      // Expected BusinessError here (defaultSubCreator returned invalid type)
      eq(key, 'Array');
      eq(reason, 'serialization');
    });

    const arr2: Array<CSimple<string>> = PersistenceV2.globalConnect({
      type: Array<CSimple<string>>,
      defaultCreator: () => new Array<CSimple<string>>(),
      // Invalid defaultSubCreator returning wrong type
      defaultSubCreator: () => undefined
    })!;
  }

}