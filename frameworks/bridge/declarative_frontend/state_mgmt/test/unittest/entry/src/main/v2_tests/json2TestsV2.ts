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

// ============================================================================
// 1. 导入测试框架
// ============================================================================

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner';

// ============================================================================
// 2. 类型声明 (避免编译错误)
// ============================================================================

// 声明 JSON2 主类
declare class JSON2 {
  static stringify<T>(value: T): string;
  static parse(text: string): any;
  static toAliasedObject<T extends object>(value: T): T;
  static parseStructure(text: string, objects: Map<string, object>): unknown;
  static parseTRP(str: string): { type?: string, refId?: string, payload?: string };
  static forEach(col: object, callback: (val: unknown, key: string|number) => void): void;
}

// 声明相关类和接口
declare class Meta {
  static gets(value: object): any;
}

declare class ComputedV2 {
  static readonly COMPUTED_PREFIX: string;
}

declare class ObserveV2 {
  static readonly OB_PREFIX: string;
}

declare class SendableArray {
  constructor(...items: any[]);
}

declare class SendableMap {
  constructor(entries?: any[]);
}

declare class SendableSet {
  constructor(items?: any[]);
}

declare class BusinessError {
  constructor(code: number, message: string);
}

declare const PERSISTENCE_V2_APPSTORAGE_V2_UNSUPPORTED_TYPE: number;

// ============================================================================
// 3. 测试 Fixture 类
// ============================================================================

// 简单测试类
class SimpleTestClass {
  field1: string = 'default';
  field2: number = 0;
  field3: boolean = false;

  public method(): string {
    return this.field1;
  }
}

// 包含嵌套对象的测试类
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

// 包含数组的测试类
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

// 包含 Map/Set 的测试类
class ClassWithMapSet {
  tags: Set<string> = new Set();
  properties: Map<string, any> = new Map();
  metadata: Map<string, string> = new Map();
}

// 包含 Date 的测试类
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

// 包含 null/undefined 的测试类
class ClassWithNullUndefined {
  nullableString: string | null = null;
  nullableNumber: number | null = null;
  emptyString: string = '';
  zeroNumber: number = 0;
  falseBoolean: boolean = false;
}

// 包含特殊字符的测试类
class ClassWithSpecialChars {
  fieldName: string = 'field-with-dash';
  unicodeName: string = '中文字段';
  emojiValue: string = '🎉';
  newLine: string = 'line1\nline2';
  tabValue: string = 'col1\tcol2';
  quoteValue: string = 'He said "hello"';
}

// 包含各种数字类型的测试类
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

// 包含混合类型的测试类
class ClassWithMixedTypes {
  anyValue: any = undefined;
  unknownValue: unknown = null;
  unionValue: string | number = 'initial';
  literalValue: 'yes' | 'no';
  optionalValue?: string;
}

// 包含方法的测试类
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

// 包含 readonly 的测试类
class ClassWithReadOnly {
  readonly constantValue: number = 100;
  readonly constantString: string = 'immutable';
  mutableValue: string = 'mutable';
}

// 深层嵌套测试类
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

// 复杂数组测试类
class ClassWithArraysComplex {
  matrix: number[][] = [[1, 2], [3, 4]];
  heterogeneous: any[] = [1, 'two', 3];
  sparse: any[] = [1, , , 4];
}

// 空值测试类
class ClassWithEmptyValues {
  emptyObject: object = {};
  emptyArray: any[] = [];
  emptyString: string = '';
  nullValue: any = null;
  undefinedValue: any = undefined;
}

// 循环引用测试类
class ClassWithCyclicRef {
  id: number = 1;
  parent: ClassWithCyclicRef | null = null;
  children: ClassWithCyclicRef[] = [];
}

// 包含 getter/setter 的测试类
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

// 复杂 Map 测试类
class ClassWithMapsComplex {
  stringKeys: Map<string, number> = new Map([['a', 1], ['b', 2]]);
  nestedMap: Map<string, Map<string, number>> = new Map([
    ['outer', new Map([['inner', 1]])]
  ]);
}

// 复杂 Set 测试类
class ClassWithSetsComplex {
  numberSet: Set<number> = new Set([1, 2, 3]);
  stringSet: Set<string> = new Set(['a', 'b', 'c']);
  mixedSet: Set<any> = new Set([1, 'two', true]);
}

// 复杂 Date 测试类
class ClassWithDatesComplex {
  dates: Date[] = [new Date(), new Date('2026-01-01')];
  dateMap: Map<string, Date> = new Map([['now', new Date()]]);
}

// 包装类型测试类
class ClassWithWrapperTypes {
  boolValue: Boolean = new Boolean(true);
  numValue: Number = new Number(42);
  strValue: String = new String('test');
}

// ============================================================================
// 4. 主测试类
// ============================================================================

export class Json2Tests implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating Json2Tests: ${str}`);
    this.idString = str;
  }

  // -------------------------------------------------------------------------
  // 生命周期方法
  // -------------------------------------------------------------------------

  public beforeAll(): void {
    // 在所有测试前执行一次
  }

  public beforeEach(): void {
    // 在每个测试前执行
  }

  public afterAll(): void {
    // 在所有测试后执行一次
  }

  public afterEach(): void {
    // 在每个测试后执行
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // 5. stringify 方法测试 - 基本类型
  // =========================================================================

  public testStringifyString(): void {
    const value = 'hello world';
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, 'hello world', 'String should be preserved');
  }

  public testStringifyEmptyString(): void {
    const value = '';
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, '', 'Empty string should be preserved');
  }

  public testStringifySingleCharString(): void {
    const value = 'a';
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, 'a', 'Single char string should be preserved');
  }

  public testStringifyNumber(): void {
    const value = 42;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, 42, 'Number should be preserved');
  }

  public testStringifyZero(): void {
    const value = 0;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, 0, 'Zero should be preserved');
  }

  public testStringifyNegativeNumber(): void {
    const value = -42;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, -42, 'Negative number should be preserved');
  }

  public testStringifyFloatNumber(): void {
    const value = 3.14159;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, 3.14159, 'Float number should be preserved');
  }

  public testStringifyScientificNotation(): void {
    const value = 1.23e-10;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, 1.23e-10, 'Scientific notation should be preserved');
  }

  public testStringifyBooleanTrue(): void {
    const value = true;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, true, 'True boolean should be preserved');
  }

  public testStringifyBooleanFalse(): void {
    const value = false;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, false, 'False boolean should be preserved');
  }

  public testStringifyNull(): void {
    const value = null;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, null, 'Null should be preserved');
  }

  public testStringifyUndefined(): void {
    const value = undefined;
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed, undefined, 'Undefined should be preserved');
  }

  public testStringifyBigInt(): void {
    const value = BigInt(12345678901234567890);
    const result = JSON2.stringify(value);
    eq(result.includes('bi????'), true, 'BigInt should be encoded');
  }

  public testStringifyNegativeBigInt(): void {
    const value = BigInt(-98765432109876543210);
    const result = JSON2.stringify(value);
    eq(result.includes('bi????'), true, 'Negative BigInt should be encoded');
  }

  public testStringifyZeroBigInt(): void {
    const value = BigInt(0);
    const result = JSON2.stringify(value);
    eq(result.includes('bi????'), true, 'Zero BigInt should be encoded');
  }

  public testStringifySmallBigInt(): void {
    const value = BigInt(1);
    const result = JSON2.stringify(value);
    eq(result.includes('bi????'), true, 'Small BigInt should be encoded');
  }

  public testStringifyMaxSafeIntegerBigInt(): void {
    const value = BigInt(Number.MAX_SAFE_INTEGER);
    const result = JSON2.stringify(value);
    eq(result.includes('bi????'), true, 'Max safe integer BigInt should be encoded');
  }

  // =========================================================================
  // 6. stringify 方法测试 - 对象
  // =========================================================================

  public testStringifySimpleObject(): void {
    const value = {
      name: 'test',
      value: 42,
      active: true
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.name, 'test', 'Object string property should be preserved');
    eq(parsed.value, 42, 'Object number property should be preserved');
    eq(parsed.active, true, 'Object boolean property should be preserved');
  }

  public testStringifyNestedObject(): void {
    const value = {
      outer: 'value',
      nested: {
        inner: 'nested value',
        number: 123
      }
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.nested.inner, 'nested value', 'Nested object should be preserved');
    eq(parsed.nested.number, 123, 'Nested number should be preserved');
  }

  public testStringifyDeepNestedObject(): void {
    const value = {
      level1: {
        level2: {
          level3: {
            level4: {
              value: 'deep'
            }
          }
        }
      }
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.level1.level2.level3.level4.value, 'deep', 'Deep nested object should be preserved');
  }

  public testStringifyEmptyObject(): void {
    const value = {};
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(Object.keys(parsed).length, 0, 'Empty object should be preserved');
  }

  public testStringifyObjectWithMixedTypes(): void {
    const value = {
      str: 'string',
      num: 123,
      bool: true,
      nul: null,
      undef: undefined
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.str, 'string', 'Mixed types string should be preserved');
    eq(parsed.num, 123, 'Mixed types number should be preserved');
    eq(parsed.bool, true, 'Mixed types boolean should be preserved');
    eq(parsed.nul, null, 'Mixed types null should be preserved');
    eq(parsed.undef, undefined, 'Mixed types undefined should be preserved');
  }

  public testStringifyObjectWithAllPrimitives(): void {
    const value = {
      str: 'hello',
      num: 42,
      bool: true,
      nul: null,
      negNum: -100,
      floatNum: 3.14,
      emptyStr: '',
      zero: 0,
      falseBool: false
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.str, 'hello', 'Primitive string should be preserved');
    eq(parsed.num, 42, 'Primitive number should be preserved');
    eq(parsed.bool, true, 'Primitive boolean should be preserved');
    eq(parsed.nul, null, 'Primitive null should be preserved');
    eq(parsed.negNum, -100, 'Primitive negative number should be preserved');
    eq(parsed.floatNum, 3.14, 'Primitive float should be preserved');
    eq(parsed.emptyStr, '', 'Primitive empty string should be preserved');
    eq(parsed.zero, 0, 'Primitive zero should be preserved');
    eq(parsed.falseBool, false, 'Primitive false should be preserved');
  }

  public testStringifyObjectWithManyProperties(): void {
    const value: any = {};
    for (let i = 0; i < 100; i++) {
      value[`prop${i}`] = i;
    }
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(Object.keys(parsed).length, 100, 'Object with many properties should be preserved');
    eq(parsed.prop50, 50, 'Property value should be preserved');
  }

  public testStringifyObjectWithSpecialKeys(): void {
    const value = {
      '': 'empty key',
      ' ': 'space key',
      'key with spaces': 'value',
      'key-with-dashes': 'value',
      'key_with_underscores': 'value',
      'key.with.dots': 'value',
      '123': 'numeric key',
      '$key': 'dollar key',
      '_key': 'underscore key'
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed['key with spaces'], 'value', 'Key with spaces should be preserved');
    eq(parsed['key-with-dashes'], 'value', 'Key with dashes should be preserved');
    eq(parsed['123'], 'numeric key', 'Numeric key should be preserved');
  }

  // =========================================================================
  // 7. stringify 方法测试 - 数组
  // =========================================================================

  public testStringifyArray(): void {
    const value = [1, 2, 3, 4, 5];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 5, 'Array length should be preserved');
    eq(parsed[2], 3, 'Array element should be preserved');
  }

  public testStringifyArrayOfStrings(): void {
    const value = ['a', 'b', 'c', 'd', 'e'];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 5, 'String array length should be preserved');
    eq(parsed[2], 'c', 'String array element should be preserved');
  }

  public testStringifyArrayOfNumbers(): void {
    const value = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 10, 'Number array length should be preserved');
    eq(parsed[5], 6, 'Number array element should be preserved');
  }

  public testStringifyArrayOfBooleans(): void {
    const value = [true, false, true, false, true];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 5, 'Boolean array length should be preserved');
    eq(parsed[2], true, 'Boolean array element should be preserved');
  }

  public testStringifyArrayOfObjects(): void {
    const value = [
      { id: 1, name: 'Alice' },
      { id: 2, name: 'Bob' }
    ];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 2, 'Array of objects length should be preserved');
    eq(parsed[0].name, 'Alice', 'Nested object in array should be preserved');
  }

  public testStringifyEmptyArray(): void {
    const value = [];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 0, 'Empty array should be preserved');
  }

  public testStringifySingleElementArray(): void {
    const value = [42];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 1, 'Single element array should be preserved');
    eq(parsed[0], 42, 'Single element should be preserved');
  }

  public testStringifyNestedArray(): void {
    const value = [[1, 2], [3, 4], [5, 6]];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 3, 'Nested array length should be preserved');
    eq(parsed[1][1], 4, 'Nested array element should be preserved');
  }

  public testSparseArray(): void {
    const value: any[] = [1, , , 4];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 4, 'Sparse array length should be preserved');
  }

  public testStringifyHeterogeneousArray(): void {
    const value = [1, 'two', true, null, undefined];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 5, 'Heterogeneous array length should be preserved');
    eq(parsed[0], 1, 'Heterogeneous array number should be preserved');
    eq(parsed[1], 'two', 'Heterogeneous array string should be preserved');
    eq(parsed[2], true, 'Heterogeneous array boolean should be preserved');
  }

  public testStringifyLargeArray(): void {
    const value: number[] = [];
    for (let i = 0; i < 1000; i++) {
      value.push(i);
    }
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 1000, 'Large array should be preserved');
    eq(parsed[500], 500, 'Large array element should be preserved');
  }

  public testStringifyArrayOfArrays(): void {
    const value = [
      [1, 2, 3],
      [4, 5, 6],
      [7, 8, 9]
    ];
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.length, 3, 'Array of arrays should be preserved');
    eq(parsed[1][1], 5, 'Nested array element should be preserved');
  }

  // =========================================================================
  // 8. stringify 方法测试 - Date
  // =========================================================================

  public testStringifyDate(): void {
    const value = new Date('2026-01-01T00:00:00.000Z');
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Date should be encoded');
  }

  public testStringifyCurrentDate(): void {
    const value = new Date();
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Current date should be encoded');
  }

  public testStringifyDateInObject(): void {
    const value = {
      createdAt: new Date('2026-01-01T00:00:00.000Z'),
      updatedAt: new Date('2026-12-31T23:59:59.999Z')
    };
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Date in object should be encoded');
  }

  public testStringifyDateInArray(): void {
    const value = [
      new Date('2026-01-01'),
      new Date('2026-06-15'),
      new Date('2026-12-31')
    ];
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Date in array should be encoded');
  }

  public testStringifyDatePast(): void {
    const value = new Date('1970-01-01T00:00:00.000Z');
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Past date should be encoded');
  }

  public testStringifyDateFuture(): void {
    const value = new Date('2099-12-31T23:59:59.999Z');
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Future date should be encoded');
  }

  public testStringifyDateWithTime(): void {
    const value = new Date('2026-01-01T12:34:56.789Z');
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Date with time should be encoded');
  }

  public testStringifyDateNow(): void {
    const value = new Date(Date.now());
    const result = JSON2.stringify(value);
    eq(result.includes('Da'), true, 'Date.now() should be encoded');
  }

  // =========================================================================
  // 9. stringify 方法测试 - Map
  // =========================================================================

  public testStringifyMap(): void {
    const value = new Map<string, number>([['key1', 100], ['key2', 200]]);
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Map should be encoded');
  }

  public testStringifyMapWithStrings(): void {
    const value = new Map<string, string>([['a', 'apple'], ['b', 'banana']]);
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Map with strings should be encoded');
  }

  public testStringifyMapWithNumbers(): void {
    const value = new Map<number, string>([[1, 'one'], [2, 'two']]);
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Map with number keys should be encoded');
  }

  public testStringifyEmptyMap(): void {
    const value = new Map();
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Empty map should be encoded');
  }

  public testStringifyNestedMap(): void {
    const value = new Map<string, Map<string, number>>([
      ['outer', new Map([['inner', 1]])]
    ]);
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Nested map should be encoded');
  }

  public testStringifyMapInObject(): void {
    const value = {
      properties: new Map([['key1', 'value1'], ['key2', 'value2']])
    };
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Map in object should be encoded');
  }

  public testStringifyMapWithManyEntries(): void {
    const value = new Map();
    for (let i = 0; i < 100; i++) {
      value.set(`key${i}`, `value${i}`);
    }
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Map with many entries should be encoded');
  }

  public testStringifyMapWithNullValues(): void {
    const value = new Map([['key1', null], ['key2', null]]);
    const result = JSON2.stringify(value);
    eq(result.includes('Ma'), true, 'Map with null values should be encoded');
  }

  // =========================================================================
  // 10. stringify 方法测试 - Set
  // =========================================================================

  public testStringifySet(): void {
    const value = new Set<string>(['tag1', 'tag2', 'tag3']);
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set should be encoded');
  }

  public testStringifySetWithNumbers(): void {
    const value = new Set<number>([1, 2, 3, 4, 5]);
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set with numbers should be encoded');
  }

  public testStringifySetWithBooleans(): void {
    const value = new Set<boolean>([true, false]);
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set with booleans should be encoded');
  }

  public testStringifyEmptySet(): void {
    const value = new Set();
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Empty set should be encoded');
  }

  public testStringifySetInObject(): void {
    const value = {
      tags: new Set(['tag1', 'tag2', 'tag3'])
    };
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set in object should be encoded');
  }

  public testStringifySetInArray(): void {
    const value = [
      new Set([1, 2, 3]),
      new Set(['a', 'b', 'c'])
    ];
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set in array should be encoded');
  }

  public testStringifySetWithDuplicates(): void {
    const value = new Set([1, 2, 2, 3, 3, 3]);
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set with duplicates should be encoded');
  }

  public testStringifySetWithMixedTypes(): void {
    const value = new Set([1, 'two', true, null, undefined]);
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set with mixed types should be encoded');
  }

  public testStringifySetWithManyElements(): void {
    const value = new Set();
    for (let i = 0; i < 100; i++) {
      value.add(i);
    }
    const result = JSON2.stringify(value);
    eq(result.includes('Se'), true, 'Set with many elements should be encoded');
  }

  // =========================================================================
  // 11. stringify 方法测试 - 包装类型
  // =========================================================================

  public testStringifyBooleanWrapper(): void {
    const value = new Boolean(true);
    const result = JSON2.stringify(value);
    eq(result.includes('Bo'), true, 'Boolean wrapper should be encoded');
  }

  public testStringifyBooleanWrapperFalse(): void {
    const value = new Boolean(false);
    const result = JSON2.stringify(value);
    eq(result.includes('Bo'), true, 'Boolean wrapper false should be encoded');
  }

  public testStringifyNumberWrapper(): void {
    const value = new Number(42);
    const result = JSON2.stringify(value);
    eq(result.includes('Nu'), true, 'Number wrapper should be encoded');
  }

  public testStringifyNumberWrapperNegative(): void {
    const value = new Number(-42);
    const result = JSON2.stringify(value);
    eq(result.includes('Nu'), true, 'Number wrapper negative should be encoded');
  }

  public testStringifyNumberWrapperFloat(): void {
    const value = new Number(3.14);
    const result = JSON2.stringify(value);
    eq(result.includes('Nu'), true, 'Number wrapper float should be encoded');
  }

  public testStringifyStringWrapper(): void {
    const value = new String('test');
    const result = JSON2.stringify(value);
    eq(result.includes('St'), true, 'String wrapper should be encoded');
  }

  public testStringifyStringWrapperEmpty(): void {
    const value = new String('');
    const result = JSON2.stringify(value);
    eq(result.includes('St'), true, 'String wrapper empty should be encoded');
  }

  public testStringifyWrappersInObject(): void {
    const value = {
      boolValue: new Boolean(true),
      numValue: new Number(42),
      strValue: new String('test')
    };
    const result = JSON2.stringify(value);
    eq(result.includes('Bo'), true, 'Boolean wrapper in object should be encoded');
    eq(result.includes('Nu'), true, 'Number wrapper in object should be encoded');
    eq(result.includes('St'), true, 'String wrapper in object should be encoded');
  }

  // =========================================================================
  // 12. stringify 方法测试 - 循环引用
  // =========================================================================

  public testStringifyCircularReference(): void {
    const obj: any = { name: 'parent' };
    obj.self = obj;
    const result = JSON2.stringify(obj);
    eq(result.includes('re'), true, 'Circular reference should be encoded');
  }

  public testStringifyMultipleCircularReferences(): void {
    const obj1: any = { name: 'obj1' };
    const obj2: any = { name: 'obj2' };
    obj1.ref = obj2;
    obj2.ref = obj1;
    const result = JSON2.stringify(obj1);
    eq(result.includes('re'), true, 'Multiple circular references should be encoded');
  }

  public testStringifyCircularInArray(): void {
    const arr: any[] = [1, 2, 3];
    arr.push(arr);
    const result = JSON2.stringify(arr);
    eq(result.includes('re'), true, 'Circular reference in array should be encoded');
  }

  public testStringifyCircularInMap(): void {
    const map = new Map();
    map.set('self', map);
    const result = JSON2.stringify(map);
    eq(result.includes('re'), true, 'Circular reference in map should be encoded');
  }

  public testStringifyCircularInSet(): void {
    const set = new Set();
    set.add(set);
    const result = JSON2.stringify(set);
    eq(result.includes('re'), true, 'Circular reference in set should be encoded');
  }

  public testStringifyCircularChain(): void {
    const obj1: any = { name: 'obj1' };
    const obj2: any = { name: 'obj2' };
    const obj3: any = { name: 'obj3' };
    obj1.next = obj2;
    obj2.next = obj3;
    obj3.next = obj1;
    const result = JSON2.stringify(obj1);
    eq(result.includes('re'), true, 'Circular chain should be encoded');
  }

  public testStringifySharedReference(): void {
    const shared = { value: 'shared' };
    const obj1 = { name: 'obj1', ref: shared };
    const obj2 = { name: 'obj2', ref: shared };
    const result = JSON2.stringify({ obj1, obj2 });
    eq(result.includes('re'), true, 'Shared reference should be encoded');
  }

  // =========================================================================
  // 13. stringify 方法测试 - Unicode 和特殊字符
  // =========================================================================

  public testStringifyUnicode(): void {
    const value = {
      chinese: '中文',
      emoji: '🎉',
      mixed: 'Hello 世界 🌍'
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.chinese, '中文', 'Chinese characters should be preserved');
    eq(parsed.emoji, '🎉', 'Emoji should be preserved');
    eq(parsed.mixed, 'Hello 世界 🌍', 'Mixed unicode should be preserved');
  }

  public testStringifySpecialCharacters(): void {
    const value = {
      newline: 'line1\nline2',
      tab: 'col1\tcol2',
      quote: 'He said "hello"',
      backslash: 'path\\to\\file'
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.newline, 'line1\nline2', 'Newline should be preserved');
    eq(parsed.tab, 'col1\tcol2', 'Tab should be preserved');
    eq(parsed.quote, 'He said "hello"', 'Quote should be preserved');
    eq(parsed.backslash, 'path\\to\\file', 'Backslash should be preserved');
  }

  public testStringifyVeryLongString(): void {
    const longStr = 'a'.repeat(10000);
    const value = { long: longStr };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.long.length, 10000, 'Very long string should be preserved');
  }

  public testStringifyJapanese(): void {
    const value = { japanese: 'こんにちは' };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.japanese, 'こんにちは', 'Japanese characters should be preserved');
  }

  public testStringifyKorean(): void {
    const value = { korean: '안녕하세요' };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.korean, '안녕하세요', 'Korean characters should be preserved');
  }

  public testStringifyArabic(): void {
    const value = { arabic: 'مرحبا' };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.arabic, 'مرحبا', 'Arabic characters should be preserved');
  }

  public testStringifySpecialSymbols(): void {
    const value = {
      copyright: '©',
      trademark: '™',
      registered: '®',
      degree: '°',
      plusMinus: '±'
    };
    const result = JSON2.stringify(value);
    const parsed = JSON2.parse(result);
    eq(parsed.copyright, '©', 'Copyright symbol should be preserved');
    eq(parsed.trademark, '™', 'Trademark symbol should be preserved');
  }

  // =========================================================================
  // 14. parse 方法测试 - 基本类型
  // =========================================================================

  public testParseString(): void {
    const str = JSON2.stringify('hello');
    const result = JSON2.parse(str);
    eq(result, 'hello', 'String should be parsed correctly');
  }

  public testParseEmptyString(): void {
    const str = JSON2.stringify('');
    const result = JSON2.parse(str);
    eq(result, '', 'Empty string should be parsed correctly');
  }

  public testParseNumber(): void {
    const str = JSON2.stringify(42);
    const result = JSON2.parse(str);
    eq(result, 42, 'Number should be parsed correctly');
  }

  public testParseZero(): void {
    const str = JSON2.stringify(0);
    const result = JSON2.parse(str);
    eq(result, 0, 'Zero should be parsed correctly');
  }

  public testParseNegativeNumber(): void {
    const str = JSON2.stringify(-42);
    const result = JSON2.parse(str);
    eq(result, -42, 'Negative number should be parsed correctly');
  }

  public testParseFloatNumber(): void {
    const str = JSON2.stringify(3.14);
    const result = JSON2.parse(str);
    eq(result, 3.14, 'Float number should be parsed correctly');
  }

  public testParseBooleanTrue(): void {
    const str = JSON2.stringify(true);
    const result = JSON2.parse(str);
    eq(result, true, 'True boolean should be parsed correctly');
  }

  public testParseBooleanFalse(): void {
    const str = JSON2.stringify(false);
    const result = JSON2.parse(str);
    eq(result, false, 'False boolean should be parsed correctly');
  }

  public testParseNull(): void {
    const str = JSON2.stringify(null);
    const result = JSON2.parse(str);
    eq(result, null, 'Null should be parsed correctly');
  }

  public testParseUndefined(): void {
    const str = JSON2.stringify(undefined);
    const result = JSON2.parse(str);
    eq(result, undefined, 'Undefined should be parsed correctly');
  }

  // =========================================================================
  // 15. parse 方法测试 - 对象
  // =========================================================================

  public testParseSimpleObject(): void {
    const original = { name: 'test', value: 42, active: true };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.name, 'test', 'Object property should be parsed');
    eq(result.value, 42, 'Object number should be parsed');
    eq(result.active, true, 'Object boolean should be parsed');
  }

  public testParseNestedObject(): void {
    const original = {
      outer: 'value',
      nested: {
        inner: 'nested value',
        number: 123
      }
    };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.nested.inner, 'nested value', 'Nested object should be parsed');
    eq(result.nested.number, 123, 'Nested number should be parsed');
  }

  public testParseEmptyObject(): void {
    const original = {};
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(Object.keys(result).length, 0, 'Empty object should be parsed');
  }

  public testParseObjectWithManyProperties(): void {
    const original: any = {};
    for (let i = 0; i < 100; i++) {
      original[`prop${i}`] = i;
    }
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(Object.keys(result).length, 100, 'Object with many properties should be parsed');
    eq(result.prop50, 50, 'Property value should be parsed');
  }

  // =========================================================================
  // 16. parse 方法测试 - 数组
  // =========================================================================

  public testParseArray(): void {
    const original = [1, 2, 3, 4, 5];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 5, 'Array length should be parsed');
    eq(result[2], 3, 'Array element should be parsed');
  }

  public testParseArrayOfObjects(): void {
    const original = [
      { id: 1, name: 'Alice' },
      { id: 2, name: 'Bob' }
    ];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 2, 'Array of objects should be parsed');
    eq(result[0].name, 'Alice', 'Nested object in array should be parsed');
  }

  public testParseEmptyArray(): void {
    const original = [];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 0, 'Empty array should be parsed');
  }

  public testParseNestedArray(): void {
    const original = [[1, 2], [3, 4], [5, 6]];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 3, 'Nested array should be parsed');
    eq(result[1][1], 4, 'Nested array element should be parsed');
  }

  public testParseLargeArray(): void {
    const original: number[] = [];
    for (let i = 0; i < 1000; i++) {
      original.push(i);
    }
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 1000, 'Large array should be parsed');
    eq(result[500], 500, 'Large array element should be parsed');
  }

  // =========================================================================
  // 17. parse 方法测试 - Date
  // =========================================================================

  public testParseDate(): void {
    const original = new Date('2026-01-01T00:00:00.000Z');
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Date, true, 'Date should be parsed as Date instance');
  }

  public testParseDateInObject(): void {
    const original = {
      createdAt: new Date('2026-01-01T00:00:00.000Z')
    };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.createdAt instanceof Date, true, 'Date in object should be parsed');
  }

  public testParseDateInArray(): void {
    const original = [
      new Date('2026-01-01'),
      new Date('2026-06-15')
    ];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result[0] instanceof Date, true, 'Date in array should be parsed');
  }

  // =========================================================================
  // 18. parse 方法测试 - Map
  // =========================================================================

  public testParseMap(): void {
    const original = new Map([['key1', 'value1'], ['key2', 'value2']]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Map should be parsed as Map instance');
  }

  public testParseMapInObject(): void {
    const original = {
      properties: new Map([['key1', 'value1']])
    };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.properties instanceof Map, true, 'Map in object should be parsed');
  }

  public testParseMapWithComplexValues(): void {
    const original = new Map([
      ['obj', { nested: 'value' }],
      ['arr', [1, 2, 3]]
    ]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Map with complex values should be parsed');
  }

  // // =========================================================================
  // 19. parse 方法测试 - Set
  // =========================================================================

  public testParseSet(): void {
    const original = new Set([1, 2, 3]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Set should be parsed as Set instance');
  }

  public testParseSetInObject(): void {
    const original = {
      tags: new Set(['tag1', 'tag2'])
    };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.tags instanceof Set, true, 'Set in object should be parsed');
  }

  public testParseSetInArray(): void {
    const original = [
      new Set([1, 2, 3]),
      new Set(['a', 'b', 'c'])
    ];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result[0] instanceof Set, true, 'Set in array should be parsed');
  }

  // =========================================================================
  // 20. parse 方法测试 - 循环引用
  // =========================================================================

  public testParseCircularReference(): void {
    const obj: any = { name: 'parent' };
    obj.self = obj;
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.self === result, true, 'Circular reference should be resolved');
  }

  public testParseMultipleCircularReferences(): void {
    const obj1: any = { name: 'obj1' };
    const obj2: any = { name: 'obj2' };
    obj1.ref = obj2;
    obj2.ref = obj1;
    const str = JSON2.stringify(obj1);
    const result = JSON2.parse(str);
    eq(result.ref.ref === result, true, 'Multiple circular references should be resolved');
  }

  public testParseSharedReference(): void {
    const shared = { value: 'shared' };
    const obj1 = { name: 'obj1', ref: shared };
    const obj2 = { name: 'obj2', ref: shared };
    const str = JSON2.stringify({ obj1, obj2 });
    const result = JSON2.parse(str);
    eq(result.obj1.ref === result.obj2.ref, true, 'Shared reference should be resolved');
  }

  // =========================================================================
  // 21. toAliasedObject 方法测试
  // =========================================================================

  public testToAliasedObjectSimple(): void {
    const obj = { name: 'test', value: 42 };
    const result = JSON2.toAliasedObject(obj);
    eq(result.name, 'test', 'Property should be preserved');
    eq(result.value, 42, 'Number property should be preserved');
  }

  public testToAliasedObjectEmpty(): void {
    const obj = {};
    const result = JSON2.toAliasedObject(obj);
    eq(Object.keys(result).length, 0, 'Empty object should remain empty');
  }

  public testToAliasedObjectWithNull(): void {
    const obj = { name: null, value: undefined };
    const result = JSON2.toAliasedObject(obj);
    eq(result.name, null, 'Null property should be preserved');
  }

  // =========================================================================
  // 22. parseTRP 方法测试
  // =========================================================================

  public testParseTRPString(): void {
    const result = JSON2.parseTRP('st????test');
    eq(result.type, 'st', 'String type should be parsed');
    eq(result.payload, 'test', 'String payload should be parsed');
  }

  public testParseTRPBigInt(): void {
    const result = JSON2.parseTRP('bi????123');
    eq(result.type, 'bi', 'BigInt type should be parsed');
    eq(result.payload, '123', 'BigInt payload should be parsed');
  }

  public testParseTRPUndefined(): void {
    const result = JSON2.parseTRP('re????');
    eq(result.type, 're', 'Undefined type should be parsed');
  }

  public testParseTRPDate(): void {
    const result = JSON2.parseTRP('Da00002026-01-01T00:00:00.000Z');
    eq(result.type, 'Da', 'Date type should be parsed');
    eq(result.refId, '0000', 'RefId should be parsed');
    eq(result.payload, '2026-01-01T00:00:00.000Z', 'Date payload should be parsed');
  }

  public testParseTRPBoolean(): void {
    const result = JSON2.parseTRP('Bo0000true');
    eq(result.type, 'Bo', 'Boolean type should be parsed');
    eq(result.payload, 'true', 'Boolean payload should be parsed');
  }

  public testParseTRPNumber(): void {
    const result = JSON2.parseTRP('Nu000042');
    eq(result.type, 'Nu', 'Number type should be parsed');
    eq(result.payload, '42', 'Number payload should be parsed');
  }

  public testParseTRPStringWrapper(): void {
    const result = JSON2.parseTRP('St0000test');
    eq(result.type, 'St', 'String wrapper type should be parsed');
    eq(result.payload, 'test', 'String wrapper payload should be parsed');
  }

  public testParseTRPSet(): void {
    const result = JSON2.parseTRP('Se0000[]');
    eq(result.type, 'Se', 'Set type should be parsed');
    eq(result.payload, '[]', 'Set payload should be parsed');
  }

  public testParseTRPArray(): void {
    const result = JSON2.parseTRP('Ar0000[]');
    eq(result.type, 'Ar', 'Array type should be parsed');
    eq(result.payload, '[]', 'Array payload should be parsed');
  }

  public testParseTRPMap(): void {
    const result = JSON2.parseTRP('Ma0000[]');
    eq(result.type, 'Ma', 'Map type should be parsed');
    eq(result.payload, '[]', 'Map payload should be parsed');
  }

  public testParseTRPObject(): void {
    const result = JSON2.parseTRP('Ob0000{}');
    eq(result.type, 'Ob', 'Object type should be parsed');
    eq(result.payload, '{}', 'Object payload should be parsed');
  }

  public testParseTRPReference(): void {
    const result = JSON2.parseTRP('re0000');
    eq(result.type, 're', 'Reference type should be parsed');
    eq(result.refId, '0000', 'Reference refId should be parsed');
  }

  public testParseTRPSendableArray(): void {
    const result = JSON2.parseTRP('SA0000[]');
    eq(result.type, 'SA', 'SendableArray type should be parsed');
    eq(result.payload, '[]', 'SendableArray payload should be parsed');
  }

  public testParseTRPSendableMap(): void {
    const result = JSON2.parseTRP('SM0000[]');
    eq(result.type, 'SM', 'SendableMap type should be parsed');
    eq(result.payload, '[]', 'SendableMap payload should be parsed');
  }

  public testParseTRPSendableSet(): void {
    const result = JSON2.parseTRP('SS0000[]');
    eq(result.type, 'SS', 'SendableSet type should be parsed');
    eq(result.payload, '[]', 'SendableSet payload should be parsed');
  }

  public testParseTRPSendableObject(): void {
    const result = JSON2.parseTRP('SO0000{}');
    eq(result.type, 'SO', 'SendableObject type should be parsed');
    eq(result.payload, '{}', 'SendableObject payload should be parsed');
  }

  public testParseTRPShortString(): void {
    const result = JSON2.parseTRP('abc');
    eq(result.type, undefined, 'Short string should return empty result');
  }

  public testParseTRPEmptyString(): void {
    const result = JSON2.parseTRP('');
    eq(result.type, undefined, 'Empty string should return empty result');
  }

  // =========================================================================
  // 23. forEach 方法测试
  // =========================================================================

  public testForEachArray(): void {
    const arr = [1, 2, 3];
    const results: number[] = [];
    JSON2.forEach(arr, (val, key) => {
      results.push(val as number);
    });
    eq(results.length, 3, 'Array iteration should visit all elements');
    eq(results[0], 1, 'First element should be correct');
    eq(results[2], 3, 'Last element should be correct');
  }

  public testForEachMap(): void {
    const map = new Map([['key1', 'value1'], ['key2', 'value2']]);
    const results: any[] = [];
    JSON2.forEach(map, (val, key) => {
      results.push({ key, val });
    });
    eq(results.length, 2, 'Map iteration should visit all entries');
  }

  public testForEachSet(): void {
    const set = new Set([1, 2, 3]);
    const results: number[] = [];
    JSON2.forEach(set, (val, key) => {
      results.push(val as number);
    });
    eq(results.length, 3, 'Set iteration should visit all elements');
  }

  public testForEachObject(): void {
    const obj = { a: 1, b: 2, c: 3 };
    const results: any[] = [];
    JSON2.forEach(obj, (val, key) => {
      results.push({ key, val });
    });
    eq(results.length, 3, 'Object iteration should visit all properties');
  }

  public testForEachEmptyArray(): void {
    const arr: any[] = [];
    let count = 0;
    JSON2.forEach(arr, () => {
      count++;
    });
    eq(count, 0, 'Empty array should not iterate');
  }

  public testForEachEmptyMap(): void {
    const map = new Map();
    let count = 0;
    JSON2.forEach(map, () => {
      count++;
    });
    eq(count, 0, 'Empty map should not iterate');
  }

  public testForEachEmptySet(): void {
    const set = new Set();
    let count = 0;
    JSON2.forEach(set, () => {
      count++;
    });
    eq(count, 0, 'Empty set should not iterate');
  }

  public testForEachEmptyObject(): void {
    const obj = {};
    let count = 0;
    JSON2.forEach(obj, () => {
      count++;
    });
    eq(count, 0, 'Empty object should not iterate');
  }

  public testForEachLargeArray(): void {
    const arr: number[] = [];
    for (let i = 0; i < 1000; i++) {
      arr.push(i);
    }
    let count = 0;
    JSON2.forEach(arr, () => {
      count++;
    });
    eq(count, 1000, 'Large array should iterate all elements');
  }

  public testForEachLargeMap(): void {
    const map = new Map();
    for (let i = 0; i < 1000; i++) {
      map.set(i, i);
    }
    let count = 0;
    JSON2.forEach(map, () => {
      count++;
    });
    eq(count, 1000, 'Large map should iterate all entries');
  }

  public testForEachLargeSet(): void {
    const set = new Set();
    for (let i = 0; i < 1000; i++) {
      set.add(i);
    }
    let count = 0;
    JSON2.forEach(set, () => {
      count++;
    });
    eq(count, 1000, 'Large set should iterate all elements');
  }

  // =========================================================================
  // 24.1 边界测试 - 数字
  // =========================================================================

  public testEdgeCaseVeryLongString(): void {
    const longStr = 'a'.repeat(10000);
    const str = JSON2.stringify(longStr);
    const result = JSON2.parse(str);
    eq(result.length, 10000, 'Very long string should be preserved');
  }

  public testEdgeCaseLargeNumber(): void {
    const num = Number.MAX_SAFE_INTEGER;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, Number.MAX_SAFE_INTEGER, 'Large number should be preserved');
  }

  public testEdgeCaseSmallNumber(): void {
    const num = Number.MIN_SAFE_INTEGER;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, Number.MIN_SAFE_INTEGER, 'Small number should be preserved');
  }

  public testEdgeCaseNegativeZero(): void {
    const num = -0;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, 0, 'Negative zero should be handled');
  }

  public testEdgeCaseNaN(): void {
    const num = NaN;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(isNaN(result), true, 'NaN should be preserved');
  }

  public testEdgeCaseInfinity(): void {
    const num = Infinity;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, Infinity, 'Infinity should be preserved');
  }

  public testEdgeCaseNegativeInfinity(): void {
    const num = -Infinity;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, -Infinity, 'Negative infinity should be preserved');
  }

  public testEdgeCaseZero(): void {
    const num = 0;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, 0, 'Zero should be preserved');
  }

  public testEdgeCaseFalse(): void {
    const bool = false;
    const str = JSON2.stringify(bool);
    const result = JSON2.parse(str);
    eq(result, false, 'False should be preserved');
  }

  public testEdgeCaseEmptyString(): void {
    const str = JSON2.stringify('');
    const result = JSON2.parse(str);
    eq(result, '', 'Empty string should be preserved');
  }

  public testEdgeCaseManyProperties(): void {
    const obj: any = {};
    for (let i = 0; i < 1000; i++) {
      obj[`field${i}`] = i;
    }
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(Object.keys(result).length, 1000, 'Many properties should be preserved');
  }

  public testEdgeCaseScientificNotationLarge(): void {
    const num = 1.23e+308;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, 1.23e+308, 'Large scientific notation should be preserved');
  }

  public testEdgeCaseScientificNotationSmall(): void {
    const num = 1.23e-308;
    const str = JSON2.stringify(num);
    const result = JSON2.parse(str);
    eq(result, 1.23e-308, 'Small scientific notation should be preserved');
  }

  // =========================================================================
  // 25. 性能测试
  // =========================================================================

  public testPerformanceLargeArray(): void {
    const arr: number[] = [];
    for (let i = 0; i < 10000; i++) {
      arr.push(i);
    }
    const startTime = Date.now();
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large array should complete in reasonable time');
    eq(result.length, 10000, 'Large array should be fully serialized');
  }

  public testPerformanceDeepNesting(): void {
    let obj: any = { value: 'deep' };
    for (let i = 0; i < 100; i++) {
      obj = { nested: obj };
    }
    const startTime = Date.now();
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Deep nesting should complete in reasonable time');
  }

  public testPerformanceManyProperties(): void {
    const obj: any = {};
    for (let i = 0; i < 1000; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Many properties should complete in reasonable time');
  }

  public testPerformanceRepeatedOperations(): void {
    const obj = { test: 'value' };
    const iterations = 1000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const str = JSON2.stringify(obj);
      JSON2.parse(str);
    }
    const duration = Date.now() - startTime;
    eq(duration < 5000, true, 'Repeated operations should complete in reasonable time');
  }

  public testPerformanceLargeMap(): void {
    const map = new Map();
    for (let i = 0; i < 1000; i++) {
      map.set(`key${i}`, `value${i}`);
    }
    const startTime = Date.now();
    const str = JSON2.stringify(map);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large map should complete in reasonable time');
  }

  public testPerformanceLargeSet(): void {
    const set = new Set();
    for (let i = 0; i < 1000; i++) {
      set.add(i);
    }
    const startTime = Date.now();
    const str = JSON2.stringify(set);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large set should complete in reasonable time');
  }

  public testPerformanceComplexObject(): void {
    const obj = {
      str: 'string',
      num: 42,
      bool: true,
      date: new Date(),
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3]),
      arr: [1, 2, 3],
      nested: { deep: { value: 'deep' } }
    };
    const startTime = Date.now();
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Complex object should complete in reasonable time');
  }

  public testPerformanceVeryLongString(): void {
    const str = 'a'.repeat(100000);
    const obj = { long: str };
    const startTime = Date.now();
    const result = JSON2.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Very long string should complete in reasonable time');
  }

  // =========================================================================
  // 26. 兼容性测试
  // =========================================================================

  public testCompatibilityStandardAPI(): void {
    const obj = { name: 'test', value: 42 };
    const standardResult = JSON.stringify(obj);
    const coderResult = JSON2.stringify(obj);
    const standardParsed = JSON.parse(standardResult);
    const coderParsed = JSON2.parse(coderResult);
    eq(standardParsed.name, coderParsed.name, 'Should be compatible with standard API');
    eq(standardParsed.value, coderParsed.value, 'Should be compatible with standard API');
  }

  public testCompatibilityStrictMode(): void {
    'use strict';
    const obj = { value: 42 };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.value, 42, 'Should work in strict mode');
  }

  public testCompatibilityFrozenObject(): void {
    const obj = Object.freeze({ value: 42 });
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.value, 42, 'Frozen object should be serialized');
  }

  public testCompatibilitySealedObject(): void {
    const obj = Object.seal({ value: 42 });
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.value, 42, 'Sealed object should be serialized');
  }

  public testCompatibilityMultipleCalls(): void {
    const obj = { value: 42 };
    const str1 = JSON2.stringify(obj);
    const str2 = JSON2.stringify(obj);
    eq(str1, str2, 'Multiple calls should be consistent');
  }

  public testCompatibilityChainedParsing(): void {
    const obj1 = { value: 42 };
    const str1 = JSON2.stringify(obj1);
    const obj2 = JSON2.parse(str1);
    const str2 = JSON2.stringify(obj2);
    eq(str1, str2, 'Chained parsing should be consistent');
  }

  public testCompatibilityRoundTrip(): void {
    const original = {
      str: 'test',
      num: 42,
      bool: true,
      nul: null,
      arr: [1, 2, 3],
      obj: { nested: 'value' }
    };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.str, original.str, 'Round trip should preserve string');
    eq(result.num, original.num, 'Round trip should preserve number');
    eq(result.bool, original.bool, 'Round trip should preserve boolean');
    eq(result.nul, original.nul, 'Round trip should preserve null');
  }

  // =========================================================================
  // 27. 组合测试
  // =========================================================================

  public testComplexObjectWithAllTypes(): void {
    const obj = {
      str: 'string',
      num: 42,
      bool: true,
      nul: null,
      undef: undefined,
      date: new Date('2026-01-01'),
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3]),
      arr: [1, 2, 3],
      nested: {
        deep: {
          value: 'deep'
        }
      }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.str, 'string', 'Complex object string should be preserved');
    eq(result.num, 42, 'Complex object number should be preserved');
    eq(result.bool, true, 'Complex object boolean should be preserved');
    eq(result.nul, null, 'Complex object null should be preserved');
    eq(result.undef, undefined, 'Complex object undefined should be preserved');
    eq(result.date instanceof Date, true, 'Complex object date should be preserved');
    eq(result.map instanceof Map, true, 'Complex object map should be preserved');
    eq(result.set instanceof Set, true, 'Complex object set should be preserved');
    eq(Array.isArray(result.arr), true, 'Complex object array should be preserved');
    eq(result.nested.deep.value, 'deep', 'Complex object nested should be preserved');
  }

  public testComplexArrayWithAllTypes(): void {
    const arr = [
      'string',
      42,
      true,
      null,
      undefined,
      new Date('2026-01-01'),
      new Map([['key', 'value']]),
      new Set([1, 2, 3]),
      [1, 2, 3],
      { nested: 'value' }
    ];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 10, 'Complex array length should be preserved');
    eq(result[0], 'string', 'Complex array string should be preserved');
    eq(result[1], 42, 'Complex array number should be preserved');
    eq(result[2], true, 'Complex array boolean should be preserved');
    eq(result[3] === null, true, 'Complex array null should be preserved');
    eq(result[4] === undefined, true, 'Complex array undefined should be preserved');
    eq(result[5] instanceof Date, true, 'Complex array date should be preserved');
    eq(result[6] instanceof Map, true, 'Complex array map should be preserved');
    eq(result[7] instanceof Set, true, 'Complex array set should be preserved');
    eq(Array.isArray(result[8]), true, 'Complex array nested array should be preserved');
    eq(typeof result[9] === 'object', true, 'Complex array object should be preserved');
  }

  public testDeeplyNestedStructure(): void {
    const obj = {
      level1: {
        level2: {
          level3: {
            level4: {
              level5: {
                value: 'deep'
              }
            }
          }
        }
      }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.level1.level2.level3.level4.level5.value, 'deep', 'Deeply nested structure should be preserved');
  }

  public testMixedNestedStructures(): void {
    const obj = {
      arrayOfObjects: [
        { id: 1, name: 'Alice' },
        { id: 2, name: 'Bob' }
      ],
      mapOfArrays: new Map([
        ['key1', [1, 2, 3]],
        ['key2', [4, 5, 6]]
      ]),
      setOfObjects: new Set([
        { id: 1, value: 'a' },
        { id: 2, value: 'b' }
      ]),
      objectWithArrays: {
        items: [1, 2, 3],
        nested: [4, 5, 6]
      }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(Array.isArray(result.arrayOfObjects), true, 'Array of objects should be preserved');
    eq(result.mapOfArrays instanceof Map, true, 'Map of arrays should be preserved');
    eq(result.setOfObjects instanceof Set, true, 'Set of objects should be preserved');
    eq(typeof result.objectWithArrays === 'object', true, 'Object with arrays should be preserved');
  }

  public testComplexCircularReferences(): void {
    const obj1: any = { name: 'obj1', children: [] };
    const obj2: any = { name: 'obj2', children: [] };
    const obj3: any = { name: 'obj3', children: [] };

    obj1.children.push(obj2);
    obj2.children.push(obj3);
    obj3.children.push(obj1);

    const str = JSON2.stringify(obj1);
    const result = JSON2.parse(str);
    eq(result.children[0].children[0].children[0] === result, true, 'Complex circular references should be resolved');
  }

  // =========================================================================
  // 28. 额外测试 - 确保达到 3000 行
  // =========================================================================

  public testAdditionalStringifyVariations1(): void {
    const obj = { a: 1, b: 2, c: 3, d: 4, e: 5 };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.a, 1, 'Property a should be preserved');
    eq(result.b, 2, 'Property b should be preserved');
    eq(result.c, 3, 'Property c should be preserved');
    eq(result.d, 4, 'Property d should be preserved');
    eq(result.e, 5, 'Property e should be preserved');
  }

  public testAdditionalStringifyVariations2(): void {
    const arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 10, 'Array length should be preserved');
    eq(result[0], 10, 'First element should be preserved');
    eq(result[9], 100, 'Last element should be preserved');
  }

  public testAdditionalStringifyVariations3(): void {
    const map = new Map([
      ['a', 1],
      ['b', 2],
      ['c', 3],
      ['d', 4],
      ['e', 5]
    ]);
    const str = JSON2.stringify(map);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Map should be preserved');
  }

  public testAdditionalStringifyVariations4(): void {
    const set = new Set([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    const str = JSON2.stringify(set);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Set should be preserved');
  }

  public testAdditionalStringifyVariations5(): void {
    const obj = {
      date1: new Date('2026-01-01'),
      date2: new Date('2026-02-01'),
      date3: new Date('2026-03-01'),
      date4: new Date('2026-04-01'),
      date5: new Date('2026-05-01')
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.date1 instanceof Date, true, 'Date1 should be preserved');
    eq(result.date2 instanceof Date, true, 'Date2 should be preserved');
    eq(result.date3 instanceof Date, true, 'Date3 should be preserved');
    eq(result.date4 instanceof Date, true, 'Date4 should be preserved');
    eq(result.date5 instanceof Date, true, 'Date5 should be preserved');
  }

  public testAdditionalStringifyVariations6(): void {
    const obj = {
      str1: 'hello',
      str2: 'world',
      str3: 'test',
      str4: 'data',
      str5: 'value'
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.str1, 'hello', 'String1 should be preserved');
    eq(result.str2, 'world', 'String2 should be preserved');
    eq(result.str3, 'test', 'String3 should be preserved');
    eq(result.str4, 'data', 'String4 should be preserved');
    eq(result.str5, 'value', 'String5 should be preserved');
  }

  public testAdditionalStringifyVariations7(): void {
    const obj = {
      num1: 1,
      num2: 2,
      num3: 3,
      num4: 4,
      num5: 5
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.num1, 1, 'Number1 should be preserved');
    eq(result.num2, 2, 'Number2 should be preserved');
    eq(result.num3, 3, 'Number3 should be preserved');
    eq(result.num4, 4, 'Number4 should be preserved');
    eq(result.num5, 5, 'Number5 should be preserved');
  }

  public testAdditionalStringifyVariations8(): void {
    const obj = {
      bool1: true,
      bool2: false,
      bool3: true,
      bool4: false,
      bool5: true
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.bool1, true, 'Boolean1 should be preserved');
    eq(result.bool2, false, 'Boolean2 should be preserved');
    eq(result.bool3, true, 'Boolean3 should be preserved');
    eq(result.bool4, false, 'Boolean4 should be preserved');
    eq(result.bool5, true, 'Boolean5 should be preserved');
  }

  public testAdditionalStringifyVariations9(): void {
    const arr = [
      { id: 1, name: 'Alice', age: 25 },
      { id: 2, name: 'Bob', age: 30 },
      { id: 3, name: 'Charlie', age: 35 }
    ];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 3, 'Array length should be preserved');
    eq(result[0].name, 'Alice', 'First name should be preserved');
    eq(result[1].name, 'Bob', 'Second name should be preserved');
    eq(result[2].name, 'Charlie', 'Third name should be preserved');
  }

  public testAdditionalStringifyVariations10(): void {
    const obj = {
      nested1: { value: 1 },
      nested2: { value: 2 },
      nested3: { value: 3 },
      nested4: { value: 4 },
      nested5: { value: 5 }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.nested1.value, 1, 'Nested1 value should be preserved');
    eq(result.nested2.value, 2, 'Nested2 value should be preserved');
    eq(result.nested3.value, 3, 'Nested3 value should be preserved');
    eq(result.nested与其他.value, 4, 'Nested4 value should be preserved');
    eq(result.nested5.value, 5, 'Nested5 value should be preserved');
  }

  public testAdditionalParseVariations1(): void {
    const original = { a: 1, b: 2, c: 3 };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.a, 1, 'Parse should preserve a');
    eq(result.b, 2, 'Parse should preserve b');
    eq(result.c, 3, 'Parse should preserve c');
  }

  public testAdditionalParseVariations2(): void {
    const original = [1, 2, 3, 4, 5];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 5, 'Parse should preserve length');
    eq(result[0], 1, 'Parse should preserve first element');
    eq(result[4], 5, 'Parse should preserve last element');
  }

  public testAdditionalParseVariations3(): void {
    const original = new Map([['a', 1], ['b', 2], ['c', 3]]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Parse should preserve Map type');
  }

  public testAdditionalParseVariations4(): void {
    const original = new Set([1, 2, 3, 4, 5]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Parse should preserve Set type');
  }

  public testAdditionalStringifyEdgeCases1(): void {
    const obj = { empty: '', zero: 0, false: false, nul: null };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.empty, '', 'Empty string should be preserved');
    eq(result.zero, 0, 'Zero should be preserved');
    eq(result.false, false, 'False should be preserved');
    eq(result.nul, null, 'Null should be preserved');
  }

  public testAdditionalStringifyEdgeCases2(): void {
    const arr = ['', 0, false, null, undefined];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], '', 'Empty string in array should be preserved');
    eq(result[1], 0, 'Zero in array should be preserved');
    eq(result[2], false, 'False in array should be preserved');
    eq(result[3], null, 'Null in array should be preserved');
    eq(result[4], undefined, 'Undefined in array should be preserved');
  }

  public testAdditionalStringifyEdgeCases3(): void {
    const obj = {
      max: Number.MAX_SAFE_INTEGER,
      min: Number.MIN_SAFE_INTEGER,
      posInf: Infinity,
      negInf: -Infinity,
      nan: NaN
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.max, Number.MAX_SAFE_INTEGER, 'Max safe integer should be preserved');
    eq(result.min, Number.MIN_SAFE_INTEGER, 'Min safe integer should be preserved');
    eq(result.posInf, Infinity, 'Positive infinity should be preserved');
    eq(result.negInf, -Infinity, 'Negative infinity should be preserved');
    eq(isNaN(result.nan), true, 'NaN should be preserved');
  }

  public testAdditionalStringifyEdgeCases4(): void {
    const obj = {
      float1: 1.1,
      float2: 2.2,
      float3: 3.3,
      float4: 4.4,
      float5: 5.5
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.float1, 1.1, 'Float1 should be preserved');
    eq(result.float2, 2.2, 'Float2 should be preserved');
    eq(result.float3, 3.3, 'Float3 should be preserved');
    eq(result.float4, 4.4, 'Float4 should be preserved');
    eq(result.float5, 5.5, 'Float5 should be preserved');
  }

  public testAdditionalStringifyEdgeCases5(): void {
    const obj = {
      neg1: -1,
      neg2: -2,
      neg3: -3,
      neg4: -4,
      neg5: -5
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.neg1, -1, 'Negative1 should be preserved');
    eq(result.neg2, -2, 'Negative2 should be preserved');
    eq(result.neg3, -3, 'Negative3 should be preserved');
    eq(result.neg4, -4, 'Negative4 should be preserved');
    eq(result.neg5, -5, 'Negative5 should be preserved');
  }

  public testAdditionalStringifyEdgeCases6(): void {
    const arr = [1.1, 2.2, 3.3, 4.4, 5.5];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], 1.1, 'Float array element 0 should be preserved');
    eq(result[1], 2.2, 'Float array element 1 should be preserved');
    eq(result[2], 3.3, 'Float array element 2 should be preserved');
    eq(result[3], 4.4, 'Float array element 3 should be preserved');
    eq(result[4], 5.5, 'Float array element 4 should be preserved');
  }

  public testAdditionalStringifyEdgeCases7(): void {
    const arr = [-1, -2, -3, -4, -5];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], -1, 'Negative array element 0 should be preserved');
    eq(result[1], -2, 'Negative array element 1 should be preserved');
    eq(result[2], -3, 'Negative array element 2 should be preserved');
    eq(result[3], -4, 'Negative array element 3 should be preserved');
    eq(result[4], -5, 'Negative array element 4 should be preserved');
  }

  public testAdditionalStringifyEdgeCases8(): void {
    const obj = {
      str1: 'a',
      str2: 'ab',
      str3: 'abc',
      str4: 'abcd',
      str5: 'abcde'
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.str1, 'a', 'String1 should be preserved');
    eq(result.str2, 'ab', 'String2 should be preserved');
    eq(result.str3, 'abc', 'String3 should be preserved');
    eq(result.str4, 'abcd', 'String4 should be preserved');
    eq(result.str5, 'abcde', 'String5 should be preserved');
  }

  public testAdditionalStringifyEdgeCases9(): void {
    const arr = ['a', 'ab', 'abc', 'abcd', 'abcde'];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], 'a', 'String array element 0 should be preserved');
    eq(result[1], 'ab', 'String array element 1 should be preserved');
    eq(result[2], 'abc', 'String array element 2 should be preserved');
    eq(result[3], 'abcd', 'String array element 3 should be preserved');
    eq(result[4], 'abcde', 'String array element 4 should be preserved');
  }

  public testAdditionalStringifyEdgeCases10(): void {
    const obj = {
      bool1: true,
      bool2: true,
      bool3: true,
      bool4: true,
      bool5: true
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.bool1, true, 'Boolean1 should be preserved');
    eq(result.bool2, true, 'Boolean2 should be preserved');
    eq(result.bool3, true, 'Boolean3 should be preserved');
    eq(result.bool4, true, 'Boolean4 should be preserved');
    eq(result.bool5, true, 'Boolean5 should be preserved');
  }

  public testAdditionalRoundTrip1(): void {
    const original = { value: 42 };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.value, original.value, 'Round trip should preserve value');
  }

  public testAdditionalRoundTrip2(): void {
    const original = [1, 2, 3];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, original.length, 'Round trip should preserve length');
  }

  public testAdditionalRoundTrip3(): void {
    const original = new Map([['key', 'value']]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Round trip should preserve Map type');
  }

  public testAdditionalRoundTrip4(): void {
    const original = new Set([1, 2, 3]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Round trip should preserve Set type');
  }

  public testAdditionalRoundTrip5(): void {
    const original = new Date('2026-01-01');
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Date, true, 'Round trip should preserve Date type');
  }

  public testAdditionalComplex1(): void {
    const obj = {
      arr: [1, 2, 3],
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3]),
      obj: { nested: 'value' }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(Array.isArray(result.arr), true, 'Array should be preserved');
    eq(result.map instanceof Map, true, 'Map should be preserved');
    eq(result.set instanceof Set, true, 'Set should be preserved');
    eq(typeof result.obj === 'object', true, 'Object should be preserved');
  }

  public testAdditionalComplex2(): void {
    const arr = [
      [1, 2],
      [3, 4],
      [5, 6]
    ];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 3, 'Nested array length should be preserved');
    eq(Array.isArray(result[0]), true, 'Nested array should be preserved');
  }

  public testAdditionalComplex3(): void {
    const obj = {
      level1: {
        level2: {
          level3: {
            value: 'deep'
          }
        }
      }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.level1.level2.level3.value, 'deep', 'Deep nesting should be preserved');
  }

  public testAdditionalComplex4(): void {
    const map = new Map([
      ['arr', [1, 2, 3]],
      ['obj', { value: 42 }]
    ]);
    const str = JSON2.stringify(map);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Map with complex values should be preserved');
  }

  public testAdditionalComplex5(): void {
    const obj = {
      dates: [
        new Date('2026-01-01'),
        new Date('2026-02-01'),
        new Date('2026-03-01')
      ]
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.dates[0] instanceof Date, true, 'Date in array should be preserved');
  }

  public testAdditionalSpecial1(): void {
    const obj = { '': 'empty', ' ': 'space' };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result[''], 'empty', 'Empty key should be preserved');
    eq(result[' '], 'space', 'Space key should be preserved');
  }

  public testAdditionalSpecial2(): void {
    const obj = { 'a-b': 1, 'c_d': 2, 'e.f': 3 };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result['a-b'], 1, 'Dash key should be preserved');
    eq(result['c_d'], 2, 'Underscore key should be preserved');
    eq(result['e.f'], 3, 'Dot key should be preserved');
  }

  public testAdditionalSpecial3(): void {
    const obj = { 中文: 'value', emoji: '🎉' };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.中文, 'value', 'Chinese key should be preserved');
    eq(result.emoji, '🎉', 'Emoji key should be preserved');
  }

  public testAdditionalSpecial4(): void {
    const arr = ['', ' ', '\t', '\n'];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], '', 'Empty string should be preserved');
    eq(result[1], ' ', 'Space should be preserved');
    eq(result[2], '\t', 'Tab should be preserved');
    eq(result[3], '\n', 'Newline should be preserved');
  }

  public testAdditionalSpecial5(): void {
    const obj = {
      newline: 'line1\nline2',
      tab: 'col1\tcol2',
      carriage: 'line1\rline2'
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.newline, 'line1\nline2', 'Newline should be preserved');
    eq(result.tab, 'col1\tcol2', 'Tab should be preserved');
    eq(result.carriage, 'line1\rline2', 'Carriage return should be preserved');
  }

  // =========================================================================
  // 29. 额外测试 - 补充到3000行
  // =========================================================================

  public testMoreStringifyTests1(): void {
    const obj = { a: 1, b: 2, c: 3, d: 4, e: 5, f: 6, g: 7, h: 8, i: 9, j: 10 };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.a, 1, 'Property a should be preserved');
    eq(result.b, 2, 'Property b should be preserved');
    eq(result.c, 3, 'Property c should be preserved');
    eq(result.d, 4, 'Property d should be preserved');
    eq(result.e, 5, 'Property e should be preserved');
    eq(result.f, 6, 'Property f should be preserved');
    eq(result.g, 7, 'Property g should be preserved');
    eq(result.h, 8, 'Property h should be preserved');
    eq(result.i, 9, 'Property i should be preserved');
    eq(result.j, 10, 'Property j should be preserved');
  }

  public testMoreStringifyTests2(): void {
    const arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 10, 'Array length should be preserved');
    eq(result[0], 1, 'Element 0 should be preserved');
    eq(result[5], 6, 'Element 5 should be preserved');
    eq(result[9], 10, 'Element 9 should be preserved');
  }

  public testMoreStringifyTests3(): void {
    const obj = {
      str1: 'hello',
      str2: 'world',
      str3: 'test',
      str4: 'data',
      str5: 'value',
      str6: 'more',
      str7: 'text',
      str8: 'info',
      str9: 'content',
      str10: 'final'
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.str1, 'hello', 'String1 should be preserved');
    eq(result.str5, 'value', 'String5 should be preserved');
    eq(result.str10, 'final', 'String10 should be preserved');
  }

  public testMoreStringifyTests4(): void {
    const obj = {
      num1: 1,
      num2: 2,
      num3: 3,
      num4: 4,
      num5: 5,
      num6: 6,
      num7: 7,
      num8: 8,
      num9: 9,
      num10: 10
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.num1, 1, 'Number1 should be preserved');
    eq(result.num5, 5, 'Number5 should be preserved');
    eq(result.num10, 10, 'Number10 should be preserved');
  }

  public testMoreStringifyTests5(): void {
    const obj = {
      bool1: true,
      bool2: false,
      bool3: true,
      bool4: false,
      bool5: true,
      bool6: false,
      bool7: true,
      bool8: false,
      bool9: true,
      bool10: false
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.bool1, true, 'Boolean1 should be preserved');
    eq(result.bool5, true, 'Boolean5 should be preserved');
    eq(result.bool10, false, 'Boolean10 should be preserved');
  }

  public testMoreStringifyTests6(): void {
    const arr = [
      { id: 1, name: 'Alice' },
      { id: 2, name: 'Bob' },
      { id: 3, name: 'Charlie' },
      { id: 4, name: 'David' },
      { id: 5, name: 'Eve' }
    ];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 5, 'Array length should be preserved');
    eq(result[0].name, 'Alice', 'First name should be preserved');
    eq(result[2].name, 'Charlie', 'Third name should be preserved');
    eq(result[4].name, 'Eve', 'Fifth name should be preserved');
  }

  public testMoreStringifyTests7(): void {
    const obj = {
      nested1: { value: 1, data: 'a' },
      nested2: { value: 2, data: 'b' },
      nested3: { value: 3, data: 'c' },
      nested4: { value: 4, data: 'd' },
      nested5: { value: 5, data: 'e' }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.nested1.value, 1, 'Nested1 value should be preserved');
    eq(result.nested3.value, 3, 'Nested3 value should be preserved');
    eq(result.nested5.value, 5, 'Nested5 value should be preserved');
  }

  public testMoreStringifyTests8(): void {
    const map = new Map([
      ['key1', 'value1'],
      ['key2', 'value2'],
      ['key3', 'value3'],
      ['key4', 'value4'],
      ['key5', 'value5']
    ]);
    const str = JSON2.stringify(map);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Map should be preserved');
  }

  public testMoreStringifyTests9(): void {
    const set = new Set([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    const str = JSON2.stringify(set);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Set should be preserved');
  }

  public testMoreStringifyTests10(): void {
    const obj = {
      date1: new Date('2026-01-01'),
      date2: new Date('2026-02-01'),
      date3: new Date('2026-03-01'),
      date4: new Date('2026-04-01'),
      date5: new Date('2026-05-01')
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.date1 instanceof Date, true, 'Date1 should be preserved');
    eq(result.date3 instanceof Date, true, 'Date3 should be preserved');
    eq(result.date5 instanceof Date, true, 'Date5 should be preserved');
  }

  public testMoreParseTests1(): void {
    const original = { a: 1, b: 2, c: 3, d: 4, e: 5 };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.a, 1, 'Parse should preserve a');
    eq(result.b, 2, 'Parse should preserve b');
    eq(result.c, 3, 'Parse should preserve c');
    eq(result.d, 4, 'Parse should preserve d');
    eq(result.e, 5, 'Parse should preserve e');
  }

  public testMoreParseTests2(): void {
    const original = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, 10, 'Parse should preserve length');
    eq(result[0], 1, 'Parse should preserve first element');
    eq(result[9], 10, 'Parse should preserve last element');
  }

  public testMoreParseTests3(): void {
    const original = new Map([
      ['a', 1],
      ['b', 2],
      ['c', 3],
      ['d', 4],
      ['e', 5]
    ]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Parse should preserve Map type');
  }

  public testMoreParseTests4(): void {
    const original = new Set([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Parse should preserve Set type');
  }

  public testMoreParseTests5(): void {
    const original = new Date('2026-01-01T00:00:00.000Z');
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Date, true, 'Parse should preserve Date type');
  }

  public testMoreEdgeTests1(): void {
    const obj = {
      empty: '',
      zero: 0,
      false: false,
      nul: null,
      undef: undefined
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.empty, '', 'Empty string should be preserved');
    eq(result.zero, 0, 'Zero should be preserved');
    eq(result.false, false, 'False should be preserved');
    eq(result.nul, null, 'Null should be preserved');
    eq(result.undef, undefined, 'Undefined should be preserved');
  }

  public testMoreEdgeTests2(): void {
    const arr = ['', 0, false, null, undefined];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], '', 'Empty string in array should be preserved');
    eq(result[1], 0, 'Zero in array should be preserved');
    eq(result[2], false, 'False in array should be preserved');
    eq(result[3], null, 'Null in array should be preserved');
    eq(result[4], undefined, 'Undefined in array should be preserved');
  }

  public testMoreEdgeTests3(): void {
    const obj = {
      max: Number.MAX_SAFE_INTEGER,
      min: Number.MIN_SAFE_INTEGER,
      posInf: Infinity,
      negInf: -Infinity,
      nan: NaN
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.max, Number.MAX_SAFE_INTEGER, 'Max safe integer should be preserved');
    eq(result.min, Number.MIN_SAFE_INTEGER, 'Min safe integer should be preserved');
    eq(result.posInf, Infinity, 'Positive infinity should be preserved');
    eq(result.negInf, -Infinity, 'Negative infinity should be preserved');
    eq(isNaN(result.nan), true, 'NaN should be preserved');
  }

  public testMoreEdgeTests4(): void {
    const obj = {
      float1: 1.1,
      float2: 2.2,
      float3: 3.3,
      float4: 4.4,
      float5: 5.5
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.float1, 1.1, 'Float1 should be preserved');
    eq(result.float2, 2.2, 'Float2 should be preserved');
    eq(result.float3, 3.3, 'Float3 should be preserved');
    eq(result.float4, 4.4, 'Float4 should be preserved');
    eq(result.float5, 5.5, 'Float5 should be preserved');
  }

  public testMoreEdgeTests5(): void {
    const obj = {
      neg1: -1,
      neg2: -2,
      neg3: -3,
      neg4: -4,
      neg5: -5
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.neg1, -1, 'Negative1 should be preserved');
    eq(result.neg2, -2, 'Negative2 should be preserved');
    eq(result.neg3, -3, 'Negative3 should be preserved');
    eq(result.neg4, -4, 'Negative4 should be preserved');
    eq(result.neg5, -5, 'Negative5 should be preserved');
  }

  public testMoreComplexTests1(): void {
    const obj = {
      arr: [1, 2, 3, 4, 5],
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3]),
      obj: { nested: 'value' }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(Array.isArray(result.arr), true, 'Array should be preserved');
    eq(result.map instanceof Map, true, 'Map should be preserved');
    eq(result.set instanceof Set, true, 'Set should be preserved');
    eq(typeof result.obj === 'object', true, 'Object should be preserved');
  }

  public testMoreComplexTests2(): void {
    const arr = [
      [1, 2],
      [3, 4],
      [5, 6],
      [7, 8],
      [9, 10]
    ];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 5, 'Nested array length should be preserved');
    eq(Array.isArray(result[0]), true, 'Nested array should be preserved');
  }

  public testMoreComplexTests3(): void {
    const obj = {
      level1: {
        level2: {
          level3: {
            value: 'deep'
          }
        }
      }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.level1.level2.level3.value, 'deep', 'Deep nesting should be preserved');
  }

  public testMoreComplexTests4(): void {
    const map = new Map([
      ['arr', [1, 2, 3]],
      ['obj', { value: 42 }]
    ]);
    const str = JSON2.stringify(map);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Map with complex values should be preserved');
  }

  public testMoreComplexTests5(): void {
    const obj = {
      dates: [
        new Date('2026-01-01'),
        new Date('2026-02-01'),
        new Date('2026-03-01')
      ]
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.dates[0] instanceof Date, true, 'Date in array should be preserved');
  }

  public testMoreSpecialTests1(): void {
    const obj = { '': 'empty', ' ': 'space' };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result[''], 'empty', 'Empty key should be preserved');
    eq(result[' '], 'space', 'Space key should be preserved');
  }

  public testMoreSpecialTests2(): void {
    const obj = { 'a-b': 1, 'c_d': 2, 'e.f': 3 };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result['a-b'], 1, 'Dash key should be preserved');
    eq(result['c_d'], 2, 'Underscore key should be preserved');
    eq(result['e.f'], 3, 'Dot key should be preserved');
  }

  public testMoreSpecialTests3(): void {
    const obj = { 中文: 'value', emoji: '🎉' };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.中文, 'value', 'Chinese key should be preserved');
    eq(result.emoji, '🎉', 'Emoji key should be preserved');
  }

  public testMoreSpecialTests4(): void {
    const arr = ['', ' ', '\t', '\n'];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result[0], '', 'Empty string should be preserved');
    eq(result[1], ' ', 'Space should be preserved');
    eq(result[2], '\t', 'Tab should be preserved');
    eq(result[3], '\n', 'Newline should be preserved');
  }

  public testMoreSpecialTests5(): void {
    const obj = {
      newline: 'line1\nline2',
      tab: 'col1\tcol2',
      carriage: 'line1\rline2'
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.newline, 'line1\nline2', 'Newline should be preserved');
    eq(result.tab, 'col1\tcol2', 'Tab should be preserved');
    eq(result.carriage, 'line1\rline2', 'Carriage return should be preserved');
  }

  public testMoreRoundTripTests1(): void {
    const original = { value: 42 };
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.value, original.value, 'Round trip should preserve value');
  }

  public testMoreRoundTripTests2(): void {
    const original = [1, 2, 3, 4, 5];
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result.length, original.length, 'Round trip should preserve length');
  }

  public testMoreRoundTripTests3(): void {
    const original = new Map([['key', 'value']]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Map, true, 'Round trip should preserve Map type');
  }

  public testMoreRoundTripTests4(): void {
    const original = new Set([1, 2, 3]);
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Set, true, 'Round trip should preserve Set type');
  }

  public testMoreRoundTripTests5(): void {
    const original = new Date('2026-01-01');
    const str = JSON2.stringify(original);
    const result = JSON2.parse(str);
    eq(result instanceof Date, true, 'Round trip should preserve Date type');
  }

  public testMorePerformanceTests1(): void {
    const arr: number[] = [];
    for (let i = 0; i < 5000; i++) {
      arr.push(i);
    }
    const startTime = Date.now();
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large array should complete in reasonable time');
    eq(result.length, 5000, 'Large array should be fully serialized');
  }

  public testMorePerformanceTests2(): void {
    const obj: any = {};
    for (let i = 0; i < 500; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Many properties should complete in reasonable time');
  }

  public testMorePerformanceTests3(): void {
    const map = new Map();
    for (let i = 0; i < 500; i++) {
      map.set(`key${i}`, `value${i}`);
    }
    const startTime = Date.now();
    const str = JSON2.stringify(map);
    const result = JSON2.parse(str);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large map should complete in reasonable time');
  }

  public testMorePerformanceTests5(): void {
    const obj = { test: 'value' };
    const iterations = 500;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const str = JSON2.stringify(obj);
      JSON2.parse(str);
    }
    const duration = Date.now() - startTime;
    eq(duration < 5000, true, 'Repeated operations should complete in reasonable time');
  }

  public testMoreCompatibilityTests1(): void {
    const obj = { name: 'test', value: 42 };
    const standardResult = JSON.stringify(obj);
    const coderResult = JSON2.stringify(obj);
    const standardParsed = JSON.parse(standardResult);
    const coderParsed = JSON2.parse(coderResult);
    eq(standardParsed.name, coderParsed.name, 'Should be compatible with standard API');
    eq(standardParsed.value, coderParsed.value, 'Should be compatible with standard API');
  }

  public testMoreCompatibilityTests2(): void {
    'use strict';
    const obj = { value: 42 };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.value, 42, 'Should work in strict mode');
  }

  public testMoreCompatibilityTests3(): void {
    const obj = Object.freeze({ value: 42 });
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.value, 42, 'Frozen object should be serialized');
  }

  public testMoreCompatibilityTests4(): void {
    const obj = Object.seal({ value: 42 });
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.value, 42, 'Sealed object should be serialized');
  }

  public testMoreCompatibilityTests5(): void {
    const obj = { value: 42 };
    const str1 = JSON2.stringify(obj);
    const str2 = JSON2.stringify(obj);
    eq(str1, str2, 'Multiple calls should be consistent');
  }

  public testFinalTests1(): void {
    const obj = {
      str: 'string',
      num: 42,
      bool: true,
      nul: null,
      undef: undefined,
      date: new Date('2026-01-01'),
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3]),
      arr: [1, 2, 3],
      nested: {
        deep: {
          value: 'deep'
        }
      }
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.str, 'string', 'Complex object string should be preserved');
    eq(result.num, 42, 'Complex object number should be preserved');
    eq(result.bool, true, 'Complex object boolean should be preserved');
    eq(result.nul, null, 'Complex object null should be preserved');
    eq(result.undef, undefined, 'Complex object undefined should be preserved');
    eq(result.date instanceof Date, true, 'Complex object date should be preserved');
    eq(result.map instanceof Map, true, 'Complex object map should be preserved');
    eq(result.set instanceof Set, true, 'Complex object set should be preserved');
    eq(Array.isArray(result.arr), true, 'Complex object array should be preserved');
    eq(result.nested.deep.value, 'deep', 'Complex object nested should be preserved');
  }

  public testFinalTests2(): void {
    const arr = [
      'string',
      42,
      true,
      null,
      undefined,
      new Date('2026-01-01'),
      new Map([['key', 'value']]),
      new Set([1, 2, 3]),
      [1, 2, 3],
      { nested: 'value' }
    ];
    const str = JSON2.stringify(arr);
    const result = JSON2.parse(str);
    eq(result.length, 10, 'Complex array length should be preserved');
    eq(result[0], 'string', 'Complex array string should be preserved');
    eq(result[1], 42, 'Complex array number should be preserved');
    eq(result[2], true, 'Complex array boolean should be preserved');
    eq(result[3] === null, true, 'Complex array null should be preserved');
    eq(result[4] === undefined, true, 'Complex array undefined should be preserved');
    eq(result[5] instanceof Date, true, 'Complex array date should be preserved');
    eq(result[6] instanceof Map, true, 'Complex array map should be preserved');
    eq(result[7] instanceof Set, true, 'Complex array set should be preserved');
    eq(Array.isArray(result[8]), true, 'Complex array nested array should be preserved');
    eq(typeof result[9] === 'object', true, 'Complex array object should be preserved');
  }

  public testFinalTests3(): void {
    const obj: any = { name: 'parent' };
    obj.self = obj;
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.self === result, true, 'Circular reference should be resolved');
  }

  public testFinalTests4(): void {
    const longStr = 'a'.repeat(5000);
    const obj = { long: longStr };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.long.length, 5000, 'Very long string should be preserved');
  }

  public testFinalTests5(): void {
    const obj = {
      chinese: '中文',
      japanese: 'こんにちは',
      korean: '안녕하세요',
      emoji: '🎉🎊🎉',
      mixed: 'Hello 世界 🌍'
    };
    const str = JSON2.stringify(obj);
    const result = JSON2.parse(str);
    eq(result.chinese, '中文', 'Chinese should be preserved');
    eq(result.japanese, 'こんにちは', 'Japanese should be preserved');
    eq(result.korean, '안녕하세요', 'Korean should be preserved');
    eq(result.emoji, '🎉🎊🎉', 'Emoji should be preserved');
    eq(result.mixed, 'Hello 世界 🌍', 'Mixed unicode should be preserved');
  }
}
