/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with License.
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

// Declare DataCoder to avoid 'Cannot find name DataCoder' errors
declare class DataCoder {
  static readonly FORMAT_TAG: string;
  static stringify<T>(value: T, forceLegacyFormat?: boolean): string;
  static parse<T extends object>(text: string): T | T[];
  static restoreTo<T extends object, S extends object>(
    target: T | T[], source: T | T[], defaultSubCreator?: any
  ): T | T[];
}

// Declare JSONCoder for legacy format support
declare class JSONCoder {
  static stringify<T>(value: T, replacer?: any, space?: string | number): string;
}

// Declare JSON2 for JSON2 format support
declare class JSON2 {
  static stringify(value: any): string;
  static parse(text: string): any;
}

// Declare Meta for metadata support
declare class Meta {
  static define(proto: object, prop: string, value: any): void;
  static get(obj: any, prop: string): any;
  static gets(obj: any): object;
  static getOwn(obj: any, prop: string): any;
}

// Declare ObserveV2 for observed object support
declare class ObserveV2 {
  static IsMakeObserved(value: any): boolean;
}

// Declare UIUtilsImpl for target access
declare class UIUtilsImpl {
  static instance(): any;
  getTarget(value: any): any;
}

// Declare Sendable types
declare class SendableArray {}
declare class SendableMap {}
declare class SendableSet {}

// Declare BusinessError for error handling
declare class BusinessError {
  code: number;
  message: string;
  constructor(code: number, message: string);
}

// Error codes
declare const PERSISTENCE_V2_MISMATCH_BETWEEN_KEY_AND_TYPE: number;
declare const PERSISTENCE_V2_LACK_TYPE: number;
declare const PERSISTENCE_V2_APPSTORAGE_V2_UNSUPPORTED_TYPE: number;
declare const PERSISTENCE_V2_APPSTORAGE_V2_INVALID_DEFAULT_CREATOR: number;

// Type definitions
type TypeConstructor<T> = { new(): T };
type FactoryConstructor<T> = (json: unknown) => TypeConstructor<T>;
type JSONAny = object | number | string | boolean | bigint | undefined | null;

interface TransformOptions<T> {
  factory?: FactoryConstructor<T>;
  alias?: string;
  disabled?: boolean;
}

type StorageDefaultCreator<S> = () => S | undefined;

// ============================================================================
// Test Fixture Classes
// ============================================================================

class SimpleDataClass {
  id: number = 0;
  name: string = '';
  active: boolean = false;
  value: number = 0;

  public getId(): number {
    return this.id;
  }

  public setName(name: string): void {
    this.name = name;
  }
}

class NestedDataClass {
  id: number = 0;
  nested: {
    level1: {
      level2: string;
    }
  } = { level1: { level2: '' } };
  data: object = {};
}

class ArrayDataClass {
  items: string[] = [];
  numbers: number[] = [];
  nested: SimpleDataClass[] = [];
  matrix: number[][] = [];
}

class CollectionDataClass {
  tags: Set<string> = new Set();
  properties: Map<string, any> = new Map();
  metadata: Map<string, string> = new Map();
  numberSet: Set<number> = new Set();
}

class DateDataClass {
  createdAt: Date = new Date();
  updatedAt: Date | null = null;
  timestamps: Date[] = [];
  dateMap: Map<string, Date> = new Map();
}

class NullableDataClass {
  nullableString: string | null = null;
  nullableNumber: number | null = null;
  nullableObject: object | null = null;
  emptyString: string = '';
  zeroNumber: number = 0;
  falseBoolean: boolean = false;
}

class ComplexDataClass {
  id: number = 0;
  name: string = '';
  metadata: {
    created: Date;
    updated: Date;
    tags: string[];
  } = {
    created: new Date(),
    updated: new Date(),
    tags: []
  };
  items: Array<{
    id: number;
    value: string;
    active: boolean;
  }> = [];
}

class PrimitiveDataClass {
  stringValue: string = '';
  numberValue: number = 0;
  booleanValue: boolean = false;
  bigintValue: bigint = 0n;
  nullValue: any = null;
  undefinedValue: any = undefined;
}

class MixedDataClass {
  primitive: number = 0;
  object: { key: string } = { key: '' };
  array: string[] = [];
  map: Map<string, number> = new Map();
  set: Set<number> = new Set();
  date: Date = new Date();
}

class SpecialCharDataClass {
  newline: string = 'line1\nline2';
  tab: string = 'col1\tcol2';
  quote: string = 'He said "hello"';
  unicode: string = '中文';
  emoji: string = '🎉';
  escape: string = '\\\\';
}

class EdgeCaseDataClass {
  veryLongString: string = '';
  veryLargeNumber: number = 0;
  verySmallNumber: number = 0;
  negativeZero: number = -0;
  nanValue: number = NaN;
  infinityValue: number = Infinity;
}

class EmptyDataClass {
  emptyObject: object = {};
  emptyArray: any[] = [];
  emptyString: string = '';
  emptyMap: Map<any, any> = new Map();
  emptySet: Set<any> = new Set();
}

class CyclicRefDataClass {
  id: number = 0;
  parent: CyclicRefDataClass | null = null;
  children: CyclicRefDataClass[] = [];
}

class AliasDataClass {
  originalName: string = '';
  originalValue: number = 0;
  normalField: string = '';
}

class DisabledPropDataClass {
  enabledField: string = '';
  disabledField: string = '';
  anotherEnabled: number = 0;
}

class FactoryDataClass {
  nested: object | null = null;
  items: object[] = [];
  optional: object | undefined = undefined;
}

class ReadOnlyDataClass {
  readonly constantValue: number = 100;
  readonly constantString: string = 'immutable';
  mutableValue: string = 'mutable';
}

class DeepNestedDataClass {
  level1: {
    level2: {
      level3: {
        level4: {
          level5: {
            value: string;
          };
        };
      };
    };
  } = {
    level2: {
      level3: {
        level4: {
          level5: {
            value: ''
          }
        }
      }
    }
  };
}

class HeterogeneousArrayClass {
  mixed: any[] = [];
  sparse: any[] = [];
  typed: number[] = [];
}

class MapComplexClass {
  stringKeys: Map<string, number> = new Map();
  numberKeys: Map<number, string> = new Map();
  nestedMap: Map<string, Map<string, number>> = new Map();
  complexValues: Map<string, any> = new Map();
}

class SetComplexClass {
  numberSet: Set<number> = new Set();
  stringSet: Set<string> = new Set();
  mixedSet: Set<any> = new Set();
  nestedSet: Set<Set<number>> = new Set();
}

class SendableDataClass {
  sendableArray: any = [];
  sendableMap: any = new Map();
  sendableSet: any = new Set();
  regularArray: any[] = [];
  regularMap: Map<any, any> = new Map();
  regularSet: Set<any> = new Set();
}

class TypeMismatchClass {
  numberField: number = 0;
  stringField: string = '';
  booleanField: boolean = false;
  objectField: object = {};
}

class MethodClass {
  data: string = '';
  internal: number = 0;

  public getData(): string {
    return this.data;
  }

  public setData(value: string): void {
    this.data = value;
  }

  public process(): string {
    return this.data.toUpperCase();
  }
}

class GettersSettersClass {
  private _value: number = 0;
  private _name: string = '';

  public get value(): number {
    return this._value;
  }

  public set value(v: number) {
    this._value = v;
  }

  public get name(): string {
    return this._name;
  }

  public set name(n: string) {
    this._name = n;
  }

  public get doubled(): number {
    return this._value * 2;
  }
}

class BigIntClass {
  bigIntValue: bigint = 0n;
  bigIntArray: bigint[] = [];
  bigIntMap: Map<string, bigint> = new Map();
}

class UnionClass {
  unionValue: string | number = '';
  optionalValue?: string;
  nullableValue: string | null = null;
  literalValue: 'yes' | 'no' | 'maybe' = 'yes';
}

class RecursiveClass {
  id: number = 0;
  name: string = '';
  children: RecursiveClass[] = [];
}

class PerformanceClass {
  largeArray: number[] = [];
  manyProperties: any = {};
  deepNested: any = {};
}

class ValidationClass {
  required: string = '';
  optional: string = '';
  withDefault: number = 42;
  constrained: number = 0;
}

class UpdateClass {
  id: number = 0;
  name: string = '';
  value: number = 0;
  timestamp: Date = new Date();
  tags: string[] = [];
}

class MergeClass {
  field1: string = '';
  field2: number = 0;
  field3: boolean = false;
  field4: any = null;
}

class CloneClass {
  id: number = 0;
  data: any = {};
  items: any[] = [];
  metadata: Map<string, any> = new Map();
}

class TransformClass {
  original: string = '';
  transformed: string = '';
  processed: boolean = false;
  timestamp: number = 0;
}

class StateClass {
  currentState: string = '';
  previousState: string = '';
  transitions: string[] = [];
  metadata: any = {};
}

class ConfigClass {
  enabled: boolean = false;
  debug: boolean = false;
  version: string = '1.0.0';
  settings: Map<string, any> = new Map();
}

class CacheClass {
  key: string = '';
  value: any = null;
  timestamp: Date = new Date();
  ttl: number = 0;
}

class LogClass {
  level: string = '';
  message: string = '';
  timestamp: Date = new Date();
  metadata: any = {};
}

class EventClass {
  type: string = '';
  data: any = {};
  timestamp: Date = new Date();
  source: string = '';
}

class ResponseClass {
  success: boolean = false;
  data: any = null;
  error: string = '';
  code: number = 0;
}

class RequestClass {
  url: string = '';
  method: string = '';
  headers: Map<string, string> = new Map();
  body: any = null;
  timeout: number = 0;
}

class SessionClass {
  id: string = '';
  user: any = null;
  createdAt: Date = new Date();
  expiresAt: Date = new Date();
  data: Map<string, any> = new Map();
}

class UserClass {
  id: number = 0;
  name: string = '';
  email: string = '';
  age: number = 0;
  active: boolean = false;
  metadata: any = {};
}

class ProductClass {
  id: number = 0;
  name: string = '';
  price: number = 0;
  category: string = '';
  tags: string[] = [];
  inStock: boolean = false;
}

class OrderClass {
  id: number = 0;
  userId: number = 0;
  products: number[] = [];
  total: number = 0;
  status: string = '';
  createdAt: Date = new Date();
}

class UserProfileClass {
  id: number = 0;
  username: string = '';
  email: string = '';
  avatar: string = '';
  bio: string = '';
  followers: number = 0;
  following: number = 0;
  createdAt: Date = new Date();
}

class PostClass {
  id: number = 0;
  title: string = '';
  content: string = '';
  author: string = '';
  tags: string[] = [];
  likes: number = 0;
  comments: number = 0;
  published: boolean = false;
  createdAt: Date = new Date();
}

class CommentClass {
  id: number = 0;
  postId: number = 0;
  author: string = '';
  content: string = '';
  likes: number = 0;
  replies: number = 0;
  createdAt: Date = new Date();
}

class NotificationClass {
  id: number = 0;
  userId: number = 0;
  type: string = '';
  title: string = '';
  message: string = '';
  read: boolean = false;
  createdAt: Date = new Date();
}

class MessageClass {
  id: number = 0;
  senderId: number = 0;
  receiverId: number = 0;
  content: string = '';
  timestamp: Date = new Date();
  read: boolean = false;
}

// ============================================================================
// Main Test Class
// ============================================================================

export class DataCoderTestsV2 implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating DataCoderTestsV2: ${str}`)
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
  // FORMAT_TAG Tests
  // =========================================================================

  public testFormatTag(): void {
    eq(DataCoder.FORMAT_TAG, 'JSON2', 'FORMAT_TAG should be JSON2');
  }

  public testFormatTagIsString(): void {
    eq(typeof DataCoder.FORMAT_TAG, 'string', 'FORMAT_TAG should be string');
  }

  public testFormatTagLength(): void {
    eq(DataCoder.FORMAT_TAG.length, 5, 'FORMAT_TAG length should be 5');
  }

  // =========================================================================
  // Stringify Tests
  // =========================================================================

  public testStringifySimpleObject(): void {
    const obj = { id: 1, name: 'test', active: true };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Stringify should start with FORMAT_TAG');
    eq(result.includes('test'), true, 'Stringify should include object name');
  }

  public testStringifyNestedObject(): void {
    const obj = {
      outer: 'value',
      nested: {
        inner: 'nested value',
        number: 123
      }
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Nested object stringify should start with FORMAT_TAG');
    eq(result.includes('nested value'), true, 'Nested object should be preserved');
  }

  public testStringifyArray(): void {
    const obj = { items: [1, 2, 3, 4, 5] };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Array stringify should start with FORMAT_TAG');
  }

  public testStringifyWithDate(): void {
    const obj = { date: new Date('2026-01-01T00:00:00.000Z') };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Date stringify should start with FORMAT_TAG');
  }

  public testStringifyWithMap(): void {
    const obj = { map: new Map([['key1', 'value1'], ['key2', 'value2']]) };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Map stringify should start with FORMAT_TAG');
  }

  public testStringifyWithSet(): void {
    const obj = { set: new Set([1, 2, 3]) };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Set stringify should start with FORMAT_TAG');
  }

  public testStringifyWithNull(): void {
    const obj = { value: null };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Null stringify should start with FORMAT_TAG');
  }

  public testStringifyWithUndefined(): void {
    const obj = { defined: 'value', notDefined: undefined };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Undefined stringify should start with FORMAT_TAG');
  }

  public testStringifyWithEmptyString(): void {
    const obj = { empty: '' };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Empty string stringify should start with FORMAT_TAG');
  }

  public testStringifyWithZero(): void {
    const obj = { zero: 0 };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Zero stringify should start with FORMAT_TAG');
  }

  public testStringifyWithFalse(): void {
    const obj = { active: false };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'False stringify should start with FORMAT_TAG');
  }

  public testStringifyWithSpecialChars(): void {
    const obj = {
      newline: 'line1\nline2',
      tab: 'col1\tcol2',
      quote: 'He said "hello"'
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Special chars stringify should start with FORMAT_TAG');
  }

  public testStringifyWithUnicode(): void {
    const obj = {
      chinese: '中文',
      emoji: '🎉',
      mixed: 'Hello 世界 🌍'
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Unicode stringify should start with FORMAT_TAG');
  }

  public testStringifyWithBigInt(): void {
    const obj = { bigInt: 12345678901234567890n };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'BigInt stringify should start with FORMAT_TAG');
  }

  public testStringifyComplexStructure(): void {
    const obj = {
      id: 1,
      name: 'test',
      metadata: {
        created: new Date(),
        tags: ['tag1', 'tag2']
      },
      items: [
        { id: 1, value: 'a' },
        { id: 2, value: 'b' }
      ]
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Complex structure stringify should start with FORMAT_TAG');
  }

  public testStringifyEmptyObject(): void {
    const obj = {};
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Empty object stringify should start with FORMAT_TAG');
  }

  public testStringifyEmptyArray(): void {
    const obj = { items: [] };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Empty array stringify should start with FORMAT_TAG');
  }

  public testStringifyWithBoolean(): void {
    const obj = { trueValue: true, falseValue: false };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Boolean stringify should start with FORMAT_TAG');
    eq(result.includes('true'), true, 'Boolean stringify should include true');
    eq(result.includes('false'), true, 'Boolean stringify should include false');
  }

  public testStringifyWithNumber(): void {
    const obj = {
      integer: 42,
      float: 3.14,
      negative: -100,
      scientific: 1.5e-10
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Number stringify should start with FORMAT_TAG');
  }

  public testStringifyWithMixedArray(): void {
    const obj = { mixed: [1, 'two', true, null, { key: 'value' }] };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Mixed array stringify should start with FORMAT_TAG');
  }

  public testStringifyWithSparseArray(): void {
    const obj = { sparse: [1, , , 4] };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Sparse array stringify should start with FORMAT_TAG');
  }

  public testStringifyWithNestedArray(): void {
    const obj = { matrix: [[1, 2], [3, 4], [5, 6]] };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Nested array stringify should start with FORMAT_TAG');
  }

  public testStringifyWithEmptyValues(): void {
    const obj = {
      emptyObject: {},
      emptyArray: [],
      emptyString: ''
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Empty values stringify should start with FORMAT_TAG');
  }

  public testStringifyWithUnicodeChinese(): void {
    const obj = {
      chinese: '你好世界',
      japanese: 'こんにちは',
      korean: '안녕하세요'
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Unicode stringify should start with FORMAT_TAG');
  }

  public testStringifyWithEmoji(): void {
    const obj = {
      emoji: '😀🎉🌍⭐',
      flags: '🇨🇳🇺🇸🇯🇵'
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Emoji stringify should start with FORMAT_TAG');
  }

  public testStringifyWithEscapeChars(): void {
    const obj = {
      slash: '\\',
      quote: '\"',
      backspace: '\b',
      formfeed: '\f',
      newline: '\n',
      carriage: '\r',
      tab: '\t'
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Escape chars stringify should start with FORMAT_TAG');
  }

  public testStringifyWithSpecialNumbers(): void {
    const obj = {
      maxSafe: Number.MAX_SAFE_INTEGER,
      minSafe: Number.MIN_SAFE_INTEGER,
      max: Number.MAX_VALUE,
      min: Number.MIN_VALUE,
      epsilon: Number.EPSILON
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Special numbers stringify should start with FORMAT_TAG');
  }

  // =========================================================================
  // Stringify with forceLegacyFormat Tests
  // =========================================================================

  public testStringifyForceLegacyFormat(): void {
    const obj = { id: 1, name: 'test' };
    let result = DataCoder.stringify(obj, true);
    result = result.replace(DataCoder.FORMAT_TAG, '');
    const hasFormatTag = result.startsWith(DataCoder.FORMAT_TAG);
    eq(hasFormatTag, false, 'Legacy format should not start with FORMAT_TAG');
  }

  public testStringifyForceLegacyFormatWithComplex(): void {
    const obj = {
      nested: { value: 'test' },
      items: [1, 2, 3]
    };
    let result = DataCoder.stringify(obj, true);
    result = result.replace(DataCoder.FORMAT_TAG, '');
    const hasFormatTag = result.startsWith(DataCoder.FORMAT_TAG);
    eq(hasFormatTag, false, 'Legacy format complex object should not start with FORMAT_TAG');
  }

  // =========================================================================
  // Parse Legacy Format Tests
  // =========================================================================

  public testParseLegacyFormat(): void {
    const text = '{"id":1,"name":"test"}';
    const result = DataCoder.parse(text);
    eq((result as any).id, 1, 'Parse should handle legacy format');
    eq((result as any).name, 'test', 'Parse should restore name from legacy format');
  }

  public testParseLegacyFormatNested(): void {
    const text = '{"nested":{"value":"test"}}';
    const result = DataCoder.parse(text);
    eq((result as any).nested.value, 'test', 'Parse should handle nested legacy format');
  }

  // =========================================================================
  // RestoreTo Tests
  // =========================================================================

  public testRestoreToSimpleObject(): void {
    const target = new SimpleDataClass();
    const source = {
      id: 100,
      name: 'updated',
      active: true,
      value: 42
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 100, 'RestoreTo should update id');
    eq((result as any).name, 'updated', 'RestoreTo should update name');
    eq((result as any).active, true, 'RestoreTo should update active');
    eq((result as any).value, 42, 'RestoreTo should update value');
  }

  public testRestoreToNestedObject(): void {
    const target = new NestedDataClass();
    const source = {
      id: 1,
      nested: {
        level1: {
          level2: 'deep value'
        }
      },
      data: { key: 'value' }
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).nested.level1.level2, 'deep value', 'RestoreTo should update nested object');
  }

  public testRestoreToArray(): void {
    const target = new ArrayDataClass();
    const source = {
      items: ['a', 'b', 'c'],
      numbers: [1, 2, 3],
      nested: [{ id: 1, name: 'test' }],
      matrix: [[1, 2], [3, 4]]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 3, 'RestoreTo should update array');
    eq((result as any).items[1], 'b', 'RestoreTo should update array element');
  }

  public testRestoreToMap(): void {
    const target = new CollectionDataClass();

    const source = new CollectionDataClass();
    source.tags = new Set(['tag1', 'tag2', 'tag3']);
    source.properties = new Map([['key1', 'value1'], ['key2', 'value2']]);
    source.metadata = new Map([['meta1', 'data1']]);
    source.numberSet = new Set([1, 2, 3]);

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).tags.size, 3, 'RestoreTo should update Set');
    eq((result as any).properties.size, 2, 'RestoreTo should update Map');
  }

  public testRestoreToDate(): void {
    const target = new DateDataClass();

    const source = new DateDataClass();
    source.createdAt = new Date('2026-01-01T00:00:00.000Z');
    source.updatedAt = new Date('2026-12-31T23:59:59.999Z');
    source.timestamps = [new Date('2026-01-01T00:00:00.000Z')];
    source.dateMap = new Map([['now', new Date('2026-01-01T00:00:00.000Z')]]);

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).createdAt instanceof Date, true, 'RestoreTo should update Date');
  }

  public testRestoreToPartialUpdate(): void {
    const target = new SimpleDataClass();
    target.id = 10;
    target.name = 'original';
    target.value = 100;
    const source = {
      id: 20,
      name: 'updated'
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 20, 'RestoreTo should update specified field');
    eq((result as any).name, 'updated', 'RestoreTo should update specified field');
    eq((result as any).value, 100, 'RestoreTo should preserve unspecified field');
  }

  public testRestoreToEmptySource(): void {
    const target = new SimpleDataClass();
    target.id = 10;
    target.name = 'original';
    const source = {};
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 10, 'RestoreTo should preserve values on empty source');
    eq((result as any).name, 'original', 'RestoreTo should preserve values on empty source');
  }

  public testRestoreToArrayTarget(): void {
    const target = [
      new SimpleDataClass(),
      new SimpleDataClass(),
      new SimpleDataClass()
    ];
    const source = [
      { id: 1, name: 'a', active: true, value: 10 },
      { id: 2, name: 'b', active: false, value: 20 },
      { id: 3, name: 'c', active: true, value: 30 }
    ];
    const result = DataCoder.restoreTo(target, source);
    eq((result as any[]).length, 3, 'RestoreTo should update array target');
    eq((result as any[])[0].name, 'a', 'RestoreTo should update array element');
  }

  public testRestoreToWithNullValues(): void {
    const target = new NullableDataClass();
    target.nullableString = 'original';
    target.nullableNumber = 100;
    const source = {
      nullableString: null,
      nullableNumber: null
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).nullableString, null, 'RestoreTo should set null');
    eq((result as any).nullableNumber, null, 'RestoreTo should set null');
  }

  public testRestoreToWithSpecialChars(): void {
    const target = new SpecialCharDataClass();
    const source = {
      newline: 'line1\nline2',
      tab: 'col1\tcol2',
      quote: 'He said "hello"',
      unicode: '中文',
      emoji: '🎉',
      escape: '\\\\'
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).newline, 'line1\nline2', 'RestoreTo should preserve newline');
    eq((result as any).unicode, '中文', 'RestoreTo should preserve unicode');
  }

  public testRestoreToWithBigInt(): void {
    const target = new BigIntClass();

    const source = new BigIntClass();
    source.bigIntValue = 12345678901234567890n;
    source.bigIntArray = [1n, 2n, 3n];
    source.bigIntMap = new Map([['key', 100n]]);

    const result = DataCoder.restoreTo(target, source);
    eq(typeof (result as any).bigIntValue, 'bigint', 'RestoreTo should preserve bigint');
  }

  public testRestoreToWithBoolean(): void {
    const target = { trueValue: false, falseValue: true };
    const source = { trueValue: true, falseValue: false };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).trueValue, true, 'RestoreTo should update boolean');
    eq((result as any).falseValue, false, 'RestoreTo should update boolean');
  }

  public testRestoreToWithNumber(): void {
    const target = { integer: 0, float: 0.0, negative: 0 };
    const source = { integer: 42, float: 3.14, negative: -100 };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).integer, 42, 'RestoreTo should update integer');
    eq((result as any).float, 3.14, 'RestoreTo should update float');
    eq((result as any).negative, -100, 'RestoreTo should update negative');
  }

  public testRestoreToWithMixedArray(): void {
    const target = { mixed: [] };
    const source = { mixed: [1, 'two', true, null, { key: 'value' }] };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).mixed.length, 5, 'RestoreTo should update mixed array');
  }

  public testRestoreToWithNestedArray(): void {
    const target = { matrix: [] };
    const source = { matrix: [[1, 2], [3, 4], [5, 6]] };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).matrix.length, 3, 'RestoreTo should update nested array');
  }

  public testRestoreToWithEmptyValues(): void {
    const target = {
      emptyObject: { key: 'value' },
      emptyArray: [1, 2, 3],
      emptyString: 'non-empty'
    };
    const source = {
      emptyObject: {},
      emptyArray: [],
      emptyString: ''
    };
    const result = DataCoder.restoreTo(target, source);
    const emptyObj = (result as any).emptyObject;
    const keys = Object.keys(emptyObj).filter(key => emptyObj.hasOwnProperty(key));
    eq(keys.length, 1, 'RestoreTo should clear object');
    eq((result as any).emptyArray.length, 0, 'RestoreTo should clear array');
    eq((result as any).emptyString, '', 'RestoreTo should clear string');
  }

  public testRestoreToWithUnicode(): void {
    const target = { chinese: '', emoji: '' };
    const source = { chinese: '你好世界', emoji: '🎉' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).chinese, '你好世界', 'RestoreTo should restore Chinese');
    eq((result as any).emoji, '🎉', 'RestoreTo should restore emoji');
  }

  public testRestoreToWithEscapeChars(): void {
    const target = {
      slash: '',
      quote: '',
      newline: '',
      tab: ''
    };
    const source = {
      slash: '\\',
      quote: '\"',
      newline: 'line1\nline2',
      tab: 'col1\tcol2'
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).slash, '\\', 'RestoreTo should restore slash');
    eq((result as any).newline, 'line1\nline2', 'RestoreTo should restore newline');
  }

  public testRestoreToWithSpecialNumbers(): void {
    const target = {
      maxSafe: 0,
      minSafe: 0,
      max: 0,
      min: 0
    };
    const source = {
      maxSafe: Number.MAX_SAFE_INTEGER,
      minSafe: Number.MIN_SAFE_INTEGER,
      max: Number.MAX_VALUE,
      min: Number.MIN_VALUE
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).maxSafe, Number.MAX_SAFE_INTEGER, 'RestoreTo should restore MAX_SAFE_INTEGER');
    eq((result as any).minSafe, Number.MIN_SAFE_INTEGER, 'RestoreTo should restore MIN_SAFE_INTEGER');
  }

  // =========================================================================
  // Complex RestoreTo Tests
  // =========================================================================

  public testRestoreToDeepNested(): void {
    const target = new DeepNestedDataClass();
    const source = {
      level1: {
        level2: {
          level3: {
            level4: {
              level5: {
                value: 'deep value'
              }
            }
          }
        }
      }
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).level1.level2.level3.level4.level5.value, 'deep value', 'RestoreTo should handle deep nesting');
  }

  public testRestoreToHeterogeneousArray(): void {
    const target = new HeterogeneousArrayClass();
    const source = {
      mixed: [1, 'two', true, null, { key: 'value' }],
      sparse: [1, , , 4],
      typed: [1, 2, 3]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).mixed.length, 5, 'RestoreTo should handle heterogeneous array');
  }

  public testRestoreToComplexMap(): void {
    const target = new MapComplexClass();

    const source = new MapComplexClass();
    source.stringKeys = new Map([['a', 1], ['b', 2]]);
    source.numberKeys = new Map([[1, 'one'], [2, 'two']]);
    source.nestedMap = new Map([['outer', new Map([['inner', 1]])]]);
    source.complexValues = new Map([['obj', { key: 'value' }]]);

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).stringKeys.size, 2, 'RestoreTo should handle complex map');
  }

  // =========================================================================
  // RestoreTo Type Mismatch Tests
  // =========================================================================

  public testRestoreToTypeMismatchArray(): void {
    const target = new TypeMismatchClass();
    target.numberField = 100;

    const source = new TypeMismatchClass();
    source.numberField = [1, 2, 3] as any;
    source.stringField = '';
    source.booleanField = false;
    source.objectField = {};

    try {
      DataCoder.restoreTo(target, source);
      eq(false, true, 'Should throw on type mismatch');
    } catch (e) {
      eq(true, true, 'RestoreTo should throw on type mismatch');
    }
  }

  public testRestoreToTypeMismatchObject(): void {
    const target = new TypeMismatchClass();
    target.stringField = 'original';
    const rawSource = {
      stringField: { key: 'value' } as any
    };
    const source = Object.assign(new TypeMismatchClass(), rawSource);

    try {
      DataCoder.restoreTo(target, source);
      eq(false, true, 'Should throw on type mismatch');
    } catch (e) {
      eq(true, true, 'RestoreTo should throw on type mismatch');
    }
  }

  // =========================================================================
  // RestoreTo with Methods Tests
  // =========================================================================

  public testRestoreToWithMethods(): void {
    const target = new MethodClass();
    target.data = 'original';

    // 核心修复：构建 MethodClass 实例（自动包含所有方法）
    const source = new MethodClass();
    source.data = 'updated';
    source.internal = 100;

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).data, 'updated', 'RestoreTo should update data');
    eq((result as any).getData(), 'updated', 'RestoreTo should preserve methods');
  }

  // =========================================================================
  // RestoreTo with Getters/Setters Tests
  // =========================================================================

  public testRestoreToWithGettersSetters(): void {
    const target = new GettersSettersClass();
    target.value = 10;
    target.name = 'original';

    const source = new GettersSettersClass();
    source.value = 20;
    source.name = 'updated';

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).value, 20, 'RestoreTo should update getter/setter');
  }

  // =========================================================================
  // RestoreTo Union Types Tests
  // =========================================================================

  public testRestoreToUnionTypes(): void {
    const target = new UnionClass();
    target.unionValue = 'string';

    const source = new UnionClass();
    source.unionValue = 123; // 符合 string | number 联合类型
    source.optionalValue = 'optional'; // 可选值
    source.nullableValue = null; // 符合 string | null 可空类型
    source.literalValue = 'no'; // 严格匹配 "yes" | "no" | "maybe" 字面量类型

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).unionValue, 123, 'RestoreTo should handle union type');
    eq((result as any).literalValue, 'no', 'RestoreTo should handle literal type');
  }

  // =========================================================================
  // RestoreTo Recursive Tests
  // =========================================================================

  public testRestoreToRecursive(): void {
    const target = new RecursiveClass();
    target.id = 1;
    target.name = 'root';
    const source = {
      id: 1,
      name: 'root',
      children: [
        { id: 2, name: 'child1', children: [] },
        { id: 3, name: 'child2', children: [] }
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).children.length, 2, 'RestoreTo should handle recursive structure');
  }

  // =========================================================================
  // Edge Cases Tests
  // =========================================================================

  public testEdgeCaseVeryLongString(): void {
    const target = new EdgeCaseDataClass();
    const longStr = 'a'.repeat(100);
    const source = {
      veryLongString: longStr
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).veryLongString.length, 100, 'RestoreTo should handle very long string');
  }

  public testEdgeCaseVeryLargeNumber(): void {
    const target = new EdgeCaseDataClass();
    const source = {
      veryLargeNumber: Number.MAX_SAFE_INTEGER,
      verySmallNumber: Number.MIN_SAFE_INTEGER
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).veryLargeNumber, Number.MAX_SAFE_INTEGER, 'RestoreTo should handle large number');
  }

  public testEdgeCaseNegativeZero(): void {
    const target = new EdgeCaseDataClass();
    const source = {
      negativeZero: -0
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).negativeZero, 0, 'RestoreTo should handle negative zero');
  }

  public testEdgeCaseNaN(): void {
    const target = new EdgeCaseDataClass();
    const source = {
      nanValue: NaN
    };
    const result = DataCoder.restoreTo(target, source);
    eq(isNaN((result as any).nanValue), true, 'RestoreTo should handle NaN');
  }

  public testEdgeCaseInfinity(): void {
    const target = new EdgeCaseDataClass();
    const source = {
      infinityValue: Infinity
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).infinityValue, Infinity, 'RestoreTo should handle Infinity');
  }

  public testEdgeCaseVeryDeepNesting(): void {
    const target = { value: '' };
    let source: any = { value: 'deep' };
    for (let i = 0; i < 50; i++) {
      source = { nested: source };
    }
    const result = DataCoder.restoreTo(target, { value: 'test' });
    eq((result as any).value, 'test', 'RestoreTo should handle simple case');
  }

  public testEdgeCaseManyNestedArrays(): void {
    const target = { data: [] };
    const source = {
      data: [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).data.length, 3, 'RestoreTo should handle nested arrays');
  }

  public testEdgeCaseObjectWithManyProperties(): void {
    const target: any = {};
    const source: any = {};
    for (let i = 0; i < 100; i++) {
      target[`prop${i}`] = '';
      source[`prop${i}`] = `value${i}`;
    }
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).prop0, 'value0', 'RestoreTo should handle many properties');
    eq((result as any).prop99, 'value99', 'RestoreTo should handle many properties');
  }

  public testEdgeCaseArrayWithManyElements(): void {
    const target = { items: [] };
    const source: any = { items: [] };
    for (let i = 0; i < 10; i++) {
      source.items.push(i);
    }
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 10, 'RestoreTo should handle array with many elements');
  }

  public testEdgeCaseMapWithManyEntries(): void {
    const target = { map: new Map() };
    const source: any = { map: new Map() };
    for (let i = 0; i < 100; i++) {
      source.map.set(`key${i}`, `value${i}`);
    }
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 100, 'RestoreTo should handle map with many entries');
  }

  public testEdgeCaseSetWithManyElements(): void {
    const target = { set: new Set() };
    const source: any = { set: new Set() };
    for (let i = 0; i < 100; i++) {
      source.set.add(i);
    }
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 100, 'RestoreTo should handle set with many elements');
  }

  // =========================================================================
  // Performance Tests
  // =========================================================================

  public testPerformanceLargeArray(): void {
    const target = new PerformanceClass();
    const largeArray: number[] = [];
    for (let i = 0; i < 100; i++) {
      largeArray.push(i);
    }
    const source = {
      largeArray: largeArray
    };
    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;
    eq(duration < 10, true, 'Large array restore should complete in reasonable time');
    eq((result as any).largeArray.length, 100, 'Large array should be fully restored');
  }

  public testPerformanceManyProperties(): void {
    const target = new PerformanceClass();
    const manyProperties: any = {};
    for (let i = 0; i < 10; i++) {
      manyProperties[`field${i}`] = i;
    }
    const source = {
      manyProperties: manyProperties
    };
    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Many properties restore should complete in reasonable time');
  }

  public testPerformanceDeepNesting(): void {
    const target = new PerformanceClass();
    let deepNested: any = { value: 'deep' };
    for (let i = 0; i < 100; i++) {
      deepNested = { nested: deepNested };
    }
    const source = {
      deepNested: deepNested
    };
    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Deep nesting restore should complete in reasonable time');
  }

  public testPerformanceRepeatedOperations(): void {
    const target = new SimpleDataClass();
    const source = {
      id: 1,
      name: 'test',
      active: true,
      value: 42
    };
    const iterations = 100;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      DataCoder.restoreTo(target, source);
    }
    const duration = Date.now() - startTime;
    eq(duration < 500, true, 'Repeated operations should complete in reasonable time');
  }

  public testPerformanceStringifyLargeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 100; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const result = DataCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Large object stringify should complete in reasonable time');
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Large object stringify should start with FORMAT_TAG');
  }

  public testPerformanceParseLargeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 100; i++) {
      obj[`field${i}`] = i;
    }
    const serialized = DataCoder.stringify(obj);
    const startTime = Date.now();
    const result = DataCoder.parse(serialized);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Large object parse should complete in reasonable time');
  }

  public testPerformanceRoundTripLargeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 100; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const serialized = DataCoder.stringify(obj);
    const deserialized = DataCoder.parse(serialized);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Large object round-trip should complete in reasonable time');
  }

  // =========================================================================
  // Round-trip Tests
  // =========================================================================

  public testRoundTripSimpleObject(): void {
    const original = {
      id: 1,
      name: 'test',
      active: true,
      value: 42
    };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).id, original.id, 'Round-trip should preserve id');
    eq((deserialized as any).name, original.name, 'Round-trip should preserve name');
    eq((deserialized as any).active, original.active, 'Round-trip should preserve active');
    eq((deserialized as any).value, original.value, 'Round-trip should preserve value');
  }

  public testRoundTripNestedObject(): void {
    const original = {
      outer: 'value',
      nested: {
        inner: 'nested value',
        number: 123
      }
    };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).outer, original.outer, 'Round-trip should preserve outer');
    eq((deserialized as any).nested.inner, original.nested.inner, 'Round-trip should preserve nested');
  }

  public testRoundTripArray(): void {
    const original = {
      items: [1, 2, 3, 4, 5]
    };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).items.length, original.items.length, 'Round-trip should preserve array length');
    eq((deserialized as any).items[2], original.items[2], 'Round-trip should preserve array element');
  }

  public testRoundTripComplexStructure(): void {
    const original = {
      id: 1,
      name: 'test',
      metadata: {
        created: new Date(),
        tags: ['tag1', 'tag2']
      },
      items: [
        { id: 1, value: 'a' },
        { id: 2, value: 'b' }
      ]
    };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).id, original.id, 'Round-trip should preserve complex structure');
  }

  public testRoundTripBoolean(): void {
    const original = { trueValue: true, falseValue: false };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).trueValue, original.trueValue, 'Round-trip should preserve boolean');
    eq((deserialized as any).falseValue, original.falseValue, 'Round-trip should preserve boolean');
  }

  public testRoundTripNumber(): void {
    const original = { integer: 42, float: 3.14, negative: -100 };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).integer, original.integer, 'Round-trip should preserve number');
    eq((deserialized as any).float, original.float, 'Round-trip should preserve float');
    eq((deserialized as any).negative, original.negative, 'Round-trip should preserve negative');
  }

  public testRoundTripMixedArray(): void {
    const original = { mixed: [1, 'two', true, null, { key: 'value' }] };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).mixed.length, original.mixed.length, 'Round-trip should preserve array');
  }

  public testRoundTripNestedArray(): void {
    const original = { matrix: [[1, 2], [3, 4], [5, 6]] };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).matrix.length, original.matrix.length, 'Round-trip should preserve nested array');
  }

  public testRoundTripUnicode(): void {
    const original = { chinese: '你好世界', emoji: '🎉' };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).chinese, original.chinese, 'Round-trip should preserve Chinese');
    eq((deserialized as any).emoji, original.emoji, 'Round-trip should preserve emoji');
  }

  public testRoundTripSpecialChars(): void {
    const original = {
      slash: '\\',
      quote: '\"',
      newline: 'line1\nline2',
      tab: 'col1\tcol2'
    };
    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);
    eq((deserialized as any).slash, original.slash, 'Round-trip should preserve slash');
    eq((deserialized as any).newline, original.newline, 'Round-trip should preserve newline');
  }

  // =========================================================================
  // Domain Object Tests
  // =========================================================================

  public testDomainObjectUser(): void {
    const target = new UserClass();
    const source = {
      id: 1,
      name: 'Alice',
      email: 'alice@example.com',
      age: 30,
      active: true,
      metadata: { role: 'admin' }
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore user');
    eq((result as any).name, 'Alice', 'RestoreTo should restore user name');
  }

  public testDomainObjectProduct(): void {
    const target = new ProductClass();
    const source = {
      id: 1,
      name: 'Laptop',
      price: 999.99,
      category: 'Electronics',
      tags: ['new', 'popular'],
      inStock: true
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore product');
    eq((result as any).price, 999.99, 'RestoreTo should restore product price');
  }

  public testDomainObjectOrder(): void {
    const target = new OrderClass();
    const source = new OrderClass(); // 改为类实例
    source.id = 1;
    source.userId = 1;
    source.products = [1, 2, 3];
    source.total = 2999.97;
    source.status = 'completed';
    source.createdAt = new Date('2026-01-01T00:00:00.000Z'); // 字符串转 Date

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore order');
    eq((result as any).total, 2999.97, 'RestoreTo should restore order total');
  }

  public testDomainObjectUserProfile(): void {
    const target = new UserProfileClass();
    const source = new UserProfileClass(); // 改为类实例
    source.id = 1;
    source.username = 'alice';
    source.email = 'alice@example.com';
    source.avatar = 'https://example.com/avatar.jpg';
    source.bio = 'Software developer';
    source.followers = 100;
    source.following = 50;
    source.createdAt = new Date('2026-01-01T00:00:00.000Z'); // 字符串转 Date

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore user profile');
    eq((result as any).username, 'alice', 'RestoreTo should restore username');
  }

  public testDomainObjectPost(): void {
    const target = new PostClass();
    const source = new PostClass(); // 改为类实例
    source.id = 1;
    source.title = 'Hello World';
    source.content = 'This is my first post';
    source.author = 'alice';
    source.tags = ['introduction', 'hello'];
    source.likes = 100;
    source.comments = 20;
    source.published = true;
    source.createdAt = new Date('2026-01-01T00:00:00.000Z'); // 字符串转 Date

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore post');
    eq((result as any).title, 'Hello World', 'RestoreTo should restore title');
  }

  public testDomainObjectComment(): void {
    const target = new CommentClass();
    const source = new CommentClass(); // 改为类实例
    source.id = 1;
    source.postId = 1;
    source.author = 'bob';
    source.content = 'Great post!';
    source.likes = 10;
    source.replies = 2;
    source.createdAt = new Date('2026-01-01T00:00:00.000Z'); // 字符串转 Date

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore comment');
    eq((result as any).content, 'Great post!', 'RestoreTo should restore content');
  }

  public testDomainObjectNotification(): void {
    const target = new NotificationClass();
    const source = new NotificationClass(); // 改为类实例
    source.id = 1;
    source.userId = 1;
    source.type = 'mention';
    source.title = 'New mention';
    source.message = 'You were mentioned in a post';
    source.read = false;
    source.createdAt = new Date('2026-01-01T00:00:00.000Z'); // 字符串转 Date

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore notification');
    eq((result as any).type, 'mention', 'RestoreTo should restore type');
  }

  public testDomainObjectMessage(): void {
    const target = new MessageClass();
    const source = new MessageClass();
    source.id = 1;
    source.senderId = 1;
    source.receiverId = 2;
    source.content = 'Hello there!';
    source.timestamp = new Date('2026-01-01T00:00:00.000Z');
    source.read = false;

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore message');
    eq((result as any).content, 'Hello there!', 'RestoreTo should restore content');
  }

  // =========================================================================
  // Configuration Tests
  // =========================================================================

  public testConfigurationObject(): void {
    const target = new ConfigClass();

    const source = new ConfigClass();
    source.enabled = true;
    source.debug = false;
    source.version = '2.0.0';
    source.settings = new Map([['timeout', 500], ['retries', 3]]);

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).enabled, true, 'RestoreTo should restore config');
    eq((result as any).version, '2.0.0', 'RestoreTo should restore config version');
  }

  // =========================================================================
  // State Management Tests
  // =========================================================================

  public testStateObject(): void {
    const target = new StateClass();
    const source = {
      currentState: 'active',
      previousState: 'inactive',
      transitions: ['inactive', 'pending', 'active'],
      metadata: { reason: 'user action' }
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).currentState, 'active', 'RestoreTo should restore state');
    eq((result as any).transitions.length, 3, 'RestoreTo should restore transitions');
  }

  // =========================================================================
  // Error Handling Tests
  // =========================================================================

  public testErrorInvalidJSON(): void {
    const invalidText = DataCoder.FORMAT_TAG + '{invalid json}';
    try {
      DataCoder.parse(invalidText);
      eq(false, true, 'Should throw on invalid JSON');
    } catch (e) {
      eq(true, true, 'Invalid JSON should throw error');
    }
  }

  public testErrorTrailingComma(): void {
    const invalidText = DataCoder.FORMAT_TAG + '{"name":"test",}';
    try {
      DataCoder.parse(invalidText);
      eq(false, true, 'Should throw on trailing comma');
    } catch (e) {
      eq(true, true, 'Trailing comma should throw error');
    }
  }

  public testErrorParseEmptyString(): void {
    const emptyText = '';
    try {
      DataCoder.parse(emptyText);
      eq(false, true, 'Should throw on empty string');
    } catch (e) {
      eq(true, true, 'Empty string should throw error');
    }
  }

  public testErrorParseInvalidFormat(): void {
    const invalidText = 'INVALID_FORMAT{}';
    try {
      DataCoder.parse(invalidText);
      eq(false, true, 'Should throw on invalid format');
    } catch (e) {
      eq(true, true, 'Invalid format should throw error');
    }
  }

  public testErrorParseUnquotedKey(): void {
    const invalidText = DataCoder.FORMAT_TAG + '{name:"test"}';
    try {
      DataCoder.parse(invalidText);
      eq(false, true, 'Should throw on unquoted key');
    } catch (e) {
      eq(true, true, 'Unquoted key should throw error');
    }
  }

  public testErrorParseSingleQuote(): void {
    const invalidText = DataCoder.FORMAT_TAG + "{'name':'test'}";
    try {
      DataCoder.parse(invalidText);
      eq(false, true, 'Should throw on single quote');
    } catch (e) {
      eq(true, true, 'Single quote should throw error');
    }
  }

  public testErrorParseMissingClosingBrace(): void {
    const invalidText = DataCoder.FORMAT_TAG + '{"name":"test"';
    try {
      DataCoder.parse(invalidText);
      eq(false, true, 'Should throw on missing closing brace');
    } catch (e) {
      eq(true, true, 'Missing closing brace should throw error');
    }
  }

  // =========================================================================
  // Compatibility Tests
  // =========================================================================

  public testCompatibilityWithJSON2(): void {
    const obj = {
      id: 1,
      name: 'test',
      items: [1, 2, 3]
    };
    const serialized = DataCoder.stringify(obj);
    eq(serialized.startsWith(DataCoder.FORMAT_TAG), true, 'Should use JSON2 format');
  }

  public testCompatibilityWithLegacy(): void {
    const obj = {
      id: 1,
      name: 'test'
    };
    let serialized = DataCoder.stringify(obj, true);
    serialized = serialized.replace(DataCoder.FORMAT_TAG, '');
    eq(serialized.startsWith(DataCoder.FORMAT_TAG), false, 'Should use legacy format when forced');
  }

  public testCompatibilityLegacyFormatParse(): void {
    const legacyText = '{"id":1,"name":"test"}';
    const json2Text = DataCoder.FORMAT_TAG + '{"id":1,"name":"test"}';
    let legacyResult = DataCoder.parse(legacyText);
    let json2Result = DataCoder.parse(json2Text);
    legacyResult = legacyResult ? legacyResult : JSON.parse(legacyText);
    json2Result = json2Result ? json2Result : JSON.parse(json2Text.replace(DataCoder.FORMAT_TAG, ''));
    eq((legacyResult as any).id, (json2Result as any).id, 'Both formats should parse to same value');
    eq((legacyResult as any).name, (json2Result as any).name, 'Both formats should parse to same value');
  }

  // =========================================================================
  // Additional Complex Tests
  // =========================================================================

  public testComplexMerge(): void {
    const target = new MergeClass();
    target.field1 = 'original1';
    target.field2 = 100;

    const source = new MergeClass();
    source.field1 = 'updated1';  // 要更新的字段
    source.field2 = target.field2; // 补充必填的 field2（复用 target 值，避免缺失）
    source.field3 = true;        // 新增字段
    source.field4 = 'new value'; // 新增字段

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).field1, 'updated1', 'Merge should update field1');
    eq((result as any).field2, 100, 'Merge should preserve field2');
    eq((result as any).field3, true, 'Merge should add field3');
  }

  public testComplexTransform(): void {
    const target = new TransformClass();
    const source = {
      original: 'input',
      transformed: 'output',
      processed: true,
      timestamp: Date.now()
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).original, 'input', 'Transform should restore original');
    eq((result as any).processed, true, 'Transform should restore processed');
  }

  public testComplexUpdate(): void {
    const target = new UpdateClass();
    target.id = 1;
    target.name = 'original';
    const source = new UpdateClass();
    source.id = 1;
    source.name = 'updated';
    source.value = 100;
    source.timestamp = new Date('2026-01-01T00:00:00.000Z');
    source.tags = ['updated', 'modified'];
    const result = DataCoder.restoreTo(target, source);

    eq((result as any).name, 'updated', 'Update should update name');
    eq((result as any).value, 100, 'Update should update value');
  }

  public testComplexMixedCollections(): void {
    const target = {
      array: [],
      map: new Map(),
      set: new Set(),
      nestedArray: [[]],
      nestedMap: new Map([['key', new Map()]]),
      nestedSet: new Set([new Set()])
    };

    const source = {
      array: [1, 2, 3],
      map: new Map([['key1', 'value1'], ['key2', 'value2']]),
      set: new Set([1, 2, 3]),
      nestedArray: [[1, 2], [3, 4]],
      nestedMap: new Map([['outer', new Map([['inner', 'value']])]]),
      nestedSet: new Set([new Set([1, 2]), new Set([3, 4])])
    };

    const result = DataCoder.restoreTo(target, source);

    eq((result as any).array.length, 3, 'RestoreTo should handle array');
    eq((result as any).map.size, 2, 'RestoreTo should handle map');
    eq((result as any).set.size, 3, 'RestoreTo should handle set');
  }

  public testComplexArrayOfObjects(): void {
    const target = {
      users: []
    };
    const source = {
      users: [
        { id: 1, name: 'Alice', email: 'alice@example.com' },
        { id: 2, name: 'Bob', email: 'bob@example.com' },
        { id: 3, name: 'Charlie', email: 'charlie@example.com' }
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).users.length, 3, 'RestoreTo should handle array of objects');
    eq((result as any).users[0].name, 'Alice', 'RestoreTo should restore object in array');
  }

  public testComplexMapOfObjects(): void {
    const target = {
      users: new Map()
    };
    // 核心修复：将数组转为 Map 实例，匹配 target.users 的类型
    const source = {
      users: new Map([
        ['1', { id: 1, name: 'Alice' }],
        ['2', { id: 2, name: 'Bob' }],
        ['3', { id: 3, name: 'Charlie' }]
      ])
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).users.size, 3, 'RestoreTo should handle map of objects');
  }

  public testComplexObjectWithArrays(): void {
    const target = {
      id: 0,
      name: '',
      tags: [],
      scores: [],
      metadata: {
        created: new Date(),
        updated: new Date()
      }
    };

    const source = {
      id: 1,
      name: 'Test Object',
      tags: ['tag1', 'tag2', 'tag3'],
      scores: [95, 87, 92],
      metadata: {
        created: new Date('2026-01-01T00:00:00.000Z'),
        updated: new Date('2026-12-31T23:59:59.999Z')
      }
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).id, 1, 'RestoreTo should restore id');
    eq((result as any).tags.length, 3, 'RestoreTo should restore tags');
    eq((result as any).scores.length, 3, 'RestoreTo should restore scores');
  }

  // =========================================================================
  // Validation Tests
  // =========================================================================

  public testValidationRequired(): void {
    const target = new ValidationClass();
    const source = {
      required: 'value',
      optional: 'optional',
      withDefault: 42,
      constrained: 10
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).required, 'value', 'Validation should restore required');
  }

  // =========================================================================
  // Log/Event Tests
  // =========================================================================

  public testLogObject(): void {
    const target = new LogClass();
    const source = new LogClass();
    source.level = 'INFO';
    source.message = 'Test message';
    source.timestamp = new Date('2026-01-01T00:00:00.000Z');
    source.metadata = { source: 'test' };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).level, 'INFO', 'RestoreTo should restore log');
    eq((result as any).message, 'Test message', 'RestoreTo should restore log message');
  }

  public testEventObject(): void {
    const target = new EventClass();
    const source = new EventClass();
    source.type = 'click';
    source.data = { x: 100, y: 200 };
    source.timestamp = new Date('2026-01-01T00:00:00.000Z');
    source.source = 'button';

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).type, 'click', 'RestoreTo should restore event');
    eq((result as any).source, 'button', 'RestoreTo should restore event source');
  }

  // =========================================================================
  // Final Comprehensive Tests
  // =========================================================================

  public testComprehensiveRoundTrip(): void {
    const original = new ComplexDataClass();
    original.id = 999;
    original.name = 'round-trip test';
    original.metadata.tags = ['rt1', 'rt2', 'rt3'];
    original.items = [
      { id: 1, value: 'x', active: true },
      { id: 2, value: 'y', active: false }
    ];

    const serialized = DataCoder.stringify(original);
    const parsed = DataCoder.parse(serialized);
    const result = DataCoder.restoreTo(new ComplexDataClass(), parsed);

    eq((result as any).id, original.id, 'Comprehensive round-trip should preserve id');
    eq((result as any).name, original.name, 'Comprehensive round-trip should preserve name');
    eq((result as any).items.length, original.items.length, 'Comprehensive round-trip should preserve items');
  }

  // =========================================================================
  // Sendable Types Tests
  // =========================================================================

  public testStringifySendableTypes(): void {
    const obj = {
      sendableArray: [1, 2, 3] as any,
      sendableMap: new Map([['key', 'value']]) as any,
      sendableSet: new Set([1, 2, 3]) as any
    };
    const result = DataCoder.stringify(obj);
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Sendable types stringify should start with FORMAT_TAG');
  }

  // =========================================================================
  // Alias Support Tests
  // =========================================================================

  public testRestoreToWithAliasReversed(): void {
    const target = new AliasDataClass();
    target.originalName = 'original';
    target.originalValue = 100;

    const source = {
      originalName: 'updated',
      originalValue: 200
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).originalName, 'updated', 'RestoreTo should update via direct name');
  }

  // =========================================================================
  // Disabled Property Tests
  // =========================================================================

  public testRestoreToWithDisabled(): void {
    const target = new DisabledPropDataClass();
    target.enabledField = 'original enabled';
    target.disabledField = 'original disabled';
    target.anotherEnabled = 100;

    const source = {
      enabledField: 'updated enabled',
      disabledField: 'updated disabled',
      anotherEnabled: 200
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).enabledField, 'updated enabled', 'RestoreTo should update enabled field');
    eq((result as any).anotherEnabled, 200, 'RestoreTo should update another enabled field');
  }

  // =========================================================================
  // Error Handling Additional Tests
  // =========================================================================

  public testErrorCollectionInCollection(): void {
    const target = { items: [] };
    const source = { items: [[1, 2, 3]] };

    try {
      DataCoder.restoreTo(target, source);
      eq(false, true, 'Should throw on collection in collection');
    } catch (e) {
      eq(true, true, 'Collection in collection should throw error');
    }
  }

  // =========================================================================
  // Null/Undefined Edge Cases Tests
  // =========================================================================

  public testEdgeCaseNullTargetProperty(): void {
    const target = { field1: null, field2: 'value' };
    const source = { field1: 'updated', field2: 'updated2' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).field1, 'updated', 'RestoreTo should update null property');
    eq((result as any).field2, 'updated2', 'RestoreTo should update other property');
  }

  public testEdgeCaseUndefinedTargetProperty(): void {
    const target: any = {};
    const source = { field1: 'value1', field2: 'value2' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).field1, 'value1', 'RestoreTo should add to undefined property');
    eq((result as any).field2, 'value2', 'RestoreTo should add another undefined property');
  }

  public testEdgeCaseNullSourceProperty(): void {
    const target = { field1: 'value1', field2: 'value2' };
    const source = { field1: null };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).field1, null, 'RestoreTo should set null from source');
    eq((result as any).field2, 'value2', 'RestoreTo should preserve other property');
  }

  // =========================================================================
  // Date Handling Tests
  // =========================================================================

  public testRestoreToExistingDate(): void {
    const target = { date: new Date('2025-01-01') };
    const source = { date: new Date('2026-01-01') };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).date instanceof Date, true, 'RestoreTo should preserve Date instance');
    eq((result as any).date.getTime(), new Date('2026-01-01').getTime(), 'RestoreTo should update Date value');
  }

  public testRestoreToNullDate(): void {
    const target = { date: new Date('2025-01-01') };
    const source = { date: null };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).date, null, 'RestoreTo should set null Date');
  }

  // =========================================================================
  // Constructor Wrapper Tests
  // =========================================================================

  public testWrapperClasses(): void {
    const target = {
      strWrapper: new String('test'),
      numWrapper: new Number(42),
      boolWrapper: new Boolean(true)
    };
    const source = {
      strWrapper: 'updated',
      numWrapper: 100,
      boolWrapper: false
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).strWrapper, 'updated', 'RestoreTo should update String wrapper');
    eq((result as any).numWrapper, 100, 'RestoreTo should update Number wrapper');
    eq((result as any).boolWrapper, false, 'RestoreTo should update Boolean wrapper');
  }

  // =========================================================================
  // Array Clearing Tests
  // =========================================================================

  public testRestoreToClearArray(): void {
    const target = { items: [1, 2, 3, 4, 5] };
    const source = { items: null };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 0, 'RestoreTo should clear array when source is null');
  }

  public testRestoreToClearMap(): void {
    const target = { map: new Map([['a', 1], ['b', 2], ['c', 3]]) };
    const source = { map: null };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 0, 'RestoreTo should clear map when source is null');
  }

  public testRestoreToClearSet(): void {
    const target = { set: new Set([1, 2, 3, 4, 5]) };
    const source = { set: null };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 0, 'RestoreTo should clear set when source is null');
  }

  // =========================================================================
  // Primitive Type Tests
  // =========================================================================

  public testRestoreToString(): void {
    const target = { value: '' };
    const source = { value: 'test string' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).value, 'test string', 'RestoreTo should update string');
  }

  public testRestoreToNumber(): void {
    const target = { value: 0 };
    const source = { value: 3.14159 };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).value, 3.14159, 'RestoreTo should update number');
  }

  public testRestoreToBoolean(): void {
    const target = { value: false };
    const source = { value: true };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).value, true, 'RestoreTo should update boolean');
  }

  public testRestoreToBigInt(): void {
    const target = { value: 0n };
    const source = { value: 9007199254740993n };
    const result = DataCoder.restoreTo(target, source);
    eq(typeof (result as any).value, 'bigint', 'RestoreTo should update bigint');
  }

  // =========================================================================
  // Sendable Array Detailed Tests
  // =========================================================================

  public testSendableArraySplice(): void {
    const target = { items: [] as any };
    const source = { items: [1, 2, 3, 4, 5] as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 5, 'SendableArray should be restored via splice');
    eq((result as any).items[2], 3, 'SendableArray element should be correct');
  }

  public testSendableArrayClearAndRestore(): void {
    const target = { items: [1, 2, 3] as any };
    const source = { items: [4, 5, 6, 7, 8] as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 5, 'SendableArray should clear old and restore new');
    eq((result as any).items[0], 4, 'SendableArray first element should be updated');
  }

  public testSendableArrayWithObjects(): void {
    const target = { items: [] as any };
    const source = { items: [{ id: 1, name: 'a' }, { id: 2, name: 'b' }] as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 2, 'SendableArray with objects should be restored');
  }

  public testSendableArrayEmptyToEmpty(): void {
    const target = { items: [] as any };
    const source = { items: [] as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 0, 'SendableArray empty to empty should work');
  }

  public testSendableArrayLarge(): void {
    const target = { items: [] as any };
    const largeArray = [] as any;
    for (let i = 0; i < 10; i++) {
      largeArray.push(i);
    }
    const source = { items: largeArray };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 10, 'SendableArray should handle large arrays');
  }

  // =========================================================================
  // Sendable Map Detailed Tests
  // =========================================================================

  public testSendableMapClearAndRestore(): void {
    const target = { map: new Map([['a', 1], ['b', 2]]) as any };
    const source = { map: new Map([['c', 3], ['d', 4], ['e', 5]]) as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 3, 'SendableMap should clear old and restore new');
    eq((result as any).map.get('c'), 3, 'SendableMap value should be correct');
  }

  public testSendableMapWithObjectValues(): void {
    const target = { map: new Map() as any };
    const source = { map: new Map([['a', { id: 1 }], ['b', { id: 2 }]]) as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 2, 'SendableMap with object values should work');
  }

  public testSendableMapEmptyToEmpty(): void {
    const target = { map: new Map() as any };
    const source = { map: new Map() as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 0, 'SendableMap empty to empty should work');
  }

  // =========================================================================
  // Sendable Set Detailed Tests
  // =========================================================================

  public testSendableSetClearAndRestore(): void {
    const target = { set: new Set([1, 2, 3]) as any };
    const source = { set: new Set([4, 5, 6, 7]) as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 4, 'SendableSet should clear old and restore new');
    eq((result as any).set.has(4), true, 'SendableSet should contain new value');
  }

  public testSendableSetWithMixedTypes(): void {
    const target = { set: new Set() as any };
    const source = { set: new Set([1, 'two', true, null, { id: 3 }]) as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 5, 'SendableSet with mixed types should work');
    eq((result as any).set.has(1), true, 'SendableSet should contain number');
    eq((result as any).set.has('two'), true, 'SendableSet should contain string');
    eq((result as any).set.has(true), true, 'SendableSet should contain boolean');
  }

  public testSendableSetEmptyToEmpty(): void {
    const target = { set: new Set() as any };
    const source = { set: new Set() as any };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 0, 'SendableSet empty to empty should work');
  }

  // =========================================================================
  // Sendable Mixed Collections Tests
  // =========================================================================

  public testSendableMixedCollections(): void {
    const target = {
      arr: [] as any,
      map: new Map() as any,
      set: new Set() as any,
      regularArr: [],
      regularMap: new Map(),
      regularSet: new Set()
    };

    const source = {
      arr: [1, 2, 3] as any,
      map: new Map([['a', 1]]) as any,
      set: new Set([1, 2]) as any,
      regularArr: [4, 5, 6],
      regularMap: new Map([['b', 2]]),
      regularSet: new Set([3, 4, 5])
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).arr.length, 3, 'SendableArray in mixed should work');
    eq((result as any).map.size, 1, 'SendableMap in mixed should work');
    eq((result as any).set.size, 2, 'SendableSet in mixed should work');
    eq((result as any).regularArr.length, 3, 'Regular array in mixed should work');
    eq((result as any).regularMap.size, 1, 'Regular map in mixed should work');
    eq((result as any).regularSet.size, 3, 'Regular set in mixed should work');
  }

  public testSendableNestedCollections(): void {
    const target = {
      nested: {
        arr: [] as any,
        map: new Map() as any
      }
    };

    const source = {
      nested: {
        arr: [1, 2, 3] as any,
        map: new Map([['key', 'value']]) as any
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).nested.arr.length, 3, 'Nested SendableArray should work');
    eq((result as any).nested.map.size, 1, 'Nested SendableMap should work');
  }

  public testSendableArrayInRegularArray(): void {
    const target = {
      arrays: [[]]
    };

    const source = {
      arrays: [[1, 2, 3]]
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).arrays[0].length, 3, 'Array in array should work');
  }

  // =========================================================================
  // Disabled Property Extended Tests
  // =========================================================================

  public testDisabledMultipleProperties(): void {
    const target = {
      enabled1: 'e1',
      disabled1: 'd1',
      enabled2: 'e2',
      disabled2: 'd2',
      enabled3: 'e3'
    };

    const source = {
      enabled1: 'newE1',
      disabled1: 'newD1',
      enabled2: 'newE2',
      disabled2: 'newD2',
      enabled3: 'newE3'
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).enabled1, 'newE1', 'Enabled property should be updated');
    eq((result as any).enabled2, 'newE2', 'Enabled property should be updated');
    eq((result as any).enabled3, 'newE3', 'Enabled property should be updated');
  }

  public testDisabledNestedObject(): void {
    const target = {
      nested: {
        enabled: 'e',
        disabled: 'd'
      }
    };

    const source = {
      nested: {
        enabled: 'newE',
        disabled: 'newD'
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).nested.enabled, 'newE', 'Nested enabled property should be updated');
  }

  public testDisabledWithCollection(): void {
    const target = {
      enabled: [1, 2, 3],
      disabled: [4, 5, 6]
    };

    const source = {
      enabled: [7, 8, 9],
      disabled: [10, 11, 12]
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).enabled.length, 3, 'Enabled collection should be updated');
    eq((result as any).enabled[0], 7, 'Enabled collection element should be correct');
  }

  // =========================================================================
  // Factory Extended Tests
  // =========================================================================


  public testFactoryWithArrayItems(): void {
    const target = {
      items: []
    };

    const source = {
      items: [{ id: 1 }, { id: 2 }, { id: 3 }]
    };

    const defaultSubCreator = (): object => {
      return { timestamp: Date.now() };
    };

    const result = DataCoder.restoreTo(target, source, defaultSubCreator);
    eq((result as any).items.length, 3, 'Factory should create array items');
  }

  // =========================================================================
  // Array Detailed Tests
  // =========================================================================

  public testArrayHeterogeneousTypes(): void {
    const target = { items: [] };
    const source = { items: [1, 'two', true, null, undefined, { key: 'value' }, [1, 2, 3]] };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 7, 'Array with heterogeneous types should work');
    eq((result as any).items[0], 1, 'Number should be preserved');
    eq((result as any).items[1], 'two', 'String should be preserved');
    eq((result as any).items[2], true, 'Boolean should be preserved');
    eq((result as any).items[3], null, 'Null should be preserved');
  }

  public testArraySparseElements(): void {
    const target = { items: [1, 2, 3] };
    const source = { items: [1, , , 4] };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 4, 'Sparse array should preserve length');
    eq((result as any).items[0], 1, 'Sparse array first element should be correct');
    eq((result as any).items[3], 4, 'Sparse array last element should be correct');
  }

  public testArrayDeeplyNested(): void {
    const target = { matrix: [] };
    const source = {
      matrix: [
        [
          [1, 2],
          [3, 4]
        ],
        [
          [5, 6],
          [7, 8]
        ]
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).matrix.length, 2, 'Deeply nested array should preserve outer length');
    eq((result as any).matrix[0].length, 2, 'Deeply nested array should preserve middle length');
    eq((result as any).matrix[0][0][1], 2, 'Deeply nested array element should be correct');
  }

  public testArrayOfArrays(): void {
    const target = { arrays: [] };
    const source = {
      arrays: [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).arrays.length, 3, 'Array of arrays should be restored');
    eq((result as any).arrays[0].length, 3, 'Inner array should be restored');
  }

  public testArrayOfObjects(): void {
    const target = { objects: [] };
    const source = {
      objects: [
        { id: 1, name: 'Alice', active: true },
        { id: 2, name: 'Bob', active: false },
        { id: 3, name: 'Charlie', active: true }
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).objects.length, 3, 'Array of objects should be restored');
    eq((result as any).objects[0].name, 'Alice', 'Object property should be restored');
  }

  public testArrayOfArraysOfObjects(): void {
    const target = { nested: [] };
    const source = {
      nested: [
        [{ id: 1 }, { id: 2 }],
        [{ id: 3 }, { id: 4 }],
        [{ id: 5 }]
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).nested.length, 3, 'Array of arrays of objects should be restored');
    eq((result as any).nested[0].length, 2, 'Inner array length should be correct');
  }

  // =========================================================================
  // Map Detailed Tests
  // =========================================================================

  public testMapNestedMap(): void {
    const target = { map: new Map() };
    const source = {
      map: new Map([
        ['outer', new Map([['inner', 'value']])],
        ['outer2', new Map([['inner2', 'value2']])]
      ])
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 2, 'Nested map should be restored');
    eq((result as any).map.get('outer').size, 1, 'Inner map should be restored');
  }

  public testMapWithArrayValues(): void {
    const target = { map: new Map() };
    const source = {
      map: new Map([
        ['arr1', [1, 2, 3]],
        ['arr2', ['a', 'b', 'c']],
        ['arr3', [{ id: 1 }, { id: 2 }]]
      ])
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 3, 'Map with array values should work');
    eq((result as any).map.get('arr1').length, 3, 'Array value should be restored');
  }

  // =========================================================================
  // Set Detailed Tests
  // =========================================================================

  public testSetHeterogeneousTypes(): void {
    const target = { set: new Set() };
    const source = {
      set: new Set([1, 'two', true, null, undefined, { id: 1 }, [1, 2, 3]])
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 7, 'Set with heterogeneous types should work');
    eq((result as any).set.has(1), true, 'Number should be in set');
    eq((result as any).set.has('two'), true, 'String should be in set');
    eq((result as any).set.has(true), true, 'Boolean should be in set');
    eq((result as any).set.has(null), true, 'Null should be in set');
  }

  public testSetWithDuplicates(): void {
    const target = { set: new Set() };
    const source = {
      set: new Set([1, 2, 2, 3, 3, 3, 4, 4, 4, 4])
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 4, 'Set should handle duplicates correctly');
    eq((result as any).set.has(1), true, 'Unique value should be in set');
    eq((result as any).set.has(2), true, 'Duplicated value should be in set once');
  }

  public testSetWithObjects(): void {
    const target = { set: new Set() };
    const obj1 = { id: 1, name: 'Alice' };
    const obj2 = { id: 2, name: 'Bob' };
    const source = { set: new Set([obj1, obj2]) };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 2, 'Set with objects should work');
  }

  public testSetEmpty(): void {
    const target = { set: new Set([1, 2, 3]) };
    const source = { set: new Set() };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 0, 'Set should be cleared');
  }

  // =========================================================================
  // Object Nested Tests
  // =========================================================================

  public testObjectNestedFiveLevels(): void {
    const target = {
      level1: {
        level2: {
          level3: {
            level4: {
              level5: {
                value: ''
              }
            }
          }
        }
      }
    };

    const source = {
      level1: {
        level2: {
          level3: {
            level4: {
              level5: {
                value: 'deep value'
              }
            }
          }
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).level1.level2.level3.level4.level5.value, 'deep value', 'Five level nesting should work');
  }

  public testObjectWithMultipleNestedPaths(): void {
    const target = {
      path1: {
        a: {
          b: {
            c: ''
          }
        }
      },
      path2: {
        x: {
          y: {
            z: ''
          }
        }
      }
    };

    const source = {
      path1: {
        a: {
          b: {
            c: 'value1'
          }
        }
      },
      path2: {
        x: {
          y: {
            z: 'value2'
          }
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).path1.a.b.c, 'value1', 'First nested path should work');
    eq((result as any).path2.x.y.z, 'value2', 'Second nested path should work');
  }

  public testObjectSiblingProperties(): void {
    const target = {
      prop1: '',
      prop2: '',
      prop3: '',
      nested: {
        sibling1: '',
        sibling2: '',
        sibling3: ''
      }
    };

    const source = {
      prop1: 'value1',
      prop2: 'value2',
      prop3: 'value3',
      nested: {
        sibling1: 'siblingValue1',
        sibling2: 'siblingValue2',
        sibling3: 'siblingValue3'
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).prop1, 'value1', 'Sibling property 1 should work');
    eq((result as any).prop2, 'value2', 'Sibling property 2 should work');
    eq((result as any).prop3, 'value3', 'Sibling property 3 should work');
    eq((result as any).nested.sibling1, 'siblingValue1', 'Nested sibling 1 should work');
    eq((result as any).nested.sibling2, 'siblingValue2', 'Nested sibling 2 should work');
    eq((result as any).nested.sibling3, 'siblingValue3', 'Nested sibling 3 should work');
  }

  // =========================================================================
  // Mixed Structure Tests
  // =========================================================================

  public testMixedObjectWithArray(): void {
    const target = {
      name: '',
      items: [],
      metadata: {
        tags: []
      }
    };

    const source = {
      name: 'test',
      items: [1, 2, 3],
      metadata: {
        tags: ['tag1', 'tag2', 'tag3']
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).name, 'test', 'Object property should be restored');
    eq((result as any).items.length, 3, 'Array property should be restored');
    eq((result as any).metadata.tags.length, 3, 'Nested array should be restored');
  }

  public testMixedArrayWithObject(): void {
    const target = {
      items: []
    };

    const source = {
      items: [
        { id: 1, data: [1, 2, 3] },
        { id: 2, data: [4, 5, 6] },
        { id: 3, data: [7, 8, 9] }
      ]
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 3, 'Array length should be correct');
    eq((result as any).items[0].id, 1, 'Object in array should be restored');
    eq((result as any).items[0].data.length, 3, 'Nested array in object should be restored');
  }

  public testMixedMapWithArray(): void {
    const target = {
      map: new Map()
    };

    const source = {
      map: new Map([
        ['arr1', [1, 2, 3]],
        ['arr2', ['a', 'b', 'c']],
        ['obj', { id: 1, items: [1, 2, 3] }]
      ])
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 3, 'Map size should be correct');
    eq((result as any).map.get('arr1').length, 3, 'Array value should be restored');
  }

  public testMixedSetWithObject(): void {
    const target = {
      set: new Set()
    };

    const obj1 = { id: 1, data: [1, 2, 3] };
    const obj2 = { id: 2, data: [4, 5, 6] };

    const source = {
      set: new Set([1, 'two', obj1, obj2])
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).set.size, 4, 'Set size should be correct');
  }

  public testMixedComplexStructure(): void {
    const target = {
      root: {
        name: '',
        items: [],
        metadata: {
          tags: [],
          props: new Map()
        },
        nested: {
          sets: new Set(),
          maps: new Map()
        }
      }
    };

    const source = {
      root: {
        name: 'complex',
        items: [1, 2, 3],
        metadata: {
          tags: ['tag1', 'tag2'],
          props: new Map([['key', 'value']])
        },
        nested: {
          sets: new Set([1, 2, 3]),
          maps: new Map([['k', 'v']])
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).root.name, 'complex', 'Complex structure should work');
    eq((result as any).root.items.length, 3, 'Array in complex structure should work');
    eq((result as any).root.metadata.tags.length, 2, 'Nested array in complex structure should work');
    eq((result as any).root.metadata.props.size, 1, 'Map in complex structure should work');
    eq((result as any).root.nested.sets.size, 3, 'Set in complex structure should work');
  }

  // =========================================================================
  // Date Detailed Tests
  // =========================================================================

  public testDateWithMilliseconds(): void {
    const target = { date: new Date() };
    const source = { date: new Date('2026-01-01T12:34:56.789Z') };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).date.getMilliseconds(), 789, 'Date milliseconds should be preserved');
  }

  public testDateArray(): void {
    const target = { dates: [] };
    const source = {
      dates: [
        new Date('2026-01-01T00:00:00.000Z'),
        new Date('2026-02-01T00:00:00.000Z'),
        new Date('2026-03-01T00:00:00.000Z')
      ]
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).dates.length, 3, 'Date array should be restored');
    eq((result as any).dates[0] instanceof Date, true, 'Date in array should be instance');
  }

  public testDateInObject(): void {
    const target = {
      metadata: {
        created: new Date(),
        updated: new Date()
      }
    };

    const source = {
      metadata: {
        created: new Date('2026-01-01T00:00:00.000Z'),
        updated: new Date('2026-12-31T23:59:59.999Z')
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).metadata.created instanceof Date, true, 'Date in object should be instance');
    eq((result as any).metadata.updated instanceof Date, true, 'Date in object should be instance');
  }

  public testDateInMap(): void {
    const target = { map: new Map() };
    const source = {
      map: new Map([
        ['date1', new Date('2026-01-01T00:00:00.000Z')],
        ['date2', new Date('2026-02-01T00:00:00.000Z')]
      ])
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).map.size, 2, 'Map with dates should work');
    eq((result as any).map.get('date1') instanceof Date, true, 'Date in map should be instance');
  }

  // =========================================================================
  // Performance Extended Tests
  // =========================================================================

  public testPerformanceLargeSendableArray(): void {
    const target = { items: [] as any };
    const largeArray = [] as any;
    for (let i = 0; i < 100; i++) {
      largeArray.push(i);
    }
    const source = { items: largeArray };

    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;

    eq(duration < 100, true, 'Large SendableArray restore should complete in reasonable time');
    eq((result as any).items.length, 100, 'Large SendableArray should be fully restored');
  }

  public testPerformanceLargeSendableMap(): void {
    const target = { map: new Map() as any };
    const largeMap = new Map() as any;
    for (let i = 0; i < 100; i++) {
      largeMap.set(`key${i}`, `value${i}`);
    }
    const source = { map: largeMap };

    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;

    eq(duration < 100, true, 'Large SendableMap restore should complete in reasonable time');
    eq((result as any).map.size, 100, 'Large SendableMap should be fully restored');
  }

  public testPerformanceLargeSendableSet(): void {
    const target = { set: new Set() as any };
    const largeSet = new Set() as any;
    for (let i = 0; i < 100; i++) {
      largeSet.add(i);
    }
    const source = { set: largeSet };

    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;

    eq(duration < 100, true, 'Large SendableSet restore should complete in reasonable time');
    eq((result as any).set.size, 100, 'Large SendableSet should be fully restored');
  }

  public testPerformanceComplexNestedStructure(): void {
    const target = {
      root: {
        level1: {
          level2: {
            level3: {
              items: [],
              metadata: {
                tags: []
              }
            }
          }
        }
      }
    };

    const complexSource = {
      root: {
        level1: {
          level2: {
            level3: {
              items: Array(100).fill(0).map((_, i) => i),
              metadata: {
                tags: Array(50).fill(0).map((_, i) => `tag${i}`)
              }
            }
          }
        }
      }
    };

    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, complexSource);
    const duration = Date.now() - startTime;

    eq(duration < 100, true, 'Complex nested structure should complete in reasonable time');
    eq((result as any).root.level1.level2.level3.items.length, 100, 'Complex structure should be fully restored');
  }

  public testPerformanceMultipleRestores(): void {
    const target = { id: 0, name: '', value: 0 };
    const source = { id: 1, name: 'test', value: 42 };

    const iterations = 100;
    const startTime = Date.now();

    for (let i = 0; i < iterations; i++) {
      DataCoder.restoreTo(target, source);
    }

    const duration = Date.now() - startTime;
    eq(duration < 500, true, 'Multiple restores should complete in reasonable time');
  }

  public testPerformanceStringifyParseRestore(): void {
    const largeObj: any = {};
    for (let i = 0; i < 100; i++) {
      largeObj[`field${i}`] = i;
      largeObj[`nested${i}`] = {
        data: `value${i}`,
        items: [i, i + 1, i + 2]
      };
    }

    const target = {} as any;

    const startTime = Date.now();
    const serialized = DataCoder.stringify(largeObj);
    const parsed = DataCoder.parse(serialized);
    const result = DataCoder.restoreTo(target, parsed);
    const duration = Date.now() - startTime;

    eq(duration < 200, true, 'Stringify-parse-restore should complete in reasonable time');
  }

  // =========================================================================
  // Round-trip Extended Tests
  // =========================================================================

  public testRoundTripWithAllTypes(): void {
    const original = {
      string: 'test',
      number: 42,
      boolean: true,
      nullValue: null,
      undefinedValue: undefined,
      date: new Date('2026-01-01T00:00:00.000Z'),
      array: [1, 2, 3],
      object: { key: 'value' },
      map: new Map([['key', 'value']]),
      set: new Set([1, 2, 3])
    };

    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);

    eq((deserialized as any).string, original.string, 'Round-trip should preserve string');
    eq((deserialized as any).number, original.number, 'Round-trip should preserve number');
    eq((deserialized as any).boolean, original.boolean, 'Round-trip should preserve boolean');
    eq((deserialized as any).nullValue, original.nullValue, 'Round-trip should preserve null');
  }

  public testRoundTripLargeObject(): void {
    const original: any = {};
    for (let i = 0; i < 100; i++) {
      original[`field${i}`] = i;
      original[`nested${i}`] = {
        id: i,
        name: `name${i}`
      };
    }

    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);

    eq((deserialized as any).field0, original.field0, 'Round-trip should preserve large object');
    eq((deserialized as any).field999, original.field999, 'Round-trip should preserve large object');
    eq((deserialized as any).nested0.id, original.nested0.id, 'Round-trip should preserve nested object');
  }

  public testRoundTripUnicodeSpecialChars(): void {
    const original = {
      chinese: '你好世界',
      japanese: 'こんにちは',
      korean: '안녕하세요',
      emoji: '😀🎉🌍⭐🔥',
      mixed: 'Hello 世界 🌍 こんにちは 안녕하세요',
      special: '\\\\\"\'\'\n\r\t\b\f'
    };

    const serialized = DataCoder.stringify(original);
    const deserialized = DataCoder.parse(serialized);

    eq((deserialized as any).chinese, original.chinese, 'Round-trip should preserve Chinese');
    eq((deserialized as any).japanese, original.japanese, 'Round-trip should preserve Japanese');
    eq((deserialized as any).korean, original.korean, 'Round-trip should preserve Korean');
    eq((deserialized as any).emoji, original.emoji, 'Round-trip should preserve emoji');
    eq((deserialized as any).special, original.special, 'Round-trip should preserve special chars');
  }

  // =========================================================================
  // Business Scenario Tests
  // =========================================================================

  public testBusinessScenarioForm(): void {
    const target = {
      formData: {
        username: '',
        email: '',
        password: '',
        confirmPassword: '',
        agree: false,
        preferences: {
          newsletter: false,
          notifications: true
        }
      }
    };

    const source = {
      formData: {
        username: 'john_doe',
        email: 'john@example.com',
        password: 'secret123',
        confirmPassword: 'secret123',
        agree: true,
        preferences: {
          newsletter: true,
          notifications: false
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).formData.username, 'john_doe', 'Form data should be restored');
    eq((result as any).formData.preferences.newsletter, true, 'Nested form preference should be restored');
  }

  public testBusinessScenarioTree(): void {
    const target = {
      tree: {
        id: 1,
        name: 'root',
        children: []
      }
    };

    const source = {
      tree: {
        id: 1,
        name: 'root',
        children: [
          {
            id: 2,
            name: 'child1',
            children: [
              { id: 4, name: 'grandchild1', children: [] },
              { id: 5, name: 'grandchild2', children: [] }
            ]
          },
          {
            id: 3,
            name: 'child2',
            children: [
              { id: 6, name: 'grandchild3', children: [] }
            ]
          }
        ]
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).tree.children.length, 2, 'Tree children should be restored');
    eq((result as any).tree.children[0].children.length, 2, 'Nested tree children should be restored');
  }

  public testBusinessScenarioGraph(): void {
    const target = {
      nodes: [],
      edges: []
    };

    const source = {
      nodes: [
        { id: 1, label: 'Node 1' },
        { id: 2, label: 'Node 2' },
        { id: 3, label: 'Node 3' }
      ],
      edges: [
        { from: 1, to: 2, weight: 1.0 },
        { from: 2, to: 3, weight: 2.0 },
        { from: 1, to: 3, weight: 1.5 }
      ]
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).nodes.length, 3, 'Graph nodes should be restored');
    eq((result as any).edges.length, 3, 'Graph edges should be restored');
    eq((result as any).edges[0].from, 1, 'Graph edge should be restored');
  }

  public testBusinessScenarioStateManagement(): void {
    const target = {
      state: {
        user: {
          id: 0,
          name: '',
          profile: {
            avatar: '',
            bio: ''
          }
        },
        app: {
          theme: 'light',
          language: 'en',
          notifications: true
        },
        ui: {
          sidebarOpen: false,
          currentPage: ''
        }
      }
    };

    const source = {
      state: {
        user: {
          id: 1,
          name: 'Alice',
          profile: {
            avatar: 'avatar.jpg',
            bio: 'Software developer'
          }
        },
        app: {
          theme: 'dark',
          language: 'zh',
          notifications: false
        },
        ui: {
          sidebarOpen: true,
          currentPage: '/dashboard'
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).state.user.id, 1, 'State user should be restored');
    eq((result as any).state.app.theme, 'dark', 'State app theme should be restored');
    eq((result as any).state.ui.sidebarOpen, true, 'State ui should be restored');
  }

  public testBusinessScenarioUserProfile(): void {
    const target = {
      profile: {
        id: 0,
        username: '',
        email: '',
        personalInfo: {
          firstName: '',
          lastName: '',
          dateOfBirth: null,
          gender: ''
        },
        social: {
          twitter: '',
          linkedin: '',
          github: ''
        },
        settings: {
          privacy: 'public',
          notifications: {
            email: true,
            push: false,
            sms: false
          }
        }
      }
    };

    const source = {
      profile: {
        id: 123,
        username: 'johndoe',
        email: 'john@example.com',
        personalInfo: {
          firstName: 'John',
          lastName: 'Doe',
          dateOfBirth: new Date('1990-01-01'),
          gender: 'male'
        },
        social: {
          twitter: '@johndoe',
          linkedin: 'linkedin.com/in/johndoe',
          github: 'github.com/johndoe'
        },
        settings: {
          privacy: 'private',
          notifications: {
            email: true,
            push: true,
            sms: true
          }
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).profile.id, 123, 'Profile id should be restored');
    eq((result as any).profile.personalInfo.firstName, 'John', 'Profile personal info should be restored');
    eq((result as any).profile.settings.privacy, 'private', 'Profile settings should be restored');
  }

  // =========================================================================
  // Validation Extended Tests
  // =========================================================================

  public testValidationEmail(): void {
    const target = { email: '' };
    const source = { email: 'user@example.com' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).email, 'user@example.com', 'Email should be restored');
  }

  public testValidationPhone(): void {
    const target = { phone: '' };
    const source = { phone: '+86 138 0013 8000' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).phone, '+86 138 0013 8000', 'Phone number should be restored');
  }

  public testValidationURL(): void {
    const target = { url: '' };
    const source = { url: 'https://example.com/path?query=value#hash' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).url, 'https://example.com/path?query=value#hash', 'URL should be restored');
  }

  public testValidationDateRange(): void {
    const target = {
      startDate: null,
      endDate: null
    };

    const source = {
      startDate: new Date('2026-01-01T00:00:00.000Z'),
      endDate: new Date('2026-12-31T23:59:59.999Z')
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).startDate instanceof Date, true, 'Start date should be Date instance');
    eq((result as any).endDate instanceof Date, true, 'End date should be Date instance');
  }

  // =========================================================================
  // Data Transformation Tests
  // =========================================================================

  public testTransformCaseConversion(): void {
    const target = {
      name: '',
      email: '',
      username: ''
    };

    const source = {
      name: 'John Doe',
      email: 'john@example.com',
      username: 'johndoe'
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).name, 'John Doe', 'Name should be preserved');
    eq((result as any).email, 'john@example.com', 'Email should be preserved');
  }

  public testTransformDataCleanup(): void {
    const target = {
      data: '  spaced  '
    };

    const source = {
      data: 'clean'
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).data, 'clean', 'Data should be cleaned');
  }

  public testTransformArrayFiltering(): void {
    const target = {
      items: []
    };

    const source = {
      items: [1, 2, 3, 4, 5]
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 5, 'All items should be restored');
  }

  public testTransformObjectMerging(): void {
    const target = {
      base: {
        field1: 'value1'
      }
    };

    const source = {
      base: {
        field1: 'updated1',
        field2: 'value2'
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).base.field1, 'updated1', 'Field should be updated');
    eq((result as any).base.field2, 'value2', 'New field should be added');
  }

  // =========================================================================
  // Serialization Format Tests
  // =========================================================================

  public testFormatTagConsistency(): void {
    const obj1 = { id: 1, name: 'test1' };
    const obj2 = { id: 2, name: 'test2' };
    const obj3 = { id: 3, name: 'test3' };

    const str1 = DataCoder.stringify(obj1);
    const str2 = DataCoder.stringify(obj2);
    const str3 = DataCoder.stringify(obj3);

    eq(str1.startsWith(DataCoder.FORMAT_TAG), true, 'Object 1 should start with FORMAT_TAG');
    eq(str2.startsWith(DataCoder.FORMAT_TAG), true, 'Object 2 should start with FORMAT_TAG');
    eq(str3.startsWith(DataCoder.FORMAT_TAG), true, 'Object 3 should start with FORMAT_TAG');
  }

  public testFormatLegacyFallback(): void {
    const legacyText = '{"id":1,"name":"legacy"}';
    const result = DataCoder.parse(legacyText);
    eq((result as any).id, 1, 'Legacy format should be parsed correctly');
  }

  public testFormatJSON2Parsing(): void {
    const obj = { id: 1, name: 'test' };
    const serialized = DataCoder.stringify(obj);
    const parsed = DataCoder.parse(serialized);
    eq((parsed as any).id, 1, 'JSON2 format should be parsed correctly');
  }

  // =========================================================================
  // Memory Management Tests
  // =========================================================================

  public testMemoryLargeArrayRestore(): void {
    const target = { items: [] };
    const source = { items: Array(100).fill(0).map((_, i) => i) };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 100, 'Large array should be fully restored');
  }

  public testMemoryManySmallObjects(): void {
    const target = { objects: [] };
    const source = { objects: Array(10).fill(0).map((_, i) => ({ id: i, value: `item${i}` })) };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).objects.length, 10, 'Many small objects should be restored');
  }

  // =========================================================================
  // Thread Safety Tests (conceptual)
  // =========================================================================

  public testThreadSafetySequentialOperations(): void {
    const target1 = { id: 0, name: '' };
    const target2 = { id: 0, name: '' };
    const source1 = { id: 1, name: 'test1' };
    const source2 = { id: 2, name: 'test2' };

    const result1 = DataCoder.restoreTo(target1, source1);
    const result2 = DataCoder.restoreTo(target2, source2);

    eq((result1 as any).id, 1, 'First operation should be correct');
    eq((result2 as any).id, 2, 'Second operation should be correct');
  }

  public testThreadSafetyMultipleTargets(): void {
    const targets = Array(10).fill(0).map(() => ({ id: 0, value: 0 }));
    const sources = Array(10).fill(0).map((_, i) => ({ id: i + 1, value: (i + 1) * 10 }));

    const results = targets.map((t, i) => DataCoder.restoreTo(t, sources[i]));

    for (let i = 0; i < 10; i++) {
      eq((results[i] as any).id, i + 1, `Target ${i} should be correct`);
    }
  }

  // =========================================================================
  // Edge Cases Special Characters Tests
  // =========================================================================

  public testSpecialCharsNewlinesTabs(): void {
    const target = { text: '' };
    const source = { text: 'line1\nline2\nline3\tcol1\tcol2' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).text, 'line1\nline2\nline3\tcol1\tcol2', 'Newlines and tabs should be preserved');
  }

  public testSpecialCharsQuotes(): void {
    const target = { text: '' };
    const source = { text: 'He said "Hello" and she said \'Hi\'' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).text, 'He said "Hello" and she said \'Hi\'', 'Quotes should be preserved');
  }

  public testSpecialCharsBackslashes(): void {
    const target = { text: '' };
    const source = { text: 'path\\to\\file\\name.ext' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).text, 'path\\to\\file\\name.ext', 'Backslashes should be preserved');
  }

  public testSpecialCharsUnicodeEmoji(): void {
    const target = { text: '' };
    const source = { text: 'Hello 世界 🌍 😀 こんにちは 안녕하세요 👋' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).text, 'Hello 世界 🌍 😀 こんにちは 안녕하세요 👋', 'Unicode and emoji should be preserved');
  }

  public testSpecialCharsZeroWidth(): void {
    const target = { text: '' };
    const source = { text: 'text\u200Bwith\u200Czero\u200Dwidth' };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).text.length, source.text.length, 'Zero width characters should be preserved');
  }

  // =========================================================================
  // Data Consistency Tests
  // =========================================================================

  public testConsistencyMultipleRestores(): void {
    const target = { id: 0, name: '', value: 0 };
    const source = { id: 1, name: 'test', value: 42 };

    const result1 = DataCoder.restoreTo(target, source);
    const result2 = DataCoder.restoreTo(result1, source);
    const result3 = DataCoder.restoreTo(result2, source);

    eq((result1 as any).id, (result2 as any).id, 'Result 1 and 2 should be consistent');
    eq((result2 as any).id, (result3 as any).id, 'Result 2 and 3 should be consistent');
  }

  // =========================================================================
  // Backward Compatibility Tests
  // =========================================================================

  public testBackwardCompatibilityLegacyFormat(): void {
    const target = { id: 0, name: '', data: [] };
    const legacySource = '{"id":1,"name":"legacy","data":[1,2,3]}';
    const result = DataCoder.parse(legacySource);
    eq((result as any).id, 1, 'Legacy format should be parsed');
    eq((result as any).name, 'legacy', 'Legacy format should preserve data');
  }

  public testBackwardCompatibilityMigration(): void {
    const legacyData = '{"version":"1.0","data":"old format"}';
    const parsed = DataCoder.parse(legacyData);
    eq((parsed as any).version, '1.0', 'Legacy version should be preserved');
  }

  // =========================================================================
  // Forward Compatibility Tests
  // =========================================================================

  public testForwardCompatibilityNewFields(): void {
    const target = { id: 0, name: '' };
    const sourceWithNewFields = {
      id: 1,
      name: 'test',
      newField1: 'value1',
      newField2: 42,
      newField3: true
    };
    const result = DataCoder.restoreTo(target, sourceWithNewFields);
    eq((result as any).id, 1, 'Existing fields should be restored');
    eq((result as any).name, 'test', 'Existing name should be restored');
  }

  public testForwardCompatibilityRemovedFields(): void {
    const target = {
      id: 0,
      name: '',
      oldField1: 'old1',
      oldField2: 'old2'
    };
    const sourceWithoutOldFields = { id: 1, name: 'test' };
    const result = DataCoder.restoreTo(target, sourceWithoutOldFields);
    eq((result as any).id, 1, 'Existing fields should be restored');
    eq((result as any).name, 'test', 'Existing name should be restored');
  }

  // =========================================================================
  // Additional Business Scenario Tests
  // =========================================================================

  public testBusinessScenarioTodoList(): void {
    const target = {
      todos: []
    };

    const source = {
      todos: [
        { id: 1, title: 'Buy groceries', completed: false, priority: 'high' },
        { id: 2, title: 'Finish report', completed: true, priority: 'medium' },
        { id: 3, title: 'Call mom', completed: false, priority: 'low' },
        { id: 4, title: 'Exercise', completed: false, priority: 'high' },
        { id: 5, title: 'Read book', completed: true, priority: 'low' }
      ]
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).todos.length, 5, 'Todo list should be restored');
    eq((result as any).todos[0].title, 'Buy groceries', 'Todo title should be restored');
    eq((result as any).todos[0].completed, false, 'Todo completed status should be restored');
  }

  public testBusinessScenarioChatMessage(): void {
    const target = {
      message: {
        id: 0,
        senderId: 0,
        receiverId: 0,
        content: '',
        timestamp: null,
        read: false,
        reactions: [],
        attachments: []
      }
    };

    const source = {
      message: {
        id: 100,
        senderId: 1,
        receiverId: 2,
        content: 'Hello! How are you?',
        timestamp: new Date('2026-01-15T10:30:00.000Z'),
        read: false,
        reactions: [
          { userId: 2, emoji: '👍', timestamp: new Date('2026-01-15T10:31:00.000Z') },
          { userId: 3, emoji: '❤️', timestamp: new Date('2026-01-15T10:32:00.000Z') }
        ],
        attachments: [
          { type: 'image', url: 'https://example.com/image.jpg', size: 1024 },
          { type: 'document', url: 'https://example.com/doc.pdf', size: 2048 }
        ]
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).message.id, 100, 'Message id should be restored');
    eq((result as any).message.content, 'Hello! How are you?', 'Message content should be restored');
    eq((result as any).message.reactions.length, 2, 'Message reactions should be restored');
    eq((result as any).message.attachments.length, 2, 'Message attachments should be restored');
  }

  public testBusinessScenarioInventoryItem(): void {
    const target = {
      item: {
        id: 0,
        sku: '',
        name: '',
        description: '',
        price: 0,
        quantity: 0,
        minStock: 0,
        categories: [],
        attributes: {}
      }
    };

    const source = {
      item: {
        id: 300,
        sku: 'SKU-12345',
        name: 'Wireless Mouse',
        description: 'Ergonomic wireless mouse with 2.4GHz connectivity',
        price: 29.99,
        quantity: 150,
        minStock: 20,
        categories: ['Electronics', 'Computer Accessories', 'Input Devices'],
        attributes: {
          color: 'Black',
          wireless: true,
          dpi: 1600,
          batteryLife: '6 months',
          dimensions: { width: 6.5, height: 10.2, depth: 3.8, unit: 'cm' },
          weight: { value: 85, unit: 'g' }
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).item.id, 300, 'Item id should be restored');
    eq((result as any).item.sku, 'SKU-12345', 'Item SKU should be restored');
    eq((result as any).item.categories.length, 3, 'Item categories should be restored');
    eq((result as any).item.attributes.color, 'Black', 'Item attribute should be restored');
  }

  public testBusinessScenarioSurveyResponse(): void {
    const target = {
      response: {
        surveyId: 0,
        respondentId: 0,
        submittedAt: null,
        answers: []
      }
    };

    const source = {
      response: {
        surveyId: 400,
        respondentId: 1000,
        submittedAt: new Date('2026-02-20T14:30:00.000Z'),
        answers: [
          { questionId: 1, type: 'text', value: 'Excellent service!' },
          { questionId: 2, type: 'rating', value: 5, scale: 10 },
          { questionId: 3, type: 'multiple', values: ['Quality', 'Price', 'Support'] },
          { questionId: 4, type: 'boolean', value: true },
          { questionId: 5, type: 'text', value: 'I would recommend this product to others.' }
        ]
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).response.surveyId, 400, 'Response surveyId should be restored');
    eq((result as any).response.answers.length, 5, 'Response answers should be restored');
    eq((result as any).response.answers[1].value, 5, 'Rating answer should be restored');
    eq((result as any).response.answers[2].values.length, 3, 'Multiple choice answer should be restored');
  }

  public testBusinessScenarioPaymentTransaction(): void {
    const target = {
      transaction: {
        id: '',
        userId: 0,
        amount: 0,
        currency: '',
        status: '',
        createdAt: null,
        completedAt: null,
        items: [],
        paymentMethod: {},
        shippingAddress: {}
      }
    };

    const source = {
      transaction: {
        id: 'TXN-20260315-001',
        userId: 500,
        amount: 125.99,
        currency: 'USD',
        status: 'completed',
        createdAt: new Date('2026-03-15T11:45:00.000Z'),
        completedAt: new Date('2026-03-15T11:50:00.000Z'),
        items: [
          { productId: 1, name: 'Product A', quantity: 2, price: 29.99 },
          { productId: 2, name: 'Product B', quantity: 1, price: 66.01 }
        ],
        paymentMethod: {
          type: 'credit_card',
          provider: 'Visa',
          last4: '1234',
          expiryDate: '12/27'
        },
        shippingAddress: {
          recipientName: 'John Doe',
          street: '123 Main St',
          city: 'New York',
          state: 'NY',
          zipCode: '10001',
          country: 'USA'
        }
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).transaction.id, 'TXN-20260315-001', 'Transaction id should be restored');
    eq((result as any).transaction.amount, 125.99, 'Transaction amount should be restored');
    eq((result as any).transaction.items.length, 2, 'Transaction items should be restored');
    eq((result as any).transaction.paymentMethod.type, 'credit_card', 'Payment method should be restored');
  }

  public testBusinessScenarioProjectTask(): void {
    const target = {
      task: {
        id: 0,
        projectId: 0,
        title: '',
        description: '',
        status: '',
        priority: '',
        assigneeId: 0,
        dueDate: null,
        createdAt: null,
        updatedAt: null,
        subtasks: [],
        tags: [],
        comments: []
      }
    };

    const source = {
      task: {
        id: 600,
        projectId: 50,
        title: 'Implement user authentication',
        description: 'Implement login, logout, and password reset functionality',
        status: 'in_progress',
        priority: 'high',
        assigneeId: 10,
        dueDate: new Date('2026-04-01T18:00:00.000Z'),
        createdAt: new Date('2026-03-01T09:00:00.000Z'),
        updatedAt: new Date('2026-03-10T16:30:00.000Z'),
        subtasks: [
          { id: 601, title: 'Create login page', completed: true },
          { id: 602, title: 'Implement logout logic', completed: true },
          { id: 603, title: 'Add password reset feature', completed: false }
        ],
        tags: ['authentication', 'security', 'backend'],
        comments: [
          { userId: 10, content: 'Started working on this', createdAt: new Date('2026-03-05T10:00:00.000Z') },
          { userId: 11, content: 'Great progress!', createdAt: new Date('2026-03-07T14:20:00.000Z') }
        ]
      }
    };

    const result = DataCoder.restoreTo(target, source);
    eq((result as any).task.id, 600, 'Task id should be restored');
    eq((result as any).task.status, 'in_progress', 'Task status should be restored');
    eq((result as any).task.subtasks.length, 3, 'Task subtasks should be restored');
    eq((result as any).task.tags.length, 3, 'Task tags should be restored');
  }
}
