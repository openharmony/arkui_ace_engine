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

import { eq, neq, ITestFile } from '../lib/testRunner'

declare class Utils {
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
  static currentAppApiVersion: number;
}

declare interface IStorage {
  get<T>(key: string): T | undefined;
  set<T>(key: string, val: T): void;
  has(key: string): boolean;
  delete(key: string): void;
  clear(): void;
}

declare class AppStorage {
  static link<T>(propName: string, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> | undefined;
  static setAndLink<T>(propName: string, defaultValue: T, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
}

declare interface IPropertySubscriber {
  id__?: number;
}

declare class SubscribedAbstractProperty<T> {
  get(): T;
  set(value: T): void;
  aboutToBeDeleted(): void;
}

declare class PersistentStorage {
  static configureBackend(storage: IStorage): void;
  static persistProp<T>(key: string, defaultValue: T): void;
  static PersistProp<T>(key: string, defaultValue: T): void;
  static deleteProp(key: string): void;
  static DeleteProp(key: string): void;
  static persistProps(properties: { key: string, defaultValue: any }[]): void;
  static PersistProps(properties: { key: string, defaultValue: any }[]): void;
  static keys(): Array<string>;
  static Keys(): Array<string>;
  static notifyHasChanged(propName: string): void;
  static NotifyHasChanged(propName: string): void;
  static aboutToBeDeleted(): void;
}

declare enum ObjectVersion {
  NewVersion,
  CompatibleVersion,
  Default,
}

declare class MapInfo<K, V> {
  static readonly replacer: string;
  static readonly replacerCompatible: string;
  public keys: K[];
  public values: V[];
  constructor(mapReplacer: string, keyToValue: { key: K, value: V }[]);
  static isObject<K, V>(obj: unknown): ObjectVersion;
  static toObject<K, V>(map: Map<K, V>): MapInfo<K, V>;
  static toMap<K, V>(obj: MapInfo<K, V>): Map<K, V>;
  static toMapCompatible<K, V>(obj: MapInfo<K, V>): Map<K, V>;
}

declare class SetInfo<V> {
  static readonly replacer: string;
  static readonly replacerCompatible: string;
  constructor(setReplacer: string, values: V[]);
  static isObject<V>(obj: unknown): obj is SetInfo<V>;
  static toObject<V>(set: Set<V>): SetInfo<V>;
  static toSet<V>(obj: SetInfo<V>): Set<V>;
}

declare class DateInfo {
  static readonly replacer: string;
  static readonly replacerCompatible: string;
  constructor(dateReplacer: string, date: string);
  static isObject(obj: unknown): obj is DateInfo;
  static toObject(date: Date): DateInfo;
  static toDate(obj: DateInfo): Date;
}

class MockStorage implements IStorage {
  private storage: Map<string, Object> = new Map();

  get<T>(key: string): T | undefined {
    return this.storage.get(key) as T;
  }

  set<T>(key: string, val: T): void {
    this.storage.set(key, val as Object);
  }

  has(key: string): boolean {
    return this.storage.has(key);
  }

  delete(key: string): void {
    this.storage.delete(key);
  }

  clear(): void {
    this.storage.clear();
  }

  size(): number {
    return this.storage.size;
  }
}

export class PersistentStorageTestsV1 implements ITestFile {
  private idString: string = "";
  private static mockStorage: MockStorage = new MockStorage();

  constructor(str: string) {
    console.log(`Creating PersistentStorageTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    PersistentStorage.configureBackend(PersistentStorageTestsV1.mockStorage);
  }

  public beforeEach(): void {
    PersistentStorageTestsV1.mockStorage.clear();
    PersistentStorage.aboutToBeDeleted();
  }

  public afterAll(): void {
    PersistentStorage.aboutToBeDeleted();
  }

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1: MapInfo Helper Class Tests
  // =========================================================================

  public testMapInfoToObject(): void {
    const map = new Map<string, number>();
    map.set('key1', 1);
    map.set('key2', 2);
    map.set('key3', 3);

    const mapInfo = MapInfo.toObject(map);

    eq(mapInfo !== undefined, true, "MapInfo.toObject returns MapInfo");
  }

  public testMapInfoToMap(): void {
    const map = new Map<string, number>();
    map.set('a', 10);
    map.set('b', 20);

    const mapInfo = MapInfo.toObject(map);
    const restoredMap = MapInfo.toMap(mapInfo);

    eq(restoredMap.size, 2, "Restored Map has correct size");
    eq(restoredMap.get('a'), 10, "Restored Map has correct value for 'a'");
    eq(restoredMap.get('b'), 20, "Restored Map has correct value for 'b'");
  }

  public testMapInfoEmptyMap(): void {
    const emptyMap = new Map<string, string>();
    const mapInfo = MapInfo.toObject(emptyMap);
    const restoredMap = MapInfo.toMap(mapInfo);

    eq(restoredMap.size, 0, "Empty Map is preserved");
  }

  // =========================================================================
  // SECTION 2: SetInfo Helper Class Tests
  // =========================================================================

  public testSetInfoToObject(): void {
    const set = new Set<string>();
    set.add('value1');
    set.add('value2');
    set.add('value3');

    const setInfo = SetInfo.toObject(set);

    eq(setInfo !== undefined, true, "SetInfo.toObject returns SetInfo");
  }

  public testSetInfoToSet(): void {
    const set = new Set<number>();
    set.add(100);
    set.add(200);
    set.add(300);

    const setInfo = SetInfo.toObject(set);
    const restoredSet = SetInfo.toSet(setInfo);

    eq(restoredSet.size, 3, "Restored Set has correct size");
    eq(restoredSet.has(100), true, "Restored Set contains 100");
    eq(restoredSet.has(200), true, "Restored Set contains 200");
    eq(restoredSet.has(300), true, "Restored Set contains 300");
  }

  public testSetInfoEmptySet(): void {
    const emptySet = new Set<string>();
    const setInfo = SetInfo.toObject(emptySet);
    const restoredSet = SetInfo.toSet(setInfo);

    eq(restoredSet.size, 0, "Empty Set is preserved");
  }

  // =========================================================================
  // SECTION 3: DateInfo Helper Class Tests
  // =========================================================================

  public testDateInfoToObject(): void {
    const date = new Date('2023-01-01T00:00:00.000Z');
    const dateInfo = DateInfo.toObject(date);

    eq(dateInfo !== undefined, true, "DateInfo.toObject returns DateInfo");
  }

  public testDateInfoToDate(): void {
    const originalDate = new Date('2024-06-15T12:30:45.000Z');
    const dateInfo = DateInfo.toObject(originalDate);
    const restoredDate = DateInfo.toDate(dateInfo);

    eq(restoredDate instanceof Date, true, "Restored value is a Date");
    eq(restoredDate.toISOString(), '2024-06-15T12:30:45.000Z', "Restored Date has correct value");
  }

  public testDateInfoCurrentDate(): void {
    const now = new Date();
    const dateInfo = DateInfo.toObject(now);
    const restoredDate = DateInfo.toDate(dateInfo);

    eq(restoredDate instanceof Date, true, "Current Date is preserved");
  }

  // =========================================================================
  // SECTION 4: Basic PersistentStorage Tests
  // =========================================================================

  public testPersistPropString(): void {
    PersistentStorage.persistProp('stringProp', 'defaultValue');

    const keys = PersistentStorage.keys();
    eq(keys.includes('stringProp'), true, "Property 'stringProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('stringProp'), true, "Value is written to storage");
  }

  public testPersistPropNumber(): void {
    PersistentStorage.persistProp('numberProp', 42);

    const keys = PersistentStorage.keys();
    eq(keys.includes('numberProp'), true, "Property 'numberProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('numberProp'), true, "Number value is written to storage");
  }

  public testPersistPropBoolean(): void {
    PersistentStorage.persistProp('boolProp', true);

    const keys = PersistentStorage.keys();
    eq(keys.includes('boolProp'), true, "Property 'boolProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('boolProp'), true, "Boolean value is written to storage");
  }

  public testPersistPropObject(): void {
    const obj = { name: 'test', value: 123 };
    PersistentStorage.persistProp('objProp', obj);

    const keys = PersistentStorage.keys();
    eq(keys.includes('objProp'), true, "Property 'objProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('objProp'), true, "Object value is written to storage");
  }

  public testPersistPropArray(): void {
    const arr = [1, 2, 3, 4, 5];
    PersistentStorage.persistProp('arrProp', arr);

    const keys = PersistentStorage.keys();
    eq(keys.includes('arrProp'), true, "Property 'arrProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('arrProp'), true, "Array value is written to storage");
  }

  // =========================================================================
  // SECTION 5: Complex Type Tests (Map, Set, Date)
  // =========================================================================

  public testPersistPropMap(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    map.set('b', 2);

    PersistentStorage.persistProp('mapProp', map);

    const keys = PersistentStorage.keys();
    eq(keys.includes('mapProp'), true, "Property 'mapProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('mapProp'), true, "Map value is written to storage");
  }

  public testPersistPropSet(): void {
    const set = new Set<string>();
    set.add('x');
    set.add('y');
    set.add('z');

    PersistentStorage.persistProp('setProp', set);

    const keys = PersistentStorage.keys();
    eq(keys.includes('setProp'), true, "Property 'setProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('setProp'), true, "Set value is written to storage");
  }

  public testPersistPropDate(): void {
    const date = new Date('2023-12-25T00:00:00.000Z');
    PersistentStorage.persistProp('dateProp', date);

    const keys = PersistentStorage.keys();
    eq(keys.includes('dateProp'), true, "Property 'dateProp' is persisted");
    eq(PersistentStorageTestsV1.mockStorage.has('dateProp'), true, "Date value is written to storage");
  }

  // =========================================================================
  // SECTION 6: Property Management Tests
  // =========================================================================

  public testPersistPropsMultiple(): void {
    const properties = [
      { key: 'prop1', defaultValue: 'value1' },
      { key: 'prop2', defaultValue: 42 },
      { key: 'prop3', defaultValue: true }
    ];

    PersistentStorage.persistProps(properties);

    const keys = PersistentStorage.keys();
    eq(keys.includes('prop1'), true, "Property 'prop1' is persisted");
    eq(keys.includes('prop2'), true, "Property 'prop2' is persisted");
    eq(keys.includes('prop3'), true, "Property 'prop3' is persisted");
    eq(keys.length, 3, "All 3 properties are persisted");
  }

  public testKeys(): void {
    PersistentStorage.persistProp('key1', 'value1');
    PersistentStorage.persistProp('key2', 'value2');
    PersistentStorage.persistProp('key3', 'value3');

    const keys = PersistentStorage.keys();
    eq(keys.length, 3, "keys() returns 3 keys");
    eq(keys.includes('key1'), true, "keys() contains 'key1'");
    eq(keys.includes('key2'), true, "keys() contains 'key2'");
    eq(keys.includes('key3'), true, "keys() contains 'key3'");
  }

  public testKeysEmpty(): void {
    const keys = PersistentStorage.keys();
    eq(Array.isArray(keys), true, "keys() returns array");
    eq(keys.length, 0, "keys() returns empty array when no properties persisted");
  }

  // =========================================================================
  // SECTION 7: Deprecated API Tests
  // =========================================================================

  public testPersistPropDeprecated(): void {
    PersistentStorage.PersistProp('deprecatedProp', 'value');

    const keys = PersistentStorage.keys();
    eq(keys.includes('deprecatedProp'), true, "PersistProp (deprecated) works");
  }

  public testPersistPropsDeprecated(): void {
    const properties = [
      { key: 'depProp1', defaultValue: 1 },
      { key: 'depProp2', defaultValue: 2 }
    ];

    PersistentStorage.PersistProps(properties);

    const keys = PersistentStorage.keys();
    eq(keys.includes('depProp1'), true, "PersistProps (deprecated) works for prop1");
    eq(keys.includes('depProp2'), true, "PersistProps (deprecated) works for prop2");
  }

  public testKeysDeprecated(): void {
    PersistentStorage.persistProp('testKey', 'testValue');

    const keys = PersistentStorage.Keys();
    eq(keys.includes('testKey'), true, "Keys (deprecated) works");
  }

  // =========================================================================
  // SECTION 8: Edge Cases
  // =========================================================================

  public testPersistPropEmptyString(): void {
    PersistentStorage.persistProp('emptyString', '');

    const keys = PersistentStorage.keys();
    eq(keys.includes('emptyString'), true, "Empty string is persisted");
  }

  public testPersistPropZero(): void {
    PersistentStorage.persistProp('zeroValue', 0);

    const keys = PersistentStorage.keys();
    eq(keys.includes('zeroValue'), true, "Zero value is persisted");
  }

  public testPersistPropFalse(): void {
    PersistentStorage.persistProp('falseValue', false);

    const keys = PersistentStorage.keys();
    eq(keys.includes('falseValue'), true, "False value is persisted");
  }

  public testPersistPropNullUndefined(): void {
    const apiVer = Utils.getApiVersion();

    if (apiVer >= 12) {
      PersistentStorage.persistProp('nullValue', null);
      PersistentStorage.persistProp('undefinedValue', undefined);

      const keys = PersistentStorage.keys();
      eq(keys.includes('nullValue'), true, "Null value is persisted in API 12+");
      eq(keys.includes('undefinedValue'), true, "Undefined value is persisted in API 12+");
    }
  }
}
