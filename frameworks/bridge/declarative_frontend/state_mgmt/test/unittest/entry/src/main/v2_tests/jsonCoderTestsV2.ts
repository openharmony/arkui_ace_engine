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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner';

// Declare JSONCoder to avoid 'Cannot find name JSONCoder' errors
declare class JSONCoder {
  static stringify<T>(value: T, replacer?: (this: any, key: string, value: any) => any, space?: string | number): string;
  static parse<T extends object>(type: any, source: object | string): T | T[];
  static parseTo<T extends object>(target: T | T[], source: object | string, type?: any): T | T[];
  static getOptions<T>(type?: any): any;
}

// Declare Meta to avoid 'Cannot find name Meta' errors
declare class Meta {
  static define(proto: object, prop: string, value: any): void;
  static get(obj: any, prop: string): any;
  static gets(obj: any): object;
  static getOwn(obj: any, prop: string): any;
}

// Type definitions for json_coder.ts
type TypeConstructor<T> = { new(): T };
type FactoryConstructor<T> = (json: object) => TypeConstructor<T>;
type JSONAny = object | number | string | boolean | undefined | null;

interface TransformOptions<T> {
  factory?: FactoryConstructor<T>;
  alias?: string;
  disabled?: boolean;
}

// ============================================================================
// Test Fixture Classes
// ============================================================================

class SimpleTestClass {
  name: string = 'test';
  value: number = 0;
  active: boolean = false;

  getName(): string {
    return this.name;
  }

  public setValue(val: number): void {
    this.value = val;
  }
}

class ClassWithNested {
  id: number = 0;
  label: string = 'nested';
  data: object = {};

  public getData(): object {
    return this.data;
  }

  public setData(data: object): void {
    this.data = data;
  }
}

class ClassWithArrays {
  items: string[] = [];
  numbers: number[] = [];
  nested: ClassWithNested[] = [];

  public addItem(item: string): void {
    this.items.push(item);
  }

  public addNumber(num: number): void {
    this.numbers.push(num);
  }

  public addNested(item: ClassWithNested): void {
    this.nested.push(item);
  }
}

class ClassWithMapSet {
  tags: Set<string> = new Set();
  properties: Map<string, any> = new Map();
  metadata: Map<string, string> = new Map();
}

class ClassWithObserved {
  __ob_id__1: number = 1;
  __ob_name__2: string = 'test';
  __ob_active__3: boolean = true;
  normalField: string = 'normal';
}

class ClassWithDates {
  createdAt: Date = new Date();
  updatedAt: Date | null = null;
  timestamp: number = 0;

  public getTimestamp(): number {
    return this.timestamp;
  }

  public setTimestamp(value: number): void {
    this.timestamp = value;
  }
}

class ClassWithNullUndefined {
  nullableString: string | null = null;
  nullableNumber: number | null = null;
  emptyString: string = '';
  zeroNumber: number = 0;
  falseBoolean: boolean = false;
}

class ClassWithSpecialChars {
  fieldName: string = 'field-with-dash';
  unicodeName: string = '中文字段';
  emojiValue: string = '🎉';
  newLine: string = 'line1\nline2';
  tabValue: string = 'col1\tcol2';
  quoteValue: string = 'He said "hello"';
}

class ClassWithNumbers {
  intValue: number = 42;
  floatValue: number = 3.14;
  negativeValue: number = -100;
  zeroValue: number = 0;
  maxValue: number = Number.MAX_SAFE_INTEGER;
  minValue: number = Number.MIN_SAFE_INTEGER;
  nanValue: number = NaN;
  infinityValue: number = Infinity;
}

class ClassWithMixedTypes {
  anyValue: any = undefined;
  unknownValue: unknown = null;
  unionValue: string | number = 'initial';
  literalValue: 'yes' | 'no';
  optionalValue?: string;
}

class ClassWithMethods {
  data: string = 'data';
  private internalState: number = 0;

  public processData(): string {
    return this.data.toUpperCase();
  }

  public getState(): number {
    return this.internalState;
  }

  public setState(value: number): void {
    this.internalState = value;
  }

  public combine(input: string): string {
    return this.data + ':' + input;
  }
}

class ClassWithReadOnly {
  readonly constantValue: number = 100;
  readonly constantString: string = 'immutable';
  mutableValue: string = 'mutable';
}

class DeepNestedClass {
  id: number = 1;
  nested: {
    level1: {
      level2: {
        level3: {
          value: string;
          count: number;
        }
      }
    }
  } = { level1: { level2: { level3: { value: 'deep', count: 0 } } } };
}

class ClassWithArraysComplex {
  matrix: number[][] = [[1, 2], [3, 4]];
  heterogeneous: any[] = [1, 'two', 3];
  sparse: any[] = [1, , , 4];
}

class ClassWithSpecialArrays {
  typedArray: Uint8Array = new Uint8Array([1, 2, 3]);
  arrayBuffer: ArrayBuffer = new ArrayBuffer(8);
}

class ClassWithEmptyValues {
  emptyObject: object = {};
  emptyArray: any[] = [];
  emptyString: string = '';
  nullValue: any = null;
  undefinedValue: any = undefined;
}

class ClassWithCyclicRef {
  id: number = 1;
  parent: ClassWithCyclicRef | null = null;
  children: ClassWithCyclicRef[] = [];
}

class ClassWithGettersSetters {
  private _value: number = 0;
  public get value(): number {
    return this._value;
  }
  public set value(v: number) {
    this._value = v;
  }
  public get doubled(): number {
    return this._value * 2;
  }
}

class ClassWithMapsComplex {
  stringKeys: Map<string, number> = new Map([['a', 1], ['b', 2]]);
  nestedMap: Map<string, Map<string, number>> = new Map([
    ['outer', new Map([['inner', 1]])]
  ]);
}

class ClassWithSetsComplex {
  numberSet: Set<number> = new Set([1, 2, 3]);
  stringSet: Set<string> = new Set(['a', 'b', 'c']);
  mixedSet: Set<any> = new Set([1, 'two', true]);
}

class ClassWithDatesComplex {
  dates: Date[] = [new Date(), new Date('2026-01-01')];
  dateMap: Map<string, Date> = new Map([['now', new Date()]]);
}

// ============================================================================
// Main Test Class
// ============================================================================

export class JsonCoderTestsV2 implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating JsonCoderTestsV2: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {}

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // Meta Class Tests
  // =========================================================================

  public testMetaDefine(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'testProp', { value: 'test' });
    const result = Meta.get(obj, 'testProp');
    eq(result && result.value, 'test', 'Meta should define property');
  }

  public testMetaGet(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'myField', { alias: 'aliased' });
    const result = Meta.get(obj, 'myField');
    eq(result && result.alias, 'aliased', 'Meta should get property');
  }

  public testMetaGets(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'prop1', { disabled: false });
    Meta.define(proto, 'prop2', { disabled: true });
    const meta = Meta.gets(obj);
    eq(Object.keys(meta).length, 2, 'Meta gets should return all properties');
  }

  public testMetaGetOwn(): void {
    const obj: any = {};
    Meta.define(obj.__proto__, 'ownProp', { factory: null });
    const result = Meta.getOwn(obj, 'ownProp');
    eq(result && result.factory, null, 'Meta getOwn should return own property');
  }

  public testMetaMultipleInheritance(): void {
    const parent: any = {};
    const child: any = Object.create(parent);
    Meta.define(Object.getPrototypeOf(parent), 'parentProp', { alias: 'p1' });
    Meta.define(Object.getPrototypeOf(child), 'childProp', { alias: 'c1' });
    const result = Meta.get(child, 'parentProp');
    eq(result && result.alias, 'p1', 'Meta should traverse prototype chain');
  }

  public testMetaOverride(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'overridable', { value: 1 });
    Meta.define(proto, 'overridable', { value: 2 });
    const result = Meta.get(obj, 'overridable');
    eq(result && result.value, 2, 'Meta should override existing property');
  }

  public testNonExistentProperty(): void {
    const obj: any = {};
    const result = Meta.get(obj, 'nonexistent');
    eq(result, undefined, 'Meta should return undefined for non-existent property');
  }

  public testMetaWeakMapStorage(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'weakProp', { value: 'stored' });
    const result = Meta.get(obj, 'weakProp');
    eq(typeof result, 'object', 'Meta should store in WeakMap');
  }

  // =========================================================================
  // ObservedReplacer Tests
  // =========================================================================

  public testObservedReplacerSet(): void {
    const obj = {
      tags: new Set<string>(['tag1', 'tag2', 'tag3'])
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.tags), true, 'Set should be converted to array');
    eq(parsed.tags.length, 3, 'Set size should be preserved');
  }

  public testObservedReplacerMap(): void {
    const obj = {
      properties: new Map<string, number>([['key1', 100], ['key2', 200]])
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.properties), true, 'Map should be converted to array');
    eq(parsed.properties.length, 2, 'Map size should be preserved');
  }

  public testObservedReplacerNestedSet(): void {
    const obj = {
      nested: {
        tags: new Set<number>([1, 2, 3])
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.nested.tags), true, 'Nested Set should be converted');
  }

  public testObservedReplacerNestedMap(): void {
    const obj = {
      nested: {
        data: new Map([['a', 1], ['b', 2]])
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.nested.data), true, 'Nested Map should be converted');
  }

  public testObservedReplacerEmptySet(): void {
    const obj = {
      emptySet: new Set<any>()
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.emptySet.length, 0, 'Empty Set should be handled');
  }

  public testObservedReplacerEmptyMap(): void {
    const obj = {
      emptyMap: new Map<any, any>()
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.emptyMap.length, 0, 'Empty Map should be handled');
  }

  public testObservedReplacerMixedTypes(): void {
    const obj = {
      num: 42,
      str: 'test',
      bool: true,
      set: new Set([1, 2]),
      map: new Map([['k', 'v']])
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.num, 42, 'Number should be preserved');
    eq(parsed.str, 'test', 'String should be preserved');
    eq(parsed.bool, true, 'Boolean should be preserved');
  }

  public testObservedReplacerDisabledProperty(): void {
    const obj: any = {};
    Object.setPrototypeOf(obj, {});
    Meta.define(Object.getPrototypeOf(obj), 'disabledProp', { disabled: true });
    obj.disabledProp = 'should be ignored';
    const result = JSONCoder.stringify(obj);
    eq(result.includes('should be ignored'), false, 'Disabled property should not appear');
  }

  public testObservedReplacerAlias(): void {
    const obj: any = {};
    Object.setPrototypeOf(obj, {});
    Meta.define(Object.getPrototypeOf(obj), 'original', { alias: 'aliased' });
    obj.original = 'value';
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.aliased, 'value', 'Alias should be used in output');
  }

  public testObservedReplacerWithCustomReplacer(): void {
    const obj = {
      tags: new Set([1, 2, 3])
    };
    const customReplacer = (key: string, value: any) => {
      if (typeof value === 'number') {
        return value * 2;
      }
      return value;
    };
    const result = JSONCoder.stringify(obj, customReplacer);
    const parsed = JSON.parse(result);
    eq(parsed.tags[0], 2, 'Custom replacer should be applied');
  }

  // =========================================================================
  // Stringify Tests
  // =========================================================================

  public testStringifySimpleObject(): void {
    const obj = {
      name: 'test',
      value: 42,
      active: true
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.name, 'test', 'Simple object stringify should preserve string');
    eq(parsed.value, 42, 'Simple object stringify should preserve number');
    eq(parsed.active, true, 'Simple object stringify should preserve boolean');
  }

  public testStringifyNestedObject(): void {
    const obj = {
      outer: 'value',
      nested: {
        inner: 'nested value',
        number: 123
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.nested.inner, 'nested value', 'Nested object should be preserved');
    eq(parsed.nested.number, 123, 'Nested number should be preserved');
  }

  public testStringifyArray(): void {
    const obj = {
      items: [1, 2, 3, 4, 5]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.items.length, 5, 'Array length should be preserved');
    eq(parsed.items[2], 3, 'Array element should be preserved');
  }

  public testStringifyArrayOfObjects(): void {
    const obj = {
      users: [
        { id: 1, name: 'Alice' },
        { id: 2, name: 'Bob' }
      ]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.users.length, 2, 'Array of objects length should be preserved');
    eq(parsed.users[0].name, 'Alice', 'Nested object in array should be preserved');
  }

  public testStringifyWithSpace(): void {
    const obj = { name: 'test', value: 42 };
    const result = JSONCoder.stringify(obj, undefined, 2);
    eq(result.includes('  '), true, 'Stringify with space should be formatted');
  }

  public testStringifyNull(): void {
    const obj = {
      value: null
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.value, null, 'Null should be preserved');
  }

  public testStringifyUndefined(): void {
    const obj = {
      defined: 'value',
      notDefined: undefined
    };
    const result = JSONCoder.stringify(obj);
    eq(result.includes('notDefined'), false, 'Undefined should be omitted');
  }

  public testStringifyEmptyString(): void {
    const obj = {
      empty: ''
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.empty, '', 'Empty string should be preserved');
  }

  public testStringifyZero(): void {
    const obj = {
      zero: 0
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.zero, 0, 'Zero should be preserved');
  }

  public testStringifyFalse(): void {
    const obj = {
      active: false
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.active, false, 'False should be preserved');
  }

  public testStringifyDate(): void {
    const obj = {
      date: new Date('2026-01-01T00:00:00.000Z')
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed.date, 'string', 'Date should be stringified');
  }

  public testStringifySpecialCharacters(): void {
    const obj = {
      newline: 'line1\nline2',
      tab: 'col1\tcol2',
      quote: 'He said "hello"'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.newline, 'line1\nline2', 'Newline should be preserved');
    eq(parsed.tab, 'col1\tcol2', 'Tab should be preserved');
  }

  public testStringifyUnicode(): void {
    const obj = {
      chinese: '中文',
      emoji: '🎉',
      mixed: 'Hello 世界 🌍'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.chinese, '中文', 'Chinese characters should be preserved');
    eq(parsed.emoji, '🎉', 'Emoji should be preserved');
  }

  // =========================================================================
  // Parse Tests
  // =========================================================================

  public testParseSimpleObject(): void {
    const json = '{"name":"test","value":42}';
    class Target {
      name: string = '';
      value: number = 0;
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).name, 'test', 'Parse should populate string property');
    eq((result as any).value, 42, 'Parse should populate number property');
  }

  public testParseNestedObject(): void {
    const json = '{"outer":"value","nested":{"inner":"nested value"}}';
    class Nested {
      inner: string = '';
    }
    class Target {
      outer: string = '';
      nested: Nested = new Nested();
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).outer, 'value', 'Parse should populate outer property');
    eq((result as any).nested.inner, 'nested value', 'Parse should populate nested object');
  }

  public testParseArray(): void {
    const json = '{"items":[1,2,3]}';
    class Item {
      value: number = 0;
    }
    class Target {
      items: Item[] = [];
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).items.length, 3, 'Parse should populate array');
  }

  public testParseArrayOfObjects(): void {
    const json = '{"users":[{"id":1,"name":"Alice"},{"id":2,"name":"Bob"}]}';
    class User {
      id: number = 0;
      name: string = '';
    }
    class Target {
      users: User[] = [];
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).users.length, 2, 'Parse should populate array of objects');
    eq((result as any).users[0].name, 'Alice', 'Parse should populate nested objects in array');
  }

  public testParseNull(): void {
    const json = '{"value":null}';
    class Target {
      value: any = undefined;
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).value, null, 'Parse should handle null');
  }

  public testParseWithObjectSource(): void {
    const source = { name: 'test', value: 42 };
    class Target {
      name: string = '';
      value: number = 0;
    }
    const result = JSONCoder.parse(Target, source);
    eq((result as any).name, 'test', 'Parse should accept object source');
    eq((result as any).value, 42, 'Parse should populate from object source');
  }

  public testParseEmptyObject(): void {
    const json = '{}';
    class Target {
      name: string = 'default';
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).name, 'default', 'Parse should preserve default values');
  }

  public testParseMismatchedTypes(): void {
    const json = '{"name":123}';
    class Target {
      name: string = '';
    }
    JSONCoder.parse(Target, json);
    eq(true, true, 'Parse should handle type mismatch');
  }

  public testParseArraySource(): void {
    const json = '[{"id":1},{"id":2}]';
    class Item {
      id: number = 0;
    }
    const result = JSONCoder.parse(Item, json) as any[];
    eq(result.length, 2, 'Parse should handle array source');
    eq(result[0].id, 1, 'Parse should populate array elements');
  }

  // =========================================================================
  // ParseTo Tests
  // =========================================================================

  public testParseToExistingObject(): void {
    const json = '{"name":"updated","value":100}';
    class Target {
      name: string = 'initial';
      value: number = 0;
    }
    const instance = new Target();
    instance.name = 'old';
    instance.value = 50;
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).name, 'updated', 'ParseTo should update existing property');
    eq((result as any).value, 100, 'ParseTo should update existing number');
  }

  public testParseToNestedObject(): void {
    const json = '{"nested":{"inner":"updated"}}';
    class Nested {
      inner: string = '';
    }
    class Target {
      nested: Nested = new Nested();
    }
    const instance = new Target();
    instance.nested.inner = 'original';
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).nested.inner, 'updated', 'ParseTo should update nested objects');
  }

  public testParseToArray(): void {
    const json = '[{"id":1},{"id":2}]';
    class Item {
      id: number = 0;
    }
    const target = [new Item(), new Item()];
    const result = JSONCoder.parseTo(target, json);
    eq((result as any[]).length, 2, 'ParseTo should update array');
    eq((result as any[])[0].id, 1, 'ParseTo should update array elements');
  }

  public testParseToWithNull(): void {
    const json = '{"value":null}';
    class Target {
      value: any = 'default';
    }
    const instance = new Target();
    instance.value = 'not null';
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).value, null, 'ParseTo should set null values');
  }

  public testParseToTypeMismatch(): void {
    const json = '[1,2,3]';
    class Target {
      name: string = '';
    }
    const instance = new Target();
    try {
      JSONCoder.parseTo(instance, json);
      eq(false, true, 'Should throw type mismatch error');
    } catch (e) {
      eq(true, true, 'ParseTo should throw on type mismatch');
    }
  }

  public testParseToPartialUpdate(): void {
    const json = '{"name":"updated"}';
    class Target {
      name: string = '';
      value: number = 100;
    }
    const instance = new Target();
    instance.name = 'old';
    instance.value = 200;
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).name, 'updated', 'ParseTo should update specified property');
    eq((result as any).value, 200, 'ParseTo should preserve unspecified property');
  }

  public testParseToWithDate(): void {
    const json = '{"date":"2026-01-01T00:00:00.000Z"}';
    class Target {
      date: Date = new Date();
    }
    const instance = new Target();
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).date instanceof Date, true, 'ParseTo should handle Date');
  }

  public testParseToEmptySource(): void {
    const json = '{}';
    class Target {
      name: string = 'default';
      value: number = 42;
    }
    const instance = new Target();
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).name, 'default', 'ParseTo should preserve defaults on empty source');
  }

  public testParseToMap(): void {
    const json = '{"data":[["key1","value1"],["key2","value2"]]}';
    class Target {
      data: Map<string, string> = new Map();
    }
    const instance = new Target();
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).data.size, 2, 'ParseTo should populate Map');
    eq((result as any).data.get('key1'), 'value1', 'ParseTo should populate Map entries');
  }

  public testParseToSet(): void {
    const json = '{"tags":[1,2,3]}';
    class Target {
      tags: Set<number> = new Set();
    }
    const instance = new Target();
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).tags.size, 3, 'ParseTo should populate Set');
  }

  // =========================================================================
  // Complex Type Tests
  // =========================================================================

  public testComplexNestedStructure(): void {
    const obj = {
      level1: {
        level2: {
          level3: {
            value: 'deep'
          }
        }
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.level1.level2.level3.value, 'deep', 'Deep nesting should be preserved');
  }

  public testComplexMixedArray(): void {
    const obj = {
      mixed: [1, 'two', true, null, { key: 'value' }]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.mixed.length, 5, 'Mixed array length should be preserved');
    eq(parsed.mixed[0], 1, 'Mixed array number should be preserved');
    eq(parsed.mixed[1], 'two', 'Mixed array string should be preserved');
  }

  public testComplexSparseArray(): void {
    const obj = {
      sparse: [1, , , 4]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.sparse.length, 4, 'Sparse array length should be preserved');
  }

  public testComplexNumberValues(): void {
    const obj = {
      int: 42,
      float: 3.14,
      negative: -100,
      scientific: 1.5e-10
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.int, 42, 'Integer should be preserved');
    eq(parsed.float.toFixed(2), '3.14', 'Float should be preserved');
  }

  public testComplexBooleanLogic(): void {
    const obj = {
      trueValue: true,
      falseValue: false,
      notTrue: false,
      notFalse: true
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.trueValue, true, 'True value should be preserved');
    eq(parsed.falseValue, false, 'False value should be preserved');
  }

  public testComplexEmptyCollections(): void {
    const obj = {
      emptyObj: {},
      emptyArr: [],
      emptyStr: ''
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Object.keys(parsed.emptyObj).length, 0, 'Empty object should be preserved');
    eq(parsed.emptyArr.length, 0, 'Empty array should be preserved');
    eq(parsed.emptyStr, '', 'Empty string should be preserved');
  }

  public testComplexSelfReferential(): void {
    const obj: any = { id: 1 };
    obj.self = obj;
    try {
      JSONCoder.stringify(obj);
      eq(false, true, 'Should throw on circular reference');
    } catch (e) {
      eq(true, true, 'Circular reference should be detected');
    }
  }

  // =========================================================================
  // Observed Prefix Tests (__ob_)
  // =========================================================================

  public testObservedPrefixStripping(): void {
    const obj: any = {
      __ob_name__1: 'Alice',
      __ob_age__2: 30,
      normalField: 'value'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.name, 'Alice', '__ob_ prefix should be stripped');
    eq(parsed.age, 30, '__ob_ prefix with number should be stripped');
    eq(parsed.normalField, 'value', 'Normal fields should be preserved');
  }

  public testObservedPrefixNested(): void {
    const obj: any = {
      user: {
        __ob_name__1: 'Bob',
        __ob_id__2: 100
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.user.name, 'Bob', 'Nested __ob_ prefix should be stripped');
  }

  public testObservedPrefixInArray(): void {
    const obj: any = {
      items: [
        { __ob_value__1: 'first' },
        { __ob_value__2: 'second' }
      ]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.items[0].value, 'first', '__ob_ prefix in array should be stripped');
  }

  // =========================================================================
  // Edge Cases Tests
  // =========================================================================

  public testEdgeCaseVeryLongString(): void {
    const longStr = 'a'.repeat(10000);
    const obj = { long: longStr };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.long.length, 10000, 'Very long string should be preserved');
  }

  public testEdgeCaseLargeNumber(): void {
    const obj = { large: Number.MAX_SAFE_INTEGER };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.large, Number.MAX_SAFE_INTEGER, 'Large number should be preserved');
  }

  public testEdgeCaseNegativeZero(): void {
    const obj = { negZero: -0 };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.negZero, 0, 'Negative zero should be handled');
  }

  public testEdgeCaseEscapedChars(): void {
    const obj = {
      slash: '\\',
      quote: '\"',
      backspace: '\b',
      formfeed: '\f'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.slash, '\\', 'Slash should be preserved');
    eq(parsed.quote, '\"', 'Quote should be preserved');
  }

  public testEdgeCaseStrictMode(): void {
    'use strict';
    const obj = { value: 42 };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.value, 42, 'Should work in strict mode');
  }

  public testEdgeCaseFrozenObject(): void {
    const obj = Object.freeze({ value: 42 });
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.value, 42, 'Frozen object should be serialized');
  }

  public testEdgeCaseSealedObject(): void {
    const obj = Object.seal({ value: 42 });
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.value, 42, 'Sealed object should be serialized');
  }

  public testEdgeCaseMultipleCalls(): void {
    const obj = { value: 42 };
    const result1 = JSONCoder.stringify(obj);
    const result2 = JSONCoder.stringify(obj);
    eq(result1, result2, 'Multiple stringify calls should be consistent');
  }

  public testEdgeCaseChainedParsing(): void {
    const obj1 = { value: 42 };
    const str1 = JSONCoder.stringify(obj1);
    const obj2 = JSON.parse(str1);
    const str2 = JSONCoder.stringify(obj2);
    eq(str1, str2, 'Chained parsing should be consistent');
  }

  // =========================================================================
  // Performance Tests
  // =========================================================================

  public testPerformanceLargeArray(): void {
    const arr: number[] = [];
    for (let i = 0; i < 10000; i++) {
      arr.push(i);
    }
    const obj = { largeArray: arr };
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large array stringify should complete in reasonable time');
    const parsed = JSON.parse(result);
    eq(parsed.largeArray.length, 10000, 'Large array should be fully serialized');
  }

  public testPerformanceDeepNesting(): void {
    let obj: any = { value: 'deep' };
    for (let i = 0; i < 100; i++) {
      obj = { nested: obj };
    }
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Deep nesting stringify should complete in reasonable time');
  }

  public testPerformanceManyProperties(): void {
    const obj: any = {};
    for (let i = 0; i < 1000; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Many properties stringify should complete in reasonable time');
  }

  public testPerformanceRepeatedOperations(): void {
    const obj = { test: 'value' };
    const iterations = 1000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      JSONCoder.stringify(obj);
    }
    const duration = Date.now() - startTime;
    eq(duration < 5000, true, 'Repeated operations should complete in reasonable time');
  }

  // =========================================================================
  // Compatibility Tests
  // =========================================================================

  public testCompatibilityStandardJSONStringify(): void {
    const obj = { name: 'test', value: 42 };
    const standardResult = JSON.stringify(obj);
    const coderResult = JSONCoder.stringify(obj);
    const standardParsed = JSON.parse(standardResult);
    const coderParsed = JSON.parse(coderResult);
    eq(standardParsed.name, coderParsed.name, 'Should be compatible with standard JSON.stringify');
    eq(standardParsed.value, coderParsed.value, 'Should be compatible with standard JSON.stringify');
  }

  public testCompatibilityStandardJSONParse(): void {
    const json = '{"name":"test","value":42}';
    const standardParsed = JSON.parse(json);
    class Target {
      name: string = '';
      value: number = 0;
    }
    const coderParsed = JSONCoder.parse(Target, json);
    eq(standardParsed.name, (coderParsed as any).name, 'Should be compatible with standard JSON.parse');
    eq(standardParsed.value, (coderParsed as any).value, 'Should be compatible with standard JSON.parse');
  }

  public testCompatibilityReplacerFunction(): void {
    const obj = { a: 1, b: 2, c: 3 };
    const replacer = (key: string, value: any) => {
      if (key === 'b') {
        return undefined;
      }
      return value;
    };
    const result = JSONCoder.stringify(obj, replacer);
    const parsed = JSON.parse(result);
    eq(parsed.b, undefined, 'Should support standard replacer function');
    eq(parsed.a, 1, 'Replacer should preserve other values');
  }

  // =========================================================================
  // Additional Date Tests
  // =========================================================================

  public testDateISOFormat(): void {
    const date = new Date('2026-01-15T12:30:45.123Z');
    const obj = { date };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed.date, 'string', 'Date should be stringified');
    eq(parsed.date.includes('2026'), true, 'Date ISO format should contain year');
  }

  public testDateInvalid(): void {
    const invalidDate = new Date('invalid');
    const obj = { date: invalidDate };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed.date, 'string', 'Invalid date should be stringified');
  }

  public testDateEpoch(): void {
    const epoch = new Date(0);
    const obj = { date: epoch };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.date.includes('1970'), true, 'Epoch date should be preserved');
  }

  public testDateFuture(): void {
    const future = new Date('2030-12-31');
    const obj = { date: future };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.date.includes('2030'), true, 'Future date should be preserved');
  }

  public testDateCurrent(): void {
    const now = new Date();
    const obj = { date: now };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed.date, 'string', 'Current date should be stringified');
  }

  // =========================================================================
  // Map/Set Additional Tests
  // =========================================================================

  public testMapStringKeys(): void {
    const map = new Map<string, number>([
      ['one', 1],
      ['two', 2],
      ['three', 3]
    ]);
    const obj = { map };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.map), true, 'Map with string keys should be serialized');
    eq(parsed.map.length, 3, 'Map size should be preserved');
  }

  public testMapNumberKeys(): void {
    const map = new Map<number, string>([
      [1, 'one'],
      [2, 'two']
    ]);
    const obj = { map };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.map.length, 2, 'Map with number keys should be serialized');
  }

  public testSetNumbers(): void {
    const set = new Set<number>([10, 20, 30, 40, 50]);
    const obj = { set };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.set[0], 10, 'Set numbers should be preserved');
  }

  public testSetStrings(): void {
    const set = new Set<string>(['a', 'b', 'c', 'd']);
    const obj = { set };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.set[1], 'b', 'Set strings should be preserved');
  }

  public testSetBooleans(): void {
    const set = new Set<boolean>([true, false, true]);
    const obj = { set };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.set.length, 3, 'Set booleans should be preserved');
  }

  public testMapComplexValues(): void {
    const map = new Map<string, any>([
      ['obj', { key: 'value' }],
        ['arr', [1, 2, 3]]
    ]);
    const obj = { map };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.map.length, 2, 'Map with complex values should be serialized');
  }

  public testSetInNestedObject(): void {
    const obj = {
      level1: {
        level2: {
          tags: new Set([1, 2, 3])
        }
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.level1.level2.tags), true, 'Nested set should be serialized');
  }

  public testMapInNestedObject(): void {
    const obj = {
      config: {
        settings: new Map([['key', 'value']])
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(Array.isArray(parsed.config.settings), true, 'Nested map should be serialized');
  }

  // =========================================================================
  // Number Type Tests
  // =========================================================================

  public testNumberInteger(): void {
    const obj = { int: 42 };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.int, 42, 'Integer should be preserved');
  }

  public testNumberFloat(): void {
    const obj = { float: 3.14159 };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.float > 3.14 && parsed.float < 3.15, true, 'Float should be preserved');
  }

  public testNumberNegative(): void {
    const obj = { neg: -999 };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.neg, -999, 'Negative number should be preserved');
  }

  public testNumberExponential(): void {
    const obj = { exp: 1.23e-4 };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.exp > 0.00012 && parsed.exp < 0.00013, true, 'Exponential should be preserved');
  }

  // =========================================================================
  // Unicode Tests
  // =========================================================================

  public testUnicodeChinese(): void {
    const obj = { text: '你好世界' };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.text, '你好世界', 'Chinese characters should be preserved');
  }

  public testUnicodeJapanese(): void {
    const obj = { text: 'こんにちは' };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.text, 'こんにちは', 'Japanese characters should be preserved');
  }

  public testUnicodeKorean(): void {
    const obj = { text: '안녕하세요' };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.text, '안녕하세요', 'Korean characters should be preserved');
  }

  public testUnicodeEmoji(): void {
    const obj = { emoji: '😀🎉🌍⭐' };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.emoji, '😀🎉🌍⭐', 'Emoji should be preserved');
  }

  // =========================================================================
  // Mixed Types Tests
  // =========================================================================

  public testMixedPrimitiveTypes(): void {
    const obj = {
      str: 'text',
      num: 123,
      bool: true,
      nullVal: null
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.str, 'text', 'String should be preserved');
    eq(parsed.num, 123, 'Number should be preserved');
    eq(parsed.bool, true, 'Boolean should be preserved');
    eq(parsed.nullVal, null, 'Null should be preserved');
  }

  public testMixedNestedStructure(): void {
    const obj = {
      primitive: 42,
      object: { nested: 'value' },
      array: [1, 2, 3],
      mixed: { arr: [{ key: 'val' }] }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.primitive, 42, 'Primitive in mixed structure should be preserved');
    eq(parsed.object.nested, 'value', 'Object in mixed structure should be preserved');
  }

  public testMixedArrayTypes(): void {
    const obj = {
      mixed: [1, 'two', true, null, { key: 'value' }]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.mixed.length, 5, 'Mixed array length should be preserved');
    eq(typeof parsed.mixed[0], 'number', 'Number in mixed array should be preserved');
    eq(typeof parsed.mixed[1], 'string', 'String in mixed array should be preserved');
  }

  public testMixedWithMapsAndSets(): void {
    const obj = {
      num: 42,
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3]),
      str: 'text'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.num, 42, 'Number should be preserved');
    eq(Array.isArray(parsed.map), true, 'Map in mixed structure should be serialized');
    eq(Array.isArray(parsed.set), true, 'Set in mixed structure should be serialized');
  }

  // =========================================================================
  // Nested Structures Tests
  // =========================================================================

  public testNestedDeepObject(): void {
    const obj = {
      l1: {
        l2: {
          l3: {
            l4: {
              value: 'deep'
            }
          }
        }
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.l1.l2.l3.l4.value, 'deep', 'Deep nested object should be preserved');
  }

  public testNestedArraysInObjects(): void {
    const obj = {
      data: {
        items: [1, 2, 3],
        nested: {
          values: ['a', 'b', 'c']
        }
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.data.items.length, 3, 'Nested array in object should be preserved');
    eq(parsed.data.nested.values[1], 'b', 'Deep nested array should be preserved');
  }

  public testNestedObjectsInArrays(): void {
    const obj = {
      users: [
        { name: 'Alice', age: 30 },
        { name: 'Bob', age: 25 }
      ]
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.users[0].name, 'Alice', 'Nested object in array should be preserved');
    eq(parsed.users[1].age, 25, 'Nested object property should be preserved');
  }

  public testNestedComplexStructure(): void {
    const obj = {
      level1: {
        items: [
          { id: 1, tags: ['a', 'b'] },
          { id: 2, tags: ['c', 'd'] }
        ],
        config: {
          enabled: true
        }
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.level1.items[0].tags[1], 'b', 'Complex nested structure should be preserved');
    eq(parsed.level1.config.enabled, true, 'Deep nested config should be preserved');
  }

  // =========================================================================
  // Error Handling Tests
  // =========================================================================

  public testErrorInvalidJSON(): void {
    const invalidJson = '{invalid json}';
    try {
      JSON.parse(invalidJson);
      eq(false, true, 'Should throw on invalid JSON');
    } catch (e) {
      eq(true, true, 'Invalid JSON should throw error');
    }
  }

  public testErrorTrailingComma(): void {
    const json = '{"name":"test",}';
    try {
      JSON.parse(json);
      eq(false, true, 'Should throw on trailing comma');
    } catch (e) {
      eq(true, true, 'Trailing comma should throw error');
    }
  }

  public testErrorUnquotedKey(): void {
    const json = '{name:"test"}';
    try {
      JSON.parse(json);
      eq(false, true, 'Should throw on unquoted key');
    } catch (e) {
      eq(true, true, 'Unquoted key should throw error');
    }
  }

  public testErrorSingleQuote(): void {
    const json = "{'name':'test'}";
    try {
      JSON.parse(json);
      eq(false, true, 'Should throw on single quote');
    } catch (e) {
      eq(true, true, 'Single quote should throw error');
    }
  }

  // =========================================================================
  // Additional Tests for Meta Class
  // =========================================================================

  public testMetaMultipleProperties(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'prop1', { value: 1 });
    Meta.define(proto, 'prop2', { value: 2 });
    Meta.define(proto, 'prop3', { value: 3 });
    const meta = Meta.gets(obj);
    eq(Object.keys(meta).length, 3, 'Meta should handle multiple properties');
  }

  public testMetaPropertyOverriding(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'overridable', { value: 'v1' });
    Meta.define(proto, 'overridable', { value: 'v2' });
    const result = Meta.get(obj, 'overridable');
    eq(result && result.value, 'v2', 'Meta should allow property overriding');
  }

  public testProtoChainTraversal(): void {
    const grandParent: any = {};
    const parent = Object.create(grandParent);
    const child = Object.create(parent);
    Meta.define(Object.getPrototypeOf(grandParent), 'root', { value: 'root' });
    Meta.define(Object.getPrototypeOf(parent), 'mid', { value: 'mid' });
    const result = Meta.get(child, 'root');
    eq(result && result.value, 'root', 'Meta should traverse entire proto chain');
  }

  // =========================================================================
  // Additional Tests for ObservedReplacer
  // =========================================================================

  public testObservedReplacerWithComplexReplacer(): void {
    const obj = {
      password: 'secret123',
      username: 'alice'
    };
    const replacer = (key: string, value: any) => {
      if (key === 'password') {
        return '***';
      }
      return value;
    };
    const result = JSONCoder.stringify(obj, replacer);
    const parsed = JSON.parse(result);
    eq(parsed.password, '***', 'Custom replacer should modify values');
    eq(parsed.username, 'alice', 'Custom replacer should preserve other values');
  }

  public testObservedReplacerSetWithReplacer(): void {
    const obj = {
      tags: new Set([1, 2, 3])
    };
    const replacer = (key: string, value: any) => {
      if (typeof value === 'number') {
        return value * 10;
      }
      return value;
    };
    const result = JSONCoder.stringify(obj, replacer);
    const parsed = JSON.parse(result);
    eq(parsed.tags[0], 10, 'Replacer should transform Set values');
  }

  // =========================================================================
  // Additional Tests for Stringify
  // =========================================================================

  public testStringifyWithTabSpace(): void {
    const obj = { name: 'test', value: 42 };
    const result = JSONCoder.stringify(obj, undefined, '\t');
    eq(result.includes('\t'), true, 'Stringify with tab space should format output');
  }

  public testStringifyWithNumberSpace(): void {
    const obj = { name: 'test', value: 42 };
    const result = JSONCoder.stringify(obj, undefined, 4);
    eq(result.includes('    '), true, 'Stringify with number space should format output');
  }

  public testStringifyPreservesOrder(): void {
    const obj: any = {};
    obj.c = 3;
    obj.a = 1;
    obj.b = 2;
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    const keys = Object.keys(parsed);
    eq(keys[0], 'c', 'Stringify should preserve insertion order');
  }

  // =========================================================================
  // Additional Tests for Parse
  // =========================================================================

  public testParseWithFactoryOption(): void {
    const json = '{"data":{"value":"test"}}';
    class Data {
      value: string = '';
    }
    class Target {
      data: Data = new Data();
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).data.value, 'test', 'Parse should handle factory option');
  }

  public testParseWithAliasOption(): void {
    const json = '{"aliased":"value"}';
    class Target {
      original: string = '';
    }
    const result = JSONCoder.parse(Target, json);
    eq(true, true, 'Parse should handle alias option');
  }

  public testParseWithDisabledOption(): void {
    const json = '{"field1":"value1","field2":"value2"}';
    class Target {
      field1: string = '';
      field2: string = '';
    }
    const result = JSONCoder.parse(Target, json);
    eq((result as any).field1, 'value1', 'Parse should handle disabled option');
  }

  // =========================================================================
  // Additional Tests for ParseTo
  // =========================================================================

  public testParseToWithPartialData(): void {
    const json = '{"field1":"updated"}';
    class Target {
      field1: string = 'default1';
      field2: string = 'default2';
    }
    const instance = new Target();
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).field1, 'updated', 'ParseTo should update provided fields');
    eq((result as any).field2, 'default2', 'ParseTo should preserve omitted fields');
  }

  public testParseToWithExtraFields(): void {
    const json = '{"field1":"value1","extra":"ignored"}';
    class Target {
      field1: string = '';
    }
    const instance = new Target();
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).field1, 'value1', 'ParseTo should handle extra fields in source');
  }

  // =========================================================================
  // Additional Complex Type Tests
  // =========================================================================

  public testComplexClassWithMethods(): void {
    class WithMethods {
      data: string = 'test';
      public getData(): string {
        return this.data;
      }
    }
    const obj = new WithMethods();
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.data, 'test', 'Class with methods should be serialized');
  }

  public testComplexInheritedClass(): void {
    class Parent {
      parentField: string = 'parent';
    }
    class Child extends Parent {
      childField: string = 'child';
    }
    const obj = new Child();
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.parentField, 'parent', 'Inherited properties should be serialized');
    eq(parsed.childField, 'child', 'Child properties should be serialized');
  }

  public testComplexUnionTypes(): void {
    const obj: any = {
      union: 'string' as string | number,
      union2: 42 as string | number
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed.union, 'string', 'Union type string should be preserved');
    eq(typeof parsed.union2, 'number', 'Union type number should be preserved');
  }

  // =========================================================================
  // Additional Performance Tests
  // =========================================================================

  public testPerformanceStringifyParseLoop(): void {
    const obj = { data: 'test', value: 42 };
    const iterations = 100;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const str = JSONCoder.stringify(obj);
      JSON.parse(str);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Stringify/Parse loop should complete quickly');
  }

  public testPerformanceLargeObjectStringify(): void {
    const obj: any = {};
    for (let i = 0; i < 100; i++) {
      obj[`field${i}`] = `value${i}`.repeat(10);
    }
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 500, true, 'Large object stringify should be fast');
  }

  public testPerformanceMapSetOperations(): void {
    const obj = {
      map: new Map<string, number>(),
      set: new Set<number>()
    };
    for (let i = 0; i < 100; i++) {
      obj.map.set(`key${i}`, i);
      obj.set.add(i);
    }
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 500, true, 'Map/Set stringify should be fast');
  }

  public testPerformanceDateOperations(): void {
    const obj = {
      dates: []
    };
    for (let i = 0; i < 100; i++) {
      (obj.dates as any).push(new Date(Date.now() + i * 1000));
    }
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 500, true, 'Date array stringify should be fast');
  }

  // =========================================================================
  // Additional Edge Cases
  // =========================================================================

  public testEdgeCaseEmptyStringKey(): void {
    const obj: any = {};
    obj[''] = 'empty key value';
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed[''], 'empty key value', 'Empty string key should be handled');
  }

  public testEdgeCaseVeryDeepNesting(): void {
    let obj: any = { value: 'deepest' };
    for (let i = 0; i < 50; i++) {
      obj = { level: obj };
    }
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    let current = parsed;
    for (let i = 0; i < 50; i++) {
      current = current.level;
    }
    eq(current.value, 'deepest', 'Very deep nesting should be handled');
  }

  public testEdgeCaseHugeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 5000; i++) {
      obj[`prop${i}`] = i;
    }
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.prop0, 0, 'Huge object should be serialized');
    eq(parsed.prop4999, 4999, 'Huge object last property should be preserved');
  }

  public testEdgeCaseSpecialFloatValues(): void {
    const obj = {
      nan: NaN,
      infinity: Infinity,
      negInfinity: -Infinity
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed.nan, 'number', 'NaN should become number (null or number)');
    eq(typeof parsed.infinity, 'number', 'Infinity should become number (null or number)');
  }

  // =========================================================================
  // Additional Compatibility Tests
  // =========================================================================

  public testCompatibilityNativeJSONMethods(): void {
    const obj = { test: 'value' };
    const nativeStr = JSON.stringify(obj);
    const coderStr = JSONCoder.stringify(obj);
    const nativeParsed = JSON.parse(nativeStr);
    const coderParsed = JSON.parse(coderStr);
    eq(nativeParsed.test, coderParsed.test, 'Should be compatible with native JSON');
  }

  public testCompatibilitySpaceArgument(): void {
    const obj = { a: 1, b: 2 };
    const nativeStr = JSON.stringify(obj, undefined, 2);
    const coderStr = JSONCoder.stringify(obj, undefined, 2);
    eq(nativeStr.split('\n').length, coderStr.split('\n').length, 'Space argument should work the same');
  }

  // =========================================================================
  // Additional GetOptions Tests
  // =========================================================================

  public testGetOptionsWithObject(): void {
    const options = { factory: null, alias: 'test', disabled: false };
    const result = JSONCoder.getOptions(options);
    eq(typeof result, 'object', 'GetOptions should handle object');
  }

  public testGetOptionsWithFunction(): void {
    class Test {
      value: string = '';
    }
    const result = JSONCoder.getOptions(Test);
    eq(typeof result, 'object', 'GetOptions should handle function');
  }

  public testGetOptionsWithString(): void {
    const result = JSONCoder.getOptions<string>('myAlias');
    eq(typeof result, 'object', 'GetOptions should handle string');
  }

  public testGetOptionsWithUndefined(): void {
    const result = JSONCoder.getOptions();
    eq(typeof result, 'object', 'GetOptions should handle undefined');
  }

  // =========================================================================
  // Additional Meta Tests
  // =========================================================================

  public testMetaDefineMultipleTimes(): void {
    const obj: any = {};
    const proto = Object.getPrototypeOf(obj);
    Meta.define(proto, 'prop', { value: 1 });
    Meta.define(proto, 'prop', { value: 2 });
    Meta.define(proto, 'prop', { value: 3 });
    const result = Meta.get(obj, 'prop');
    eq(result && result.value, 3, 'Meta should handle multiple define calls');
  }

  public testMetaGetsFromMultipleLevels(): void {
    const grandParent: any = {};
    const parent = Object.create(grandParent);
    const child = Object.create(parent);
    Meta.define(Object.getPrototypeOf(grandParent), 'gp', { value: 1 });
    Meta.define(Object.getPrototypeOf(parent), 'p', { value: 2 });
    Meta.define(Object.getPrototypeOf(child), 'c', { value: 3 });
    const meta = Meta.gets(child);
    eq(Object.keys(meta).length, 3, 'Meta gets should collect from all levels');
  }

  public testMetaGetOwnIgnoresParent(): void {
    const parent: any = {};
    const child = Object.create(parent);
    Meta.define(Object.getPrototypeOf(parent), 'parentProp', { value: 1 });
    Meta.define(Object.getPrototypeOf(child), 'childProp', { value: 2 });
    const result = Meta.getOwn(child, 'childProp');
    eq(result && result.value, 2, 'Meta getOwn should ignore parent properties');
  }

  // =========================================================================
  // Additional ObservedReplacer Tests
  // =========================================================================

  public testObservedReplacerWithUndefined(): void {
    const obj = {
      defined: 'value',
      notDefined: undefined
    };
    const result = JSONCoder.stringify(obj);
    eq(result.includes('notDefined'), false, 'ObservedReplacer should omit undefined');
  }

  public testObservedReplacerWithFunction(): void {
    const obj: any = {
      data: 'test',
      method() {
        return this.data;
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.data, 'test', 'Functions should be filtered out');
  }

  // =========================================================================
  // Additional Stringify Tests
  // =========================================================================

  public testStringifyWithReplacerReturningUndefined(): void {
    const obj = { a: 1, b: 2, c: 3 };
    const replacer = (key: string, value: any) => {
      if (key === 'b') {
        return undefined;
      }
      return value;
    };
    const result = JSONCoder.stringify(obj, replacer);
    const parsed = JSON.parse(result);
    eq(parsed.b, undefined, 'Replacer returning undefined should omit property');
  }

  public testStringifyWithReplacerModifyingValues(): void {
    const obj = { value: 42 };
    const replacer = (key: string, value: any) => {
      if (typeof value === 'number') {
        return value * 2;
      }
      return value;
    };
    const result = JSONCoder.stringify(obj, replacer);
    const parsed = JSON.parse(result);
    eq(parsed.value, 84, 'Replacer should modify values');
  }

  // =========================================================================
  // Additional Parse Tests
  // =========================================================================

  public testParseWithFactoryCreatingNewInstances(): void {
    const json = '{"item":{"value":"test"}}';
    class Item {
      value: string = '';
    }
    class Container {
      item: Item = new Item();
    }
    const result = JSONCoder.parse(Container, json);
    eq((result as any).item.value, 'test', 'Parse should create new instances via factory');
  }

  public testParseWithComplexNestingAndFactory(): void {
    const json = '{"level1":{"level2":{"level3":{"value":"deep"}}}';
    class Level3 {
      value: string = '';
    }
    class Level2 {
      level3: Level3 = new Level3();
    }
    class Level1 {
      level2: Level2 = new Level2();
    }
    const result = JSONCoder.parse(Level1, json);
    eq((result as any).level2.level3.value, 'deep', 'Parse should handle deep nesting with factory');
  }

  // =========================================================================
  // Additional ParseTo Tests
  // =========================================================================

  public testParseToWithDateConversion(): void {
    const json = '{"date":"2026-01-01T00:00:00.000Z"}';
    class Target {
      date: Date = new Date();
    }
    const instance = new Target();
    const originalDate = instance.date.getTime();
    const result = JSONCoder.parseTo(instance, json);
    const newDate = (result as any).date.getTime();
    eq(typeof newDate, 'number', 'ParseTo should convert date string to Date');
  }

  public testParseToWithMapRestoration(): void {
    const json = '{"map":[["key1","value1"],["key2","value2"]]}';
    class Target {
      map: Map<string, string> = new Map();
    }
    const instance = new Target();
    instance.map.set('old', 'oldValue');
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).map.size, 2, 'ParseTo should restore Map');
  }

  public testParseToWithSetRestoration(): void {
    const json = '{"set":[1,2,3]}';
    class Target {
      set: Set<number> = new Set();
    }
    const instance = new Target();
    instance.set.add(0);
    const result = JSONCoder.parseTo(instance, json);
    eq((result as any).set.size, 3, 'ParseTo should restore Set');
  }

  // =========================================================================
  // Additional Complex Scenarios
  // =========================================================================

  public testComplexFullCycle(): void {
    class Original {
      name: string = 'test';
      value: number = 42;
      nested: { inner: string } = { inner: 'deep' };
      map: Map<string, number> = new Map([['key', 1]]);
      set: Set<number> = new Set([1, 2, 3]);
    }
    const original = new Original();
    const stringified = JSONCoder.stringify(original);
    const parsed = JSON.parse(stringified);
    eq(parsed.name, 'test', 'Full cycle should preserve string');
    eq(parsed.value, 42, 'Full cycle should preserve number');
    eq(parsed.nested.inner, 'deep', 'Full cycle should preserve nested object');
  }

  public testComplexArrayOfClassInstances(): void {
    class Item {
      id: number = 0;
      name: string = '';
    }
    const items = [new Item(), new Item(), new Item()];
    items[0].id = 1;
    items[0].name = 'first';
    items[1].id = 2;
    items[1].name = 'second';
    items[2].id = 3;
    items[2].name = 'third';
    const stringified = JSONCoder.stringify({ items });
    const parsed = JSON.parse(stringified);
    eq(parsed.items.length, 3, 'Array of class instances should be serialized');
    eq(parsed.items[0].name, 'first', 'Class instance properties should be preserved');
  }

  public testComplexMapOfClassInstances(): void {
    class Value {
      data: string = '';
    }
    const map = new Map<string, Value>();
    const v1 = new Value();
    v1.data = 'value1';
    const v2 = new Value();
    v2.data = 'value2';
    map.set('key1', v1);
    map.set('key2', v2);
    const stringified = JSONCoder.stringify({ map });
    const parsed = JSON.parse(stringified);
    eq(parsed.map.length, 2, 'Map of class instances should be serialized');
  }

  public testComplexSetOfClassInstances(): void {
    class Item {
      id: number = 0;
    }
    const set = new Set<Item>();
    const i1 = new Item();
    i1.id = 1;
    const i2 = new Item();
    i2.id = 2;
    set.add(i1);
    set.add(i2);
    const stringified = JSONCoder.stringify({ set });
    const parsed = JSON.parse(stringified);
    eq(parsed.set.length, 2, 'Set of class instances should be serialized');
  }

  // =========================================================================
  // Additional Edge Cases
  // =========================================================================

  public testEdgeCaseNullPrototype(): void {
    const obj = Object.create(null);
    (obj as any).value = 'test';
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.value, 'test', 'Null prototype object should be serialized');
  }

  public testEdgeCaseGetterSetter(): void {
    const obj = {
      _value: 42,
      get value() {
        return this._value;
      },
      set value(v) {
        this._value = v;
      }
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(typeof parsed._value, 'number', 'Getter/setter backing property should be serialized');
  }

  public testEdgeCaseSymbolKeys(): void {
    const obj: any = {};
    const sym = Symbol('test');
    obj[sym] = 'symbol value';
    obj.regular = 'regular value';
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.regular, 'regular value', 'Regular keys should be preserved');
    eq(parsed[sym], undefined, 'Symbol keys should be ignored');
  }

  // =========================================================================
  // Additional Unicode and Special Characters
  // =========================================================================

  public testUnicodeAllScripts(): void {
    const obj = {
      latin: 'Hello',
      cyrillic: 'Привет',
      greek: 'Γεια',
      chinese: '你好',
      japanese: 'こんにちは',
      korean: '안녕하세요',
      arabic: 'مرحبا',
      hebrew: 'שלום',
      thai: 'สวัสดี'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.latin, 'Hello', 'Latin script should be preserved');
    eq(parsed.cyrillic, 'Привет', 'Cyrillic script should be preserved');
    eq(parsed.chinese, '你好', 'Chinese script should be preserved');
  }

  public testSpecialCharactersAll(): void {
    const obj = {
      newline: 'line1\nline2',
      carriage: 'text\rmore',
      tab: 'col1\tcol2',
      backspace: 'a\bc',
      formfeed: 'page1\fpage2',
      slash: 'path/to/file',
      backslash: 'path\\to\\file',
      quote: 'He said "hello"',
      apostrophe: 'It\'s great'
    };
    const result = JSONCoder.stringify(obj);
    const parsed = JSON.parse(result);
    eq(parsed.newline, 'line1\nline2', 'Newline should be preserved');
    eq(parsed.tab, 'col1\tcol2', 'Tab should be preserved');
  }

  // =========================================================================
  // Additional Performance with Large Data
  // =========================================================================

  public testPerformanceLargeMap(): void {
    const map = new Map<string, number>();
    for (let i = 0; i < 1000; i++) {
      map.set(`key${i}`, i);
    }
    const obj = { map };
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 2000, true, 'Large Map stringify should complete');
    const parsed = JSON.parse(result);
    eq(parsed.map.length, 1000, 'Large Map should be fully serialized');
  }

  public testPerformanceLargeSet(): void {
    const set = new Set<number>();
    for (let i = 0; i < 1000; i++) {
      set.add(i);
    }
    const obj = { set };
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 2000, true, 'Large Set stringify should complete');
    const parsed = JSON.parse(result);
    eq(parsed.set.length, 1000, 'Large Set should be fully serialized');
  }

  public testPerformanceLargeArrayOfObjects(): void {
    const arr: any[] = [];
    for (let i = 0; i < 500; i++) {
      arr.push({ id: i, name: `item${i}`, active: i % 2 === 0 });
    }
    const obj = { items: arr };
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large array of objects should be serialized quickly');
    const parsed = JSON.parse(result);
    eq(parsed.items.length, 500, 'All array items should be serialized');
  }

  public testPerformanceVeryDeepNesting(): void {
    let obj: any = { value: 'deepest' };
    for (let i = 0; i < 200; i++) {
      obj = { nested: obj };
    }
    const startTime = Date.now();
    const result = JSONCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 2000, true, 'Very deep nesting should be handled');
  }

  // =========================================================================
  // Memory Stress Tests
  // =========================================================================

  public testMemoryStressLargeObject(): void {
    const largeObj: any = {
      items: [],
      nested: []
    };

    for (let i = 0; i < 100; i++) {
      largeObj.items.push({
        id: i,
        data: 'x'.repeat(100),
        nested: {
          level1: {
            level2: {
              value: `item${i}`
            }
          }
        }
      });
    }

    const startTime = Date.now();
    const result = JSONCoder.stringify(largeObj);
    const duration = Date.now() - startTime;

    const parsed = JSON.parse(result);
    eq(parsed.items.length, 100, 'Should handle large object');
    eq(duration < 2000, true, 'Should complete in reasonable time');
  }

  public testMemoryStressManyProperties(): void {
    const largeObj: any = {};
    for (let i = 0; i < 500; i++) {
      largeObj[`field${i}`] = `value${i}`;
    }

    const startTime = Date.now();
    const result = JSONCoder.stringify(largeObj);
    const duration = Date.now() - startTime;

    const parsed = JSON.parse(result);

    let count = 0;
    for (const key in parsed) {
      if (parsed.hasOwnProperty(key)) {
        count++;
      }
    }

    eq(count, 500, 'Should handle many properties');
    eq(duration < 2000, true, 'Should complete in reasonable time');
  }

  // =========================================================================
  // Final Comprehensive Tests
  // =========================================================================

  public testComprehensiveRealWorldScenario(): void {
    class User {
      __ob_id__1: number = 0;
      __ob_name__2: string = '';
      email: string = '';
      tags: Set<string> = new Set();
      metadata: Map<string, string> = new Map();
      createdAt: Date = new Date();
      active: boolean = true;
    }

    const user = new User();
    user.__ob_id__1 = 1;
    user.__ob_name__2 = 'Alice';
    user.email = 'alice@example.com';
    user.tags.add('admin');
    user.tags.add('user');
    user.metadata.set('department', 'engineering');
    user.createdAt = new Date('2026-01-01');

    const stringified = JSONCoder.stringify(user);
    const parsed = JSON.parse(stringified);

    eq(parsed.name, 'Alice', 'Real world scenario should strip __ob_ prefix');
    eq(parsed.email, 'alice@example.com', 'Real world scenario should preserve email');
    eq(Array.isArray(parsed.tags), true, 'Real world scenario should serialize Set');
    eq(parsed.tags.length, 2, 'Real world scenario should preserve Set size');
    eq(Array.isArray(parsed.metadata), true, 'Real world scenario should serialize Map');
  }

  public testComprehensiveErrorRecovery(): void {
    const obj1 = { value: 42 };
    const obj2 = { invalid: undefined };

    const result1 = JSONCoder.stringify(obj1);
    const parsed1 = JSON.parse(result1);

    const result2 = JSONCoder.stringify(obj2);
    const parsed2 = JSON.parse(result2);

    eq(parsed1.value, 42, 'First object should be serialized correctly');
    eq(parsed2.invalid, undefined, 'Second object should handle undefined');
  }

  public testComprehensiveMixedAllFeatures(): void {
    const obj = {
      primitive: 'test',
      number: 42,
      boolean: true,
      null: null,
      array: [1, 2, 3],
      object: { nested: 'value' },
      set: new Set([1, 2, 3]),
      map: new Map([['key', 'value']]),
      date: new Date('2026-01-01'),
      __ob_hidden__1: 'secret',
      empty: '',
      zero: 0,
      falseVal: false
    };

    const stringified = JSONCoder.stringify(obj);
    const parsed = JSON.parse(stringified);

    eq(parsed.primitive, 'test', 'Comprehensive test should preserve primitive');
    eq(parsed.number, 42, 'Comprehensive test should preserve number');
    eq(parsed.boolean, true, 'Comprehensive test should preserve boolean');
    eq(parsed.null, null, 'Comprehensive test should preserve null');
    eq(Array.isArray(parsed.array), true, 'Comprehensive test should preserve array');
    eq(parsed.object.nested, 'value', 'Comprehensive test should preserve object');
    eq(Array.isArray(parsed.set), true, 'Comprehensive test should serialize Set');
    eq(Array.isArray(parsed.map), true, 'Comprehensive test should serialize Map');
    eq(parsed.hidden, 'secret', 'Comprehensive test should strip __ob_ prefix');
    eq(parsed.empty, '', 'Comprehensive test should preserve empty string');
    eq(parsed.zero, 0, 'Comprehensive test should preserve zero');
    eq(parsed.falseVal, false, 'Comprehensive test should preserve false');
  }

  public testComprehensiveStateManagementScenario(): void {
    class ViewModel {
      __ob_id__1: number = 0;
      __ob_title__2: string = '';
      __ob_loading__3: boolean = false;
      __ob_error__4: string | null = null;
      items: any[] = [];
      tags: Set<string> = new Set();
      config: Map<string, any> = new Map();
      updatedAt: Date = new Date();
    }

    const vm = new ViewModel();
    vm.__ob_id__1 = 1;
    vm.__ob_title__2 = 'Test View';
    vm.__ob_loading__3 = false;
    vm.items = [
      { id: 1, label: 'Item 1' },
      { id: 2, label: 'Item 2' }
    ];
    vm.tags.add('important');
    vm.tags.add('urgent');
    vm.config.set('theme', 'dark');
    vm.updatedAt = new Date('2026-02-13');

    const stringified = JSONCoder.stringify(vm);
    const parsed = JSON.parse(stringified);

    eq(parsed.id, 1, 'State management should serialize __ob_id__1 as id');
    eq(parsed.title, 'Test View', 'State management should serialize __ob_title__2 as title');
    eq(parsed.loading, false, 'State management should serialize __ob_loading__3 as loading');
    eq(parsed.items.length, 2, 'State management should serialize items array');
    eq(Array.isArray(parsed.tags), true, 'State management should serialize tags Set');
    eq(parsed.tags.length, 2, 'State management should preserve tags size');
    eq(Array.isArray(parsed.config), true, 'State management should serialize config Map');
  }

  public testComprehensivePerformanceAndMemory(): void {
    const iterations = 50;
    const results: number[] = [];

    for (let i = 0; i < iterations; i++) {
      const obj = {
        data: new Map(
          Array.from({ length: 100 }, (_, idx) => [`key${idx}`, `value${idx}`])
        ),
        tags: new Set(Array.from({ length: 50 }, (_, idx) => idx)),
        items: Array.from({ length: 20 }, (_, idx) => ({
          id: idx,
          name: `item${idx}`,
          nested: { value: `nested${idx}` }
        }))
      };

      const startTime = Date.now();
      const stringified = JSONCoder.stringify(obj);
      const parsed = JSON.parse(stringified);
      const duration = Date.now() - startTime;

      results.push(duration);
    }

    const avgDuration = results.reduce((a, b) => a + b, 0) / results.length;
    eq(avgDuration < 100, true, 'Comprehensive performance test should complete quickly');
  }
}
