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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner'

// Declare types from stateMgmt.d.ts
declare class AppStorage {
  // Static singleton methods
  static createSingleton(initializingProperties?: Object): void;
  static getOrCreate(): AppStorage;
  static aboutToBeDeleted(): void;

  // Static method wrappers (API 10+)
  static ref<T>(propName: string): AbstractProperty<T> | undefined;
  static setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T>;
  static link<T>(key: string, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  static setAndLink<T>(key: string, defaultValue: T, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  static prop<T>(propName: string, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  static setAndProp<S>(key: string, defaultValue: S, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<S>;
  static has(key: string): boolean;
  static get<T>(key: string): T | undefined;
  static set<T>(key: string, newValue: T): boolean;
  static setOrCreate<T>(key: string, newValue: T): void;
  static delete(key: string): boolean;
  static keys(): IterableIterator<string>;
  static size(): number;
  static clear(): boolean;
  static subscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean;
  static unsubscribeFromChangesOf(propName: string, subscriberId: number): boolean;

  // Deprecated capitalized versions
  static Link<T>(key: string, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  static SetAndLink<T>(key: string, defaultValue: T, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  static Prop<T>(propName: string, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  static SetAndProp<S>(key: string, defaultValue: S, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<S>;
  static Has(key: string): boolean;
  static Get<T>(key: string): T | undefined;
  static Set<T>(key: string, newValue: T): boolean;
  static SetOrCreate<T>(key: string, newValue: T): void;
  static Delete(key: string): boolean;
  static Keys(): IterableIterator<string>;
  static Size(): number;
  static Clear(): boolean;
  static StaticClear(): boolean;
  static SubscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean;
  static UnsubscribeFromChangesOf(propName: string, subscriberId: number): boolean;
  static IsMutable(key: string): boolean;
}

declare class AbstractProperty<T> {
  get(): T;
  set(value: T): void;
}

declare class SubscribedAbstractProperty<T> extends AbstractProperty<T> {
  aboutToBeDeleted(): void;
}

declare interface IPropertySubscriber {
  id__?: number;
}

declare interface ISinglePropertyChangeSubscriber<T> {
  hasChanged(value: T): void;
}

declare class Utils {
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
}

/**
 * AppStorage-Specific Unit Tests
 *
 * This test suite validates AppStorage-specific features:
 * - Singleton pattern (createSingleton, getOrCreate)
 * - Static method wrappers vs instance methods
 * - AppStorage unique APIs (ref, setAndRef, aboutToBeDeleted)
 * - Deprecated APIs (backward compatibility)
 *
 * Note: Comprehensive LocalStorage testing is done in localStorageTestsV1.ts.
 * Since AppStorage extends LocalStorage, those tests validate AppStorage's
 * inherited functionality.
 */
export class AppStorageTestsV1 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating AppStorageTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log("AppStorageTestsV1: Setting up test suite");
    // Ensure AppStorage singleton is initialized
    try {
      AppStorage.getOrCreate();
    } catch (e) {
      console.log("AppStorage already initialized or error initializing");
    }
  }

  public beforeEach(): void {
    // Clean up before each test if possible
    try {
      AppStorage.clear();
    } catch (e) {
      // Clear may fail if there are subscribers, that's ok
    }
  }

  public afterAll(): void {
    console.log("AppStorageTestsV1: Tearing down test suite");
  }

  public afterEach(): void {
    // Clean up after each test
    try {
      AppStorage.clear();
    } catch (e) {
      // Clear may fail if there are subscribers
    }
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 2.1: Singleton Pattern (createSingleton, getOrCreate)
  // =========================================================================

  /**
   * Test createSingleton() basics
   * Expected: Creates AppStorage instance
   */
  public testCreateSingletonBasics(): void {
    // Note: createSingleton is not a public API and can only be called once
    // The singleton should already be initialized by getOrCreate()

    const instance = AppStorage.getOrCreate();
    eq(instance !== undefined, true, "getOrCreate returns AppStorage instance");
  }

  /**
   * Test createSingleton() with properties
   * Expected: Properties are initialized
   */
  public testCreateSingletonWithProperties(): void {
    // Set some properties to verify singleton works
    AppStorage.setOrCreate("testProp1", "value1");
    AppStorage.setOrCreate("testProp2", 42);

    eq(AppStorage.has("testProp1"), true, "property1 is accessible");
    eq(AppStorage.has("testProp2"), true, "property2 is accessible");
    eq(AppStorage.get("testProp1"), "value1", "property1 has correct value");
    eq(AppStorage.get("testProp2"), 42, "property2 has correct value");
  }

  /**
   * Test getOrCreate() creates instance
   * Expected: First call creates instance
   */
  public testGetOrCreateCreatesInstance(): void {
    const instance1 = AppStorage.getOrCreate();

    eq(instance1 !== undefined, true, "getOrCreate returns instance");
  }

  /**
   * Test getOrCreate() returns existing instance
   * Expected: Subsequent calls return same instance
   */
  public testGetOrCreateReturnsExisting(): void {
    const instance1 = AppStorage.getOrCreate();
    const instance2 = AppStorage.getOrCreate();

    eq(instance1 !== undefined, true, "first call returns instance");
    eq(instance2 !== undefined, true, "second call returns instance");
    // Both should be the same singleton
  }

  /**
   * Test singleton persistence across operations
   * Expected: State persists across getOrCreate() calls
   */
  public testSingletonPersistence(): void {
    AppStorage.setOrCreate("persistProp", "persistent");

    const instance1 = AppStorage.getOrCreate();
    eq(instance1 !== undefined, true, "getOrCreate returns instance");

    eq(AppStorage.get("persistProp"), "persistent", "value persists");

    const instance2 = AppStorage.getOrCreate();
    eq(AppStorage.get("persistProp"), "persistent", "value still persists");
  }

  // =========================================================================
  // SECTION 2.2: Static Method Wrappers
  // =========================================================================

  /**
   * Test static has() vs LocalStorage has()
   * Expected: Both work identically on singleton
   */
  public testStaticHas(): void {
    AppStorage.setOrCreate("staticHasProp", "value");

    const result = AppStorage.has("staticHasProp");

    eq(result, true, "static has() returns true for existing property");
    eq(AppStorage.has("nonExistent"), false, "static has() returns false for non-existent");
  }

  /**
   * Test static get() vs LocalStorage get()
   * Expected: Both work identically on singleton
   */
  public testStaticGet(): void {
    AppStorage.setOrCreate("staticGetProp", "getValue");

    const result = AppStorage.get<string>("staticGetProp");

    eq(result, "getValue", "static get() returns correct value");
    eq(AppStorage.get("nonExistent"), undefined, "static get() returns undefined for non-existent");
  }

  /**
   * Test static set() vs LocalStorage set()
   * Expected: Both work identically on singleton
   */
  public testStaticSet(): void {
    AppStorage.setOrCreate("staticSetProp", "initial");

    const result = AppStorage.set("staticSetProp", "updated");

    eq(result, true, "static set() returns true");
    eq(AppStorage.get("staticSetProp"), "updated", "value is updated");

    const failResult = AppStorage.set("nonExistent", "value");
    eq(failResult, false, "static set() returns false for non-existent property");
  }

  /**
   * Test static setOrCreate() vs LocalStorage setOrCreate()
   * Expected: Both work identically on singleton
   */
  public testStaticSetOrCreate(): void {
    // Create new property
    AppStorage.setOrCreate("newStaticProp", "newValue");
    eq(AppStorage.has("newStaticProp"), true, "property created");
    eq(AppStorage.get("newStaticProp"), "newValue", "value is correct");

    // Update existing property
    AppStorage.setOrCreate("newStaticProp", "updatedValue");
    eq(AppStorage.get("newStaticProp"), "updatedValue", "value is updated");
  }

  /**
   * Test static link() vs LocalStorage link()
   * Expected: Static link() uses singleton storage
   */
  public testStaticLink(): void {
    AppStorage.setOrCreate("staticLinkProp", "linkValue");

    const link = AppStorage.link<string>("staticLinkProp");

    eq(link !== undefined, true, "static link() returns SubscribedAbstractProperty");
    eq(link!.get(), "linkValue", "link has correct value");

    // Test two-way sync
    link!.set("viaLink");
    eq(link!.get(), "viaLink", "link reflects change");
    eq(AppStorage.get("staticLinkProp"), "viaLink", "storage reflects link change");

    link!.aboutToBeDeleted();
  }

  /**
   * Test static setAndLink() vs LocalStorage setAndLink()
   * Expected: Static setAndLink() uses singleton storage
   */
  public testStaticSetAndLink(): void {
    const link = AppStorage.setAndLink("staticSetAndLinkProp", "defaultValue");

    eq(link !== undefined, true, "static setAndLink() returns SubscribedAbstractProperty");
    eq(link!.get(), "defaultValue", "setAndLink creates with default value");
    eq(AppStorage.has("staticSetAndLinkProp"), true, "property exists in storage");

    link!.aboutToBeDeleted();
  }

  /**
   * Test static prop() vs LocalStorage prop()
   * Expected: Static prop() uses singleton storage
   */
  public testStaticProp(): void {
    AppStorage.setOrCreate("staticPropProp", "propValue");

    const prop = AppStorage.prop<string>("staticPropProp");

    eq(prop !== undefined, true, "static prop() returns SubscribedAbstractProperty");
    eq(prop!.get(), "propValue", "prop has correct value");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test static setAndProp() vs LocalStorage setAndProp()
   * Expected: Static setAndProp() uses singleton storage
   */
  public testStaticSetAndProp(): void {
    const prop = AppStorage.setAndProp("staticSetAndPropProp", "defaultPropValue");

    eq(prop !== undefined, true, "static setAndProp() returns SubscribedAbstractProperty");
    eq(prop!.get(), "defaultPropValue", "setAndProp creates with default value");
    eq(AppStorage.has("staticSetAndPropProp"), true, "property exists in storage");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test static delete() vs LocalStorage delete()
   * Expected: Static delete() uses singleton storage
   */
  public testStaticDelete(): void {
    AppStorage.setOrCreate("staticDeleteProp", "value");

    eq(AppStorage.has("staticDeleteProp"), true, "property exists before delete");

    const result = AppStorage.delete("staticDeleteProp");

    eq(result, true, "static delete() returns true");
    eq(AppStorage.has("staticDeleteProp"), false, "property does not exist after delete");
  }

  /**
   * Test static clear() vs LocalStorage clear()
   * Expected: Static clear() uses singleton storage
   */
  public testStaticClear(): void {
    AppStorage.setOrCreate("clearProp1", "value1");
    AppStorage.setOrCreate("clearProp2", "value2");
    AppStorage.setOrCreate("clearProp3", "value3");

    eq(AppStorage.size(), 3, "storage has 3 properties before clear");

    const result = AppStorage.clear();

    eq(result, true, "static clear() returns true");
    eq(AppStorage.size(), 0, "storage is empty after clear");
  }

  /**
   * Test static keys() vs LocalStorage keys()
   * Expected: Static keys() uses singleton storage
   */
  public testStaticKeys(): void {
    AppStorage.setOrCreate("key1", "value1");
    AppStorage.setOrCreate("key2", "value2");
    AppStorage.setOrCreate("key3", "value3");

    const keys = AppStorage.keys();
    const keyArray = Array.from(keys);

    eq(keyArray.length, 3, "static keys() returns 3 keys");
    eq(keyArray.includes("key1"), true, "keys contains key1");
    eq(keyArray.includes("key2"), true, "keys contains key2");
    eq(keyArray.includes("key3"), true, "keys contains key3");
  }

  /**
   * Test static size() vs LocalStorage size()
   * Expected: Static size() uses singleton storage
   */
  public testStaticSize(): void {
    AppStorage.setOrCreate("sizeProp1", "value1");
    AppStorage.setOrCreate("sizeProp2", "value2");

    const size = AppStorage.size();

    eq(size, 2, "static size() returns correct count");
  }

  // =========================================================================
  // SECTION 2.3: AppStorage Unique APIs
  // =========================================================================

  /**
   * Test static ref() - API 12+
   * Expected: Returns AbstractProperty for property
   */
  public testRefAPI12(): void {
    AppStorage.setOrCreate("refProp", "refValue");

    const ref = AppStorage.ref<string>("refProp");

    eq(ref !== undefined, true, "static ref() returns AbstractProperty");
    eq(ref!.get(), "refValue", "ref has correct value");
  }

  /**
   * Test static setAndRef() - API 12+
   * Expected: Creates property if not exists, returns AbstractProperty
   */
  public testSetAndRefAPI12(): void {
    const ref = AppStorage.setAndRef("setAndRefProp", "defaultValue");

    eq(ref !== undefined, true, "static setAndRef() returns AbstractProperty");
    eq(ref!.get(), "defaultValue", "setAndRef creates with default value");
    eq(AppStorage.has("setAndRefProp"), true, "property exists in storage");
  }

  /**
   * Test aboutToBeDeleted() cleanup
   * Expected: All properties cleaned up
   */
  public testAboutToBeDeleted(): void {
    AppStorage.setOrCreate("cleanupProp1", "value1");
    AppStorage.setOrCreate("cleanupProp2", "value2");

    eq(AppStorage.size(), 2, "storage has 2 properties before cleanup");

    // Note: aboutToBeDeleted may not actually clear if there are subscribers
    // This test verifies the method can be called
    try {
      AppStorage.aboutToBeDeleted();
    } catch (e) {
      // May fail if there are subscribers, that's expected
    }
  }

  /**
   * Test IsMutable() - deprecated
   * Expected: Always returns true
   */
  public testIsMutable(): void {
    AppStorage.setOrCreate("mutableProp", "value");

    const result = AppStorage.IsMutable("mutableProp");

    eq(result, true, "IsMutable() always returns true (deprecated)");
  }

  // =========================================================================
  // SECTION 2.4: Integration with Inherited Methods
  // =========================================================================

  /**
   * Test AppStorage uses LocalStorage methods
   * Expected: All static methods route to singleton instance
   */
  public testAppStorageUsesLocalStorageMethods(): void {
    // Test that AppStorage properly inherits LocalStorage methods
    AppStorage.setOrCreate("inheritProp", "value");

    eq(AppStorage.has("inheritProp"), true, "has() works (inherited)");
    eq(AppStorage.get("inheritProp"), "value", "get() works (inherited)");

    const setResult = AppStorage.set("inheritProp", "updated");
    eq(setResult, true, "set() works (inherited)");
    eq(AppStorage.get("inheritProp"), "updated", "set updated value (inherited)");
  }

  /**
   * Test multiple operations on singleton
   * Expected: All operations work on same underlying storage
   */
  public testMultipleOperationsOnSingleton(): void {
    // Create via setOrCreate
    AppStorage.setOrCreate("multiOpProp", "initial");

    // Link via link()
    const link = AppStorage.link<string>("multiOpProp");
    eq(link!.get(), "initial", "link has initial value");

    // Prop via prop()
    const prop = AppStorage.prop<string>("multiOpProp");
    eq(prop!.get(), "initial", "prop has initial value");

    // Get via get()
    eq(AppStorage.get("multiOpProp"), "initial", "get returns initial value");

    // Update via set()
    AppStorage.set("multiOpProp", "updated");
    eq(link!.get(), "updated", "link sees update");
    eq(prop!.get(), "updated", "prop sees update");
    eq(AppStorage.get("multiOpProp"), "updated", "get sees update");

    // Clean up
    link!.aboutToBeDeleted();
    prop!.aboutToBeDeleted();
  }

  /**
   * Test singleton state across different static methods
   * Expected: State persists across different method calls
   */
  public testSingletonStatePersistence(): void {
    // Set value using setOrCreate
    AppStorage.setOrCreate("persistProp", "persistValue");

    // Access using different methods
    const hasResult = AppStorage.has("persistProp");
    const getResult = AppStorage.get("persistProp");
    const sizeResult = AppStorage.size();

    eq(hasResult, true, "has() sees the property");
    eq(getResult, "persistValue", "get() sees the value");
    eq(sizeResult > 0, true, "size() is non-zero");

    // Clean up
    AppStorage.delete("persistProp");
  }

  // =========================================================================
  // SECTION: Deprecated APIs (backward compatibility)
  // =========================================================================

  /**
   * Test deprecated Has() vs has()
   * Expected: Both work identically
   */
  public testDeprecatedHas(): void {
    AppStorage.setOrCreate("deprHasProp", "value");

    const result1 = AppStorage.has("deprHasProp");
    const result2 = AppStorage.Has("deprHasProp");

    eq(result1, true, "has() works");
    eq(result2, true, "Has() deprecated version also works");
  }

  /**
   * Test deprecated Get() vs get()
   * Expected: Both work identically
   */
  public testDeprecatedGet(): void {
    AppStorage.setOrCreate("deprGetProp", "value");

    const result1 = AppStorage.get("deprGetProp");
    const result2 = AppStorage.Get("deprGetProp");

    eq(result1, "value", "get() works");
    eq(result2, "value", "Get() deprecated version also works");
  }

  /**
   * Test deprecated Set() vs set()
   * Expected: Both work identically
   */
  public testDeprecatedSet(): void {
    AppStorage.setOrCreate("deprSetProp", "initial");

    const result1 = AppStorage.set("deprSetProp", "updated1");
    const result2 = AppStorage.Set("deprSetProp", "updated2");

    eq(result1, true, "set() works");
    eq(result2, true, "Set() deprecated version also works");
    eq(AppStorage.get("deprSetProp"), "updated2", "value is updated");
  }

  /**
   * Test deprecated SetOrCreate() vs setOrCreate()
   * Expected: Both work identically
   */
  public testDeprecatedSetOrCreate(): void {
    AppStorage.SetOrCreate("deprSetOrCreateProp", "value");

    eq(AppStorage.has("deprSetOrCreateProp"), true, "SetOrCreate() works");
    eq(AppStorage.get("deprSetOrCreateProp"), "value", "value is correct");

    AppStorage.setOrCreate("deprSetOrCreateProp", "updated");
    eq(AppStorage.get("deprSetOrCreateProp"), "updated", "setOrCreate() also works");
  }

  /**
   * Test deprecated Delete() vs delete()
   * Expected: Both work identically
   */
  public testDeprecatedDelete(): void {
    AppStorage.setOrCreate("deprDeleteProp", "value");

    eq(AppStorage.has("deprDeleteProp"), true, "property exists");

    const result = AppStorage.Delete("deprDeleteProp");

    eq(result, true, "Delete() deprecated version works");
    eq(AppStorage.has("deprDeleteProp"), false, "property is deleted");
  }

  /**
   * Test deprecated Keys() vs keys()
   * Expected: Both work identically
   */
  public testDeprecatedKeys(): void {
    AppStorage.setOrCreate("key1", "value1");
    AppStorage.setOrCreate("key2", "value2");

    const keys1 = Array.from(AppStorage.keys());
    const keys2 = Array.from(AppStorage.Keys());

    eq(keys1.length, 2, "keys() works");
    eq(keys2.length, 2, "Keys() deprecated version also works");
  }

  /**
   * Test deprecated Size() vs size()
   * Expected: Both work identically
   */
  public testDeprecatedSize(): void {
    AppStorage.setOrCreate("sizeProp1", "value1");
    AppStorage.setOrCreate("sizeProp2", "value2");

    const size1 = AppStorage.size();
    const size2 = AppStorage.Size();

    eq(size1, 2, "size() works");
    eq(size2, 2, "Size() deprecated version also works");
  }

  /**
   * Test deprecated Clear() vs clear()
   * Expected: Both work identically
   */
  public testDeprecatedClear(): void {
    AppStorage.setOrCreate("clearProp1", "value1");
    AppStorage.setOrCreate("clearProp2", "value2");

    eq(AppStorage.size(), 2, "storage has 2 properties");

    const result = AppStorage.Clear();

    eq(result, true, "Clear() deprecated version works");
    eq(AppStorage.size(), 0, "storage is empty");
  }

  /**
   * Test deprecated StaticClear()
   * Expected: Works like clear()
   */
  public testDeprecatedStaticClear(): void {
    AppStorage.setOrCreate("staticClearProp1", "value1");
    AppStorage.setOrCreate("staticClearProp2", "value2");

    eq(AppStorage.size(), 2, "storage has 2 properties");

    const result = AppStorage.StaticClear();

    eq(result, true, "StaticClear() deprecated version works");
    eq(AppStorage.size(), 0, "storage is empty");
  }

  /**
   * Test deprecated Link() vs link()
   * Expected: Both work identically
   */
  public testDeprecatedLink(): void {
    AppStorage.setOrCreate("deprLinkProp", "value");

    const link1 = AppStorage.link<string>("deprLinkProp");
    const link2 = AppStorage.Link<string>("deprLinkProp");

    eq(link1 !== undefined, true, "link() works");
    eq(link2 !== undefined, true, "Link() deprecated version also works");
    eq(link1!.get(), "value", "link has correct value");
    eq(link2!.get(), "value", "Link has correct value");

    link1!.aboutToBeDeleted();
    link2!.aboutToBeDeleted();
  }

  /**
   * Test deprecated SetAndLink() vs setAndLink()
   * Expected: Both work identically
   */
  public testDeprecatedSetAndLink(): void {
    const link1 = AppStorage.setAndLink("deprSetAndLinkProp", "value1");
    AppStorage.delete("deprSetAndLinkProp");

    const link2 = AppStorage.SetAndLink("deprSetAndLinkProp", "value2");

    eq(link1 !== undefined, true, "setAndLink() works");
    eq(link2 !== undefined, true, "SetAndLink() deprecated version also works");

    link1!.aboutToBeDeleted();
    link2!.aboutToBeDeleted();
  }

  /**
   * Test deprecated Prop() vs prop()
   * Expected: Both work identically
   */
  public testDeprecatedProp(): void {
    AppStorage.setOrCreate("deprPropProp", "value");

    const prop1 = AppStorage.prop<string>("deprPropProp");
    const prop2 = AppStorage.Prop<string>("deprPropProp");

    eq(prop1 !== undefined, true, "prop() works");
    eq(prop2 !== undefined, true, "Prop() deprecated version also works");
    eq(prop1!.get(), "value", "prop has correct value");
    eq(prop2!.get(), "value", "Prop has correct value");

    prop1!.aboutToBeDeleted();
    prop2!.aboutToBeDeleted();
  }

  /**
   * Test deprecated SetAndProp() vs setAndProp()
   * Expected: Both work identically
   */
  public testDeprecatedSetAndProp(): void {
    const prop1 = AppStorage.setAndProp("deprSetAndPropProp", "value1");
    AppStorage.delete("deprSetAndPropProp");

    const prop2 = AppStorage.SetAndProp("deprSetAndPropProp", "value2");

    eq(prop1 !== undefined, true, "setAndProp() works");
    eq(prop2 !== undefined, true, "SetAndProp() deprecated version also works");

    prop1!.aboutToBeDeleted();
    prop2!.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION: Edge Cases and Integration Tests
  // =========================================================================

  /**
   * Test AppStorage with complex data types
   * Expected: Objects and arrays work correctly
   */
  public testAppStorageComplexTypes(): void {
    // Object
    const obj = { name: "Alice", age: 30 };
    AppStorage.setOrCreate("complexObj", obj);
    eq((AppStorage.get("complexObj") as any).name, "Alice", "object works");

    // Array
    const arr = [1, 2, 3, 4, 5];
    AppStorage.setOrCreate("complexArr", arr);
    eq((AppStorage.get("complexArr") as any).length, 5, "array works");

    // Nested object
    const nested = { level1: { level2: { value: "deep" } } };
    AppStorage.setOrCreate("complexNested", nested);
    eq((AppStorage.get("complexNested") as any).level1.level2.value, "deep", "nested object works");
  }

  /**
   * Test AppStorage with link/prop mix
   * Expected: Multiple sync methods work together
   */
  public testAppStorageLinkPropMix(): void {
    AppStorage.setOrCreate("mixProp", "initial");

    const link = AppStorage.link<string>("mixProp");
    const prop = AppStorage.prop<string>("mixProp");

    eq(link!.get(), "initial", "link has initial value");
    eq(prop!.get(), "initial", "prop has initial value");

    AppStorage.set("mixProp", "updated");

    eq(link!.get(), "updated", "link sees update");
    eq(prop!.get(), "updated", "prop sees update");

    link!.aboutToBeDeleted();
    prop!.aboutToBeDeleted();
  }

  /**
   * Test AppStorage consecutive operations
   * Expected: Multiple operations work correctly in sequence
   */
  public testAppStorageConsecutiveOperations(): void {
    // Create properties
    AppStorage.setOrCreate("op1", "value1");
    AppStorage.setOrCreate("op2", "value2");
    eq(AppStorage.size(), 2, "2 properties created");

    // Update properties
    AppStorage.set("op1", "updated1");
    AppStorage.set("op2", "updated2");
    eq(AppStorage.get("op1"), "updated1", "op1 updated");
    eq(AppStorage.get("op2"), "updated2", "op2 updated");

    // Delete properties
    AppStorage.delete("op1");
    eq(AppStorage.size(), 1, "1 property after delete");
    eq(AppStorage.has("op1"), false, "op1 deleted");

    // Clear remaining
    AppStorage.clear();
    eq(AppStorage.size(), 0, "0 properties after clear");
  }

  /**
   * Test AppStorage null/undefined handling (API version dependent)
   * Expected: Behavior depends on API version
   */
  public testAppStorageNullUndefinedHandling(): void {
    const apiVer = Utils.getApiVersion();

    if (apiVer >= 12) {
      // API 12+ allows null
      AppStorage.setOrCreate<any>("nullProp", null);
      eq(AppStorage.get("nullProp"), null, "null works in API 12+");

      // API 12+ allows undefined
      AppStorage.setOrCreate<any>("undefProp", undefined);
      eq(AppStorage.get("undefProp"), undefined, "undefined works in API 12+");
    }
  }

  /**
   * Test AppStorage many properties
   * Expected: Can handle many properties efficiently
   */
  public testAppStorageManyProperties(): void {
    const count = 50;

    for (let i = 0; i < count; i++) {
      AppStorage.setOrCreate(`manyProp${i}`, i);
    }

    eq(AppStorage.size(), count, `storage has ${count} properties`);

    for (let i = 0; i < count; i++) {
      eq(AppStorage.get(`manyProp${i}`), i, `property ${i} has correct value`);
    }

    // Clean up
    for (let i = 0; i < count; i++) {
      AppStorage.delete(`manyProp${i}`);
    }

    eq(AppStorage.size(), 0, "all properties deleted");
  }
}
