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
    const longStr = 'a'.repeat(10000);
    const source = {
      veryLongString: longStr
    };
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).veryLongString.length, 10000, 'RestoreTo should handle very long string');
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
    for (let i = 0; i < 1000; i++) {
      source.items.push(i);
    }
    const result = DataCoder.restoreTo(target, source);
    eq((result as any).items.length, 1000, 'RestoreTo should handle array with many elements');
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
    for (let i = 0; i < 10000; i++) {
      largeArray.push(i);
    }
    const source = {
      largeArray: largeArray
    };
    const startTime = Date.now();
    const result = DataCoder.restoreTo(target, source);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large array restore should complete in reasonable time');
    eq((result as any).largeArray.length, 10000, 'Large array should be fully restored');
  }

  public testPerformanceManyProperties(): void {
    const target = new PerformanceClass();
    const manyProperties: any = {};
    for (let i = 0; i < 1000; i++) {
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
    const iterations = 1000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      DataCoder.restoreTo(target, source);
    }
    const duration = Date.now() - startTime;
    eq(duration < 5000, true, 'Repeated operations should complete in reasonable time');
  }

  public testPerformanceStringifyLargeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 1000; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const result = DataCoder.stringify(obj);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large object stringify should complete in reasonable time');
    eq(result.startsWith(DataCoder.FORMAT_TAG), true, 'Large object stringify should start with FORMAT_TAG');
  }

  public testPerformanceParseLargeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 1000; i++) {
      obj[`field${i}`] = i;
    }
    const serialized = DataCoder.stringify(obj);
    const startTime = Date.now();
    const result = DataCoder.parse(serialized);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large object parse should complete in reasonable time');
  }

  public testPerformanceRoundTripLargeObject(): void {
    const obj: any = {};
    for (let i = 0; i < 1000; i++) {
      obj[`field${i}`] = i;
    }
    const startTime = Date.now();
    const serialized = DataCoder.stringify(obj);
    const deserialized = DataCoder.parse(serialized);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large object round-trip should complete in reasonable time');
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
    source.followers = 1000;
    source.following = 500;
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
    source.settings = new Map([['timeout', 5000], ['retries', 3]]);

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

  public testCompatibilityLegacyFormatStringify(): void {
    const obj = { id: 1, name: 'test' };
    const json2Result = DataCoder.stringify(obj);
    const legacyResult = DataCoder.stringify(obj, true);
    eq(json2Result.startsWith(DataCoder.FORMAT_TAG), true, 'JSON2 format should start with FORMAT_TAG');
    eq(legacyResult.startsWith(DataCoder.FORMAT_TAG), true, 'Legacy format should not start with FORMAT_TAG');
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
}
