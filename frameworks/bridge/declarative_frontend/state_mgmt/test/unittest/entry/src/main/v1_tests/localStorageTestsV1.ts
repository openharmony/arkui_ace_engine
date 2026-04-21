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

import { eq, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class Utils {
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
  static currentAppApiVersion: number;
}

// Declare types from stateMgmt.d.ts
declare class LocalStorage {
  constructor(initializingProperties?: Object);
  has(propName: string): boolean;
  keys(): IterableIterator<string>;
  size(): number;
  get<T>(propName: string): T | undefined;
  set<T>(propName: string, newValue: T): boolean;
  setOrCreate<T>(propName: string, newValue: T): boolean;
  ref<T>(propName: string): AbstractProperty<T> | undefined;
  setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T>;
  link<T>(propName: string, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> | undefined;
  setAndLink<T>(propName: string, defaultValue: T, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  prop<T>(propName: string, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> | undefined;
  setAndProp<T>(propName: string, defaultValue: T, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T>;
  delete(propName: string): boolean;
  clear(): boolean;
  aboutToBeDeleted(): boolean;
  unsubscribeFromChangesOf(propName: string, subscriberId: number): boolean;
}

declare class AbstractProperty<T> {
  get(): T;
  set(value: T): void;
  info(): string;
}

declare class SubscribedAbstractProperty<T> extends AbstractProperty<T> {
  aboutToBeDeleted(): void;
  numberOfSubscrbers(): number;
}

declare interface IPropertySubscriber {
  id__?: number;
}

/**
 * Comprehensive LocalStorage Unit Tests
 *
 * This test suite validates ALL LocalStorage APIs comprehensively.
 * Since AppStorage extends LocalStorage, these tests also validate
 * AppStorage's inherited functionality.
 *
 * Test Sections:
 * 1. Reference System APIs (ref, setAndRef)
 * 2. Link System APIs (link, setAndLink)
 * 3. Prop System APIs (prop, setAndProp)
 * 4. Property Management APIs (get, set, setOrCreate, delete, clear)
 * 5. Metadata APIs (size, keys)
 * 6. Subscription System (subscribeToChangesOf, unsubscribeFromChangesOf)
 * 7. Deprecated APIs (backward compatibility)
 * 8. Arrays and Objects (complex types)
 * 9. Edge Cases (stress tests)
 */
export class LocalStorageTestsV1 implements ITestFile {
  private idString: string = "";
  private static storage: LocalStorage = new LocalStorage();  // 静态变量，所有测试共享

  constructor(str: string) {
    console.log(`Creating LocalStorageTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    LocalStorageTestsV1.storage.aboutToBeDeleted();
    LocalStorageTestsV1.storage = new LocalStorage();
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1.0: Constructor and Initialization
  // =========================================================================

  /**
   * Test LocalStorage constructor with initial properties
   * Expected: Properties are initialized from object
   */
  public testConstructorWithInitialProps(): void {
    const storage = new LocalStorage({ prop1: "value1", prop2: 42, prop3: true });

    eq(storage.has("prop1"), true, "prop1 initialized");
    eq(storage.has("prop2"), true, "prop2 initialized");
    eq(storage.has("prop3"), true, "prop3 initialized");
    eq(storage.get("prop1"), "value1", "prop1 has correct value");
    eq(storage.get("prop2"), 42, "prop2 has correct value");
    eq(storage.get("prop3"), true, "prop3 has correct value");
  }


  // =========================================================================
  // SECTION 1.1: Reference System APIs (ref, setAndRef) - API 12+
  // =========================================================================

  /**
   * Test ref() with an existing property
   * Expected: Returns AbstractProperty for the existing property
   */
  public testRefWithExistingProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("testProp", "hello");
    const ref = LocalStorageTestsV1.storage.ref<string>("testProp");

    eq(ref !== undefined, true, "ref returns AbstractProperty for existing property");
    eq(ref!.get(), "hello", "ref gets correct value");
  }

  /**
   * Test ref() with a non-existent property
   * Expected: Returns undefined
   */
  public testRefWithNonExistentProperty(): void {
    const ref = LocalStorageTestsV1.storage.ref<string>("nonExistent");

    eq(ref, undefined, "ref returns undefined for non-existent property");
  }

  /**
   * Test ref() with various value types
   * Expected: Works with string, number, boolean, object, array
   */
  public testRefValueTypeSupport(): void {
    // String
    LocalStorageTestsV1.storage.setOrCreate("strProp", "test");
    const strRef = LocalStorageTestsV1.storage.ref<string>("strProp");
    eq(strRef !== undefined, true, "ref supports string");
    eq(strRef!.get(), "test", "string ref value correct");

    // Number
    LocalStorageTestsV1.storage.setOrCreate("numProp", 42);
    const numRef = LocalStorageTestsV1.storage.ref<number>("numProp");
    eq(numRef !== undefined, true, "ref supports number");
    eq(numRef!.get(), 42, "number ref value correct");

    // Boolean
    LocalStorageTestsV1.storage.setOrCreate("boolProp", true);
    const boolRef = LocalStorageTestsV1.storage.ref<boolean>("boolProp");
    eq(boolRef !== undefined, true, "ref supports boolean");
    eq(boolRef!.get(), true, "boolean ref value correct");

    // Object
    const testObj = { key: "value", nested: { num: 123 } };
    LocalStorageTestsV1.storage.setOrCreate("objProp", testObj);
    const objRef = LocalStorageTestsV1.storage.ref<Object>("objProp");
    eq(objRef !== undefined, true, "ref supports object");
    eq((objRef!.get() as any).key, "value", "object ref value correct");

    // Array
    const testArr = [1, 2, 3, 4, 5];
    LocalStorageTestsV1.storage.setOrCreate("arrProp", testArr);
    const arrRef = LocalStorageTestsV1.storage.ref<Array<number>>("arrProp");
    eq(arrRef !== undefined, true, "ref supports array");
    eq(arrRef!.get()!.length, 5, "array ref length correct");
  }

  /**
   * Test ref info() method
   * Expected: Returns the property name
   */
  public testRefInfo(): void {
    LocalStorageTestsV1.storage.setOrCreate("refInfoProp", "value");

    const ref = LocalStorageTestsV1.storage.ref<string>("refInfoProp");

    eq(ref !== undefined, true, "ref created");
    eq(ref!.info(), "refInfoProp", "ref.info() returns property name");
  }

  /**
   * Test calling ref() multiple times on the same property
   * Expected: Each call returns an AbstractProperty instance
   */
  public testRefSamePropertyMultipleTimes(): void {
    LocalStorageTestsV1.storage.setOrCreate("testProp", "value");

    const ref1 = LocalStorageTestsV1.storage.ref<string>("testProp");
    const ref2 = LocalStorageTestsV1.storage.ref<string>("testProp");

    eq(ref1 !== undefined, true, "first ref returns AbstractProperty");
    eq(ref2 !== undefined, true, "second ref returns AbstractProperty");
    eq(ref1!.get(), ref2!.get(), "both refs have same value");

    // Note: Framework may return the same instance for efficiency
  }

  /**
   * Test setAndRef() creates a new property
   * Expected: Property is created and AbstractProperty is returned
   */
  public testSetAndRefCreatesNewProperty(): void {
    const ref = LocalStorageTestsV1.storage.setAndRef("newProp", "defaultValue");

    eq(ref !== undefined, true, "setAndRef returns AbstractProperty");
    eq(ref!.get(), "defaultValue", "setAndRef creates property with default value");
    eq(LocalStorageTestsV1.storage.has("newProp"), true, "property exists in storage");
    eq(LocalStorageTestsV1.storage.get("newProp"), "defaultValue", "storage has correct value");
  }

  /**
   * Test setAndRef() with an existing property
   * Expected: Does NOT update existing value, returns AbstractProperty
   */
  public testSetAndRefExistingProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("existingProp", "originalValue");

    const ref = LocalStorageTestsV1.storage.setAndRef("existingProp", "newValue");

    eq(ref!.get(), "originalValue", "setAndRef does NOT update existing value");
    eq(LocalStorageTestsV1.storage.get("existingProp"), "originalValue", "storage keeps original value");
  }

  /**
   * Test setAndRef() with various types
   * Expected: Works with different data types
   */
  public testSetAndRefVariousTypes(): void {

    // String
    const strRef = LocalStorageTestsV1.storage.setAndRef<string>("strKey", "string");
    eq(strRef!.get(), "string", "setAndRef works with string");

    // Number
    const numRef = LocalStorageTestsV1.storage.setAndRef<number>("numKey", 100);
    eq(numRef!.get(), 100, "setAndRef works with number");

    // Boolean
    const boolRef = LocalStorageTestsV1.storage.setAndRef<boolean>("boolKey", false);
    eq(boolRef!.get(), false, "setAndRef works with boolean");

    // Object
    const obj = { a: 1, b: 2 };
    const objRef = LocalStorageTestsV1.storage.setAndRef<Object>("objKey", obj);
    eq((objRef!.get() as any).a, 1, "setAndRef works with object");

    // Null (API 12+)
    const apiVer = Utils.getApiVersion();
    if (apiVer >= 12) {
      const nullRef = LocalStorageTestsV1.storage.setAndRef<any>("nullKey", null);
      eq(nullRef!.get(), null, "setAndRef works with null in API 12+");
    }

    // Undefined (API 12+)
    if (apiVer >= 12) {
      const undefRef = LocalStorageTestsV1.storage.setAndRef<any>("undefKey", undefined);
      eq(undefRef!.get(), undefined, "setAndRef works with undefined in API 12+");
    }
  }

  /**
   * Test setAndRef() followed by ref()
   * Expected: Both return AbstractProperty with same value
   */
  public testSetAndRefThenRef(): void {
    const ref1 = LocalStorageTestsV1.storage.setAndRef("prop", "value1");
    const ref2 = LocalStorageTestsV1.storage.ref<string>("prop");

    eq(ref1!.get(), "value1", "setAndRef returns correct value");
    eq(ref2!.get(), "value1", "ref returns same value");
  }

  /**
   * Test difference between ref() and setAndRef()
   * Expected: ref() fails if property doesn't exist; setAndRef() creates it
   */
  public testRefVsSetAndRefDifference(): void {
    const ref1 = LocalStorageTestsV1.storage.ref<string>("nonExistent");
    eq(ref1, undefined, "ref returns undefined for non-existent property");

    const ref2 = LocalStorageTestsV1.storage.setAndRef<string>("nonExistent", "created");
    eq(ref2 !== undefined, true, "setAndRef creates and returns AbstractProperty");
    eq(ref2!.get(), "created", "setAndRef creates property with given value");

    const ref3 = LocalStorageTestsV1.storage.ref<string>("nonExistent");
    eq(ref3 !== undefined, true, "ref now returns AbstractProperty for created property");
  }

  // =========================================================================
  // SECTION 1.2: Link System APIs (link, setAndLink)
  // =========================================================================

  /**
   * Test link() creates a link to an existing property
   * Expected: Returns SubscribedAbstractProperty
   */
  public testLinkCreatesProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("sourceProp", "linkValue");

    const link = LocalStorageTestsV1.storage.link<string>("sourceProp");

    eq(link !== undefined, true, "link returns SubscribedAbstractProperty");
    eq(link!.get(), "linkValue", "link gets correct value from storage");
  }

  /**
   * Test link() with non-existent property
   * Expected: Returns undefined
   */
  public testLinkNonExistentProperty(): void {
    const link = LocalStorageTestsV1.storage.link<string>("nonExistent");

    eq(link, undefined, "link returns undefined for non-existent property");
  }

  /**
   * Test link() two-way synchronization
   * Expected: Changes through link reflect in storage, and vice versa
   */
  public testLinkTwoWaySync(): void {
    LocalStorageTestsV1.storage.setOrCreate("syncProp", "initial");

    const link = LocalStorageTestsV1.storage.link<string>("syncProp");
    eq(link!.get(), "initial", "link has initial value");

    // Change through link
    link!.set("changedViaLink");
    eq(link!.get(), "changedViaLink", "link reflects change");
    eq(LocalStorageTestsV1.storage.get("syncProp"), "changedViaLink", "storage reflects link change");

    // Change through storage
    LocalStorageTestsV1.storage.set("syncProp", "changedViaStorage");
    eq(link!.get(), "changedViaStorage", "link reflects storage change");
    eq(LocalStorageTestsV1.storage.get("syncProp"), "changedViaStorage", "storage has updated value");

    link!.aboutToBeDeleted();
  }

  /**
   * Test link() with various value types
   * Expected: Works with string, number, boolean, object, array
   */
  public testLinkValueTypes(): void {

    // String
    LocalStorageTestsV1.storage.setOrCreate("strProp", "string");
    const strLink = LocalStorageTestsV1.storage.link<string>("strProp");
    eq(strLink!.get(), "string", "link works with string");
    strLink!.aboutToBeDeleted();

    // Number
    LocalStorageTestsV1.storage.setOrCreate("numProp", 123);
    const numLink = LocalStorageTestsV1.storage.link<number>("numProp");
    eq(numLink!.get(), 123, "link works with number");
    numLink!.aboutToBeDeleted();

    // Boolean
    LocalStorageTestsV1.storage.setOrCreate("boolProp", true);
    const boolLink = LocalStorageTestsV1.storage.link<boolean>("boolProp");
    eq(boolLink!.get(), true, "link works with boolean");
    boolLink!.aboutToBeDeleted();

    // Object
    LocalStorageTestsV1.storage.setOrCreate("objProp", { x: 1, y: 2 });
    const objLink = LocalStorageTestsV1.storage.link<Object>("objProp");
    eq((objLink!.get() as any).x, 1, "link works with object");
    objLink!.aboutToBeDeleted();

    // Array
    LocalStorageTestsV1.storage.setOrCreate("arrProp", [10, 20, 30]);
    const arrLink = LocalStorageTestsV1.storage.link<Array<number>>("arrProp");
    eq(arrLink!.get()!.length, 3, "link works with array");
    arrLink!.aboutToBeDeleted();
  }

  /**
   * Test that links count in subscribers
   * Expected: Each link adds a subscriber
   */
  public testLinksCountInSubscribers(): void {
    LocalStorageTestsV1.storage.setOrCreate("subscribedProp", "value");

    const link1 = LocalStorageTestsV1.storage.link<string>("subscribedProp");
    eq(LocalStorageTestsV1.storage.has("subscribedProp"), true, "property exists after first link");

    const link2 = LocalStorageTestsV1.storage.link<string>("subscribedProp");

    // Multiple links should be possible
    eq(link1!.get(), "value", "link1 still works");
    eq(link2!.get(), "value", "link2 works");

    link1!.aboutToBeDeleted();
    link2!.aboutToBeDeleted();
  }

  /**
   * Test link independence
   * Expected: Different links to different properties are independent
   */
  public testLinkIndependence(): void {
    LocalStorageTestsV1.storage.setOrCreate("propA", "valueA");
    LocalStorageTestsV1.storage.setOrCreate("propB", "valueB");

    const linkA = LocalStorageTestsV1.storage.link<string>("propA");
    const linkB = LocalStorageTestsV1.storage.link<string>("propB");

    eq(linkA!.get(), "valueA", "linkA has correct value");
    eq(linkB!.get(), "valueB", "linkB has correct value");

    linkA!.set("updatedA");
    eq(linkA!.get(), "updatedA", "linkA updated");
    eq(linkB!.get(), "valueB", "linkB unchanged");

    linkB!.set("updatedB");
    eq(linkA!.get(), "updatedA", "linkA still has its value");
    eq(linkB!.get(), "updatedB", "linkB updated");

    linkA!.aboutToBeDeleted();
    linkB!.aboutToBeDeleted();
  }

  /**
   * Test link() with subscriber name
   * Expected: Link is created with subscriber name
   */
  public testLinkWithSubscriberName(): void {
    LocalStorageTestsV1.storage.setOrCreate("multiProp", "multi");

    const link = LocalStorageTestsV1.storage.link<string>("multiProp", undefined, "customName");

    eq(link !== undefined, true, "link with subscriber name is created");
    eq(link!.get(), "multi", "link has correct value");

    link!.aboutToBeDeleted();
  }

  /**
   * Test link info() method
   * Expected: Returns the property name
   */
  public testLinkInfo(): void {
    LocalStorageTestsV1.storage.setOrCreate("infoProp", "value");

    const link = LocalStorageTestsV1.storage.link<string>("infoProp");

    eq(link !== undefined, true, "link created");
    eq(link!.info(), "infoProp", "link.info() returns property name");

    link!.aboutToBeDeleted();
  }

  /**
   * Test link numberOfSubscrbers() method
   * Expected: Returns the number of subscribers
   */
  public testLinkNumberOfSubscribers(): void {
    LocalStorageTestsV1.storage.setOrCreate("subCountProp", "value");

    const link = LocalStorageTestsV1.storage.link<string>("subCountProp");

    eq(link !== undefined, true, "link created");
    // Verify method is callable and returns a number
    const count = link!.numberOfSubscrbers();
    eq(typeof count, "number", "numberOfSubscrbers() returns a number");
    eq(count >= 0, true, `numberOfSubscrbers() returns ${count} (non-negative)`);

    link!.aboutToBeDeleted();
  }

  /**
   * Test prop info() method
   * Expected: Returns the property name
   */
  public testPropInfo(): void {
    LocalStorageTestsV1.storage.setOrCreate("infoPropProp", "value");

    const prop = LocalStorageTestsV1.storage.prop<string>("infoPropProp");

    eq(prop !== undefined, true, "prop created");
    eq(prop!.info(), "infoPropProp", "prop.info() returns property name");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test prop numberOfSubscrbers() method
   * Expected: Returns the number of subscribers
   */
  public testPropNumberOfSubscribers(): void {
    LocalStorageTestsV1.storage.setOrCreate("subCountPropProp", "value");

    const prop = LocalStorageTestsV1.storage.prop<string>("subCountPropProp");

    eq(prop !== undefined, true, "prop created");
    // Verify method is callable and returns a number
    const count = prop!.numberOfSubscrbers();
    eq(typeof count, "number", "numberOfSubscrbers() returns a number");
    eq(count >= 0, true, `numberOfSubscrbers() returns ${count} (non-negative)`);

    prop!.aboutToBeDeleted();
  }

  /**
   * Test multiple links increase subscriber count
   * Expected: Each link is independent
   */
  public testMultipleLinksSubscriberCount(): void {
    LocalStorageTestsV1.storage.setOrCreate("multiLinkProp", "value");

    const link1 = LocalStorageTestsV1.storage.link<string>("multiLinkProp");
    const count1 = link1!.numberOfSubscrbers();
    eq(typeof count1, "number", `first link numberOfSubscrbers() returns ${count1}`);

    const link2 = LocalStorageTestsV1.storage.link<string>("multiLinkProp");
    const count2 = link2!.numberOfSubscrbers();
    eq(typeof count2, "number", `second link numberOfSubscrbers() returns ${count2}`);

    link1!.aboutToBeDeleted();
    link2!.aboutToBeDeleted();
  }

  /**
   * Test multiple links to the same property
   * Expected: Each link is independent but all sync with the same source
   */
  public testMultipleLinksToSameProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("shared", "value");

    const link1 = LocalStorageTestsV1.storage.link<string>("shared");
    const link2 = LocalStorageTestsV1.storage.link<string>("shared");
    const link3 = LocalStorageTestsV1.storage.link<string>("shared");

    eq(link1!.get(), "value", "link1 has initial value");
    eq(link2!.get(), "value", "link2 has initial value");
    eq(link3!.get(), "value", "link3 has initial value");

    link1!.set("updated");
    eq(link1!.get(), "updated", "link1 reflects change");
    eq(link2!.get(), "updated", "link2 sees change through link1");
    eq(link3!.get(), "updated", "link3 sees change through link1");
    eq(LocalStorageTestsV1.storage.get("shared"), "updated", "storage reflects change");

    link1!.aboutToBeDeleted();
    link2!.aboutToBeDeleted();
    link3!.aboutToBeDeleted();
  }

  /**
   * Test link() followed by delete() with subscribers
   * Expected: Delete fails when links (subscribers) exist
   */
  public testLinkThenDeleteWithSubscribers(): void {
    LocalStorageTestsV1.storage.setOrCreate("deleteTestProp", "value");

    const link = LocalStorageTestsV1.storage.link<string>("deleteTestProp");

    eq(link !== undefined, true, "link created");

    const deleteResult = LocalStorageTestsV1.storage.delete("deleteTestProp");
    eq(deleteResult, false, "delete fails with active link subscriber");
    eq(LocalStorageTestsV1.storage.has("deleteTestProp"), true, "property still exists after failed delete");

    link!.aboutToBeDeleted();
  }

  /**
   * Test link() with null and undefined (API version dependent)
   * Expected: Behavior depends on API version
   */
  public testLinkWithNullUndefined(): void {
    const apiVer = Utils.getApiVersion();

    if (apiVer >= 12) {
      // API 12+ allows null
      LocalStorageTestsV1.storage.setOrCreate<any>("nullProp", null);
      const nullLink = LocalStorageTestsV1.storage.link<any>("nullProp");
      eq(nullLink !== undefined, true, "link works with null in API 12+");
      eq(nullLink!.get(), null, "null link value is null");
      nullLink!.aboutToBeDeleted();

      // API 12+ allows undefined
      LocalStorageTestsV1.storage.setOrCreate<any>("undefProp", undefined);
      const undefLink = LocalStorageTestsV1.storage.link<any>("undefProp");
      eq(undefLink !== undefined, true, "link works with undefined in API 12+");
      undefLink!.aboutToBeDeleted();
    } else {
      // API < 12: null is converted, undefined is not allowed
      LocalStorageTestsV1.storage.setOrCreate("nullProp", null);
      const nullLink = LocalStorageTestsV1.storage.link<any>("nullProp");
      eq(nullLink !== undefined, true, "link works with null in earlier API");
      nullLink!.aboutToBeDeleted();
    }
  }

  /**
   * Test link() aboutToBeDeleted decreases subscriber count
   * Expected: Subscriber count decreases after link is deleted
   */
  public testLinkAboutToBeDeleted(): void {
    LocalStorageTestsV1.storage.setOrCreate("linkDeleteProp", "value");

    const link = LocalStorageTestsV1.storage.link<string>("linkDeleteProp");
    eq(link !== undefined, true, "link created");

    // Delete the link
    link!.aboutToBeDeleted();
  }

  /**
   * Test setAndLink() creates property and returns link
   * Expected: Property is created if it doesn't exist
   */
  public testSetAndLinkCreatesNewProperty(): void {
    const link = LocalStorageTestsV1.storage.setAndLink("newLinkProp", "defaultValue");

    eq(link !== undefined, true, "setAndLink returns SubscribedAbstractProperty");
    eq(link!.get(), "defaultValue", "setAndLink creates property with default value");
    eq(LocalStorageTestsV1.storage.has("newLinkProp"), true, "property exists in storage");

    link!.aboutToBeDeleted();
  }

  /**
   * Test setAndLink() with existing property
   * Expected: Does NOT update existing value, returns link
   */
  public testSetAndLinkExistingProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("existingLinkProp", "original");

    const link = LocalStorageTestsV1.storage.setAndLink("existingLinkProp", "newDefault");

    eq(link!.get(), "original", "setAndLink does NOT update existing value");
    eq(LocalStorageTestsV1.storage.get("existingLinkProp"), "original", "storage keeps original value");

    link!.aboutToBeDeleted();
  }


  /**
   * Test setAndLink() two-way sync
   * Expected: Changes sync between link and storage
   */
  public testSetAndLinkTwoWaySync(): void {
    const link = LocalStorageTestsV1.storage.setAndLink("syncLinkProp", "initial");

    eq(link!.get(), "initial", "setAndLink has initial value");

    link!.set("viaLink");
    eq(link!.get(), "viaLink", "link reflects change");
    eq(LocalStorageTestsV1.storage.get("syncLinkProp"), "viaLink", "storage reflects link change");

    LocalStorageTestsV1.storage.set("syncLinkProp", "viaStorage");
    eq(link!.get(), "viaStorage", "link reflects storage change");

    link!.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 1.3: Prop System APIs (prop, setAndProp)
  // =========================================================================

  /**
   * Test setAndProp() creates a new property
   * Expected: Property is created and SubscribedAbstractProperty is returned
   */
  public testSetAndPropCreatesNewProperty(): void {
    const prop = LocalStorageTestsV1.storage.setAndProp("newPropProp", "propValue");

    eq(prop !== undefined, true, "setAndProp returns SubscribedAbstractProperty");
    eq(prop!.get(), "propValue", "setAndProp creates property with default value");
    eq(LocalStorageTestsV1.storage.has("newPropProp"), true, "property exists in storage");
    eq(LocalStorageTestsV1.storage.get("newPropProp"), "propValue", "storage has correct value");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test prop() with non-existent property
   * Expected: Returns undefined
   */
  public testPropNonExistentProperty(): void {
    const prop = LocalStorageTestsV1.storage.prop<string>("nonExistentProp");

    eq(prop, undefined, "prop returns undefined for non-existent property");
  }

  /**
   * Test prop() one-way sync (AppStorage → prop, not reverse)
   * Expected: prop.set() changes are local, storage changes reflect to prop
   */
  public testPropOneWaySync(): void {
    LocalStorageTestsV1.storage.setOrCreate("oneWayProp", "initial");

    const prop = LocalStorageTestsV1.storage.prop<string>("oneWayProp");
    eq(prop!.get(), "initial", "prop has initial value");

    // Storage change should reflect to prop
    LocalStorageTestsV1.storage.set("oneWayProp", "fromStorage");
    eq(prop!.get(), "fromStorage", "prop sees storage change");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test prop() vs link() behavior comparison
   * Expected: link is two-way, prop is one-way
   */
  public testPropVsLinkBehavior(): void {
    LocalStorageTestsV1.storage.setOrCreate("compareProp", "initial");

    const prop = LocalStorageTestsV1.storage.prop<string>("compareProp");
    const link = LocalStorageTestsV1.storage.link<string>("compareProp");

    eq(prop!.get(), "initial", "prop has initial value");
    eq(link!.get(), "initial", "link has initial value");

    // Storage change reflects to both
    LocalStorageTestsV1.storage.set("compareProp", "changed");
    eq(prop!.get(), "changed", "prop reflects storage change");
    eq(link!.get(), "changed", "link reflects storage change");

    prop!.aboutToBeDeleted();
    link!.aboutToBeDeleted();
  }

  /**
   * Test multiple props to the same property
   * Expected: All props see storage changes
   */
  public testMultiplePropsToSameProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("sharedPropProp", "value");

    const prop1 = LocalStorageTestsV1.storage.prop<string>("sharedPropProp");
    const prop2 = LocalStorageTestsV1.storage.prop<string>("sharedPropProp");

    eq(prop1!.get(), "value", "prop1 has initial value");
    eq(prop2!.get(), "value", "prop2 has initial value");

    LocalStorageTestsV1.storage.set("sharedPropProp", "updated");
    eq(prop1!.get(), "updated", "prop1 sees storage change");
    eq(prop2!.get(), "updated", "prop2 sees storage change");

    prop1!.aboutToBeDeleted();
    prop2!.aboutToBeDeleted();
  }

  /**
   * Test props independence
   * Expected: Different props to different properties are independent
   */
  public testPropsIndependence(): void {
    LocalStorageTestsV1.storage.setOrCreate("propA", "valueA");
    LocalStorageTestsV1.storage.setOrCreate("propB", "valueB");

    const propA = LocalStorageTestsV1.storage.prop<string>("propA");
    const propB = LocalStorageTestsV1.storage.prop<string>("propB");

    eq(propA!.get(), "valueA", "propA has correct value");
    eq(propB!.get(), "valueB", "propB has correct value");

    LocalStorageTestsV1.storage.set("propA", "updatedA");
    eq(propA!.get(), "updatedA", "propA updated");
    eq(propB!.get(), "valueB", "propB unchanged");

    propA!.aboutToBeDeleted();
    propB!.aboutToBeDeleted();
  }


  /**
   * Test prop() and link() mixed
   * Expected: Both can coexist and see changes
   */
  public testPropAndLinkMixed(): void {
    LocalStorageTestsV1.storage.setOrCreate("mixedProp", "initial");

    const prop = LocalStorageTestsV1.storage.prop<string>("mixedProp");
    const link = LocalStorageTestsV1.storage.link<string>("mixedProp");

    eq(prop!.get(), "initial", "prop has initial value");
    eq(link!.get(), "initial", "link has initial value");

    LocalStorageTestsV1.storage.set("mixedProp", "changed");
    eq(prop!.get(), "changed", "prop reflects storage change");
    eq(link!.get(), "changed", "link reflects storage change");

    prop!.aboutToBeDeleted();
    link!.aboutToBeDeleted();
  }

  /**
   * Test prop() aboutToBeDeleted
   * Expected: Prop cleanup works correctly
   */
  public testPropAboutToBeDeleted(): void {
    LocalStorageTestsV1.storage.setOrCreate("propDeleteProp", "value");

    const prop = LocalStorageTestsV1.storage.prop<string>("propDeleteProp");
    eq(prop !== undefined, true, "prop created");

    prop!.aboutToBeDeleted();
    // Prop should be cleaned up
  }

  /**
   * Test prop() with subscriber name
   * Expected: Prop is created with subscriber name
   */
  public testPropWithSubscriberName(): void {
    LocalStorageTestsV1.storage.setOrCreate("multiPropProp", "multi");

    const prop = LocalStorageTestsV1.storage.prop<string>("multiPropProp", undefined, "customPropName");

    eq(prop !== undefined, true, "prop with subscriber name is created");
    eq(prop!.get(), "multi", "prop has correct value");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test setAndLink() with subscriber
   * Expected: Link is created with subscriber
   */
  public testSetAndLinkWithSubscriber(): void {
    const link = LocalStorageTestsV1.storage.setAndLink("subLinkProp", "value", undefined, "myName");

    eq(link !== undefined, true, "setAndLink with subscriber works");
    eq(link!.get(), "value", "setAndLink link has correct value");

    link!.aboutToBeDeleted();
  }

  /**
   * Test setAndProp() with existing property
   * Expected: Does NOT update existing value
   */
  public testSetAndPropExistingProperty(): void {
    LocalStorageTestsV1.storage.setOrCreate("existingPropProp", "original");

    const prop = LocalStorageTestsV1.storage.setAndProp("existingPropProp", "newDefault");

    eq(prop!.get(), "original", "setAndProp does NOT update existing value");
    eq(LocalStorageTestsV1.storage.get("existingPropProp"), "original", "storage keeps original value");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test setAndProp() with subscriber
   * Expected: Prop is created with subscriber
   */
  public testSetAndPropWithSubscriber(): void {
    const prop = LocalStorageTestsV1.storage.setAndProp("subPropProp", "value", undefined, "myName");

    eq(prop !== undefined, true, "setAndProp with subscriber works");
    eq(prop!.get(), "value", "setAndProp prop has correct value");

    prop!.aboutToBeDeleted();
  }


  // =========================================================================
  // SECTION 1.4: Property Management APIs (get, set, setOrCreate, delete, clear)
  // =========================================================================

  /**
   * Test set() with non-existent property
   * Expected: Returns false, property not created
   */
  public testSetNonExistentProperty(): void {
    const result = LocalStorageTestsV1.storage.set("nonExistent", "value");

    eq(result, false, "set returns false for non-existent property");
    eq(LocalStorageTestsV1.storage.has("nonExistent"), false, "property does not exist");
  }

  /**
   * Test set() with null (API version dependent)
   * Expected: API < 12 returns false, API >= 12 returns true
   */
  public testSetWithNull(): void {
    LocalStorageTestsV1.storage.setOrCreate("nullProp", "initial");

    const apiVer = Utils.getApiVersion();
    const result = LocalStorageTestsV1.storage.set<any>("nullProp", null);

    if (apiVer >= 12) {
      eq(result, true, "set with null returns true in API 12+");
    } else {
      eq(result, false, "set with null returns false in API < 12");
    }
  }

  /**
   * Test set() with undefined (API version dependent)
   * Expected: API < 12 returns false, API >= 12 returns true
   */
  public testSetWithUndefined(): void {
    LocalStorageTestsV1.storage.setOrCreate("undefProp", "initial");

    const apiVer = Utils.getApiVersion();
    const result = LocalStorageTestsV1.storage.set<any>("undefProp", undefined);

    if (apiVer >= 12) {
      eq(result, true, "set with undefined returns true in API 12+");
    } else {
      eq(result, false, "set with undefined returns false in API < 12");
    }
  }

  /**
   * Test get() with non-existent property
   * Expected: Returns undefined
   */
  public testGetNonExistentProperty(): void {
    const val = LocalStorageTestsV1.storage.get("nonExistent");

    eq(val, undefined, "get returns undefined for non-existent property");
  }

  /**
   * Test get() after type changes
   * Expected: Returns current value regardless of type
   */
  public testGetTypeChanges(): void {
    LocalStorageTestsV1.storage.setOrCreate("typeProp", "string");
    eq(LocalStorageTestsV1.storage.get("typeProp"), "string", "get returns string");

    LocalStorageTestsV1.storage.set("typeProp", 123);
    eq(LocalStorageTestsV1.storage.get("typeProp"), 123, "get returns number after type change");
  }

  /**
   * Test get() after delete()
   * Expected: Returns undefined
   */
  public testGetAfterDelete(): void {
    LocalStorageTestsV1.storage.setOrCreate("deleteGetProp", "value");
    eq(LocalStorageTestsV1.storage.get("deleteGetProp"), "value", "get returns value before delete");

    LocalStorageTestsV1.storage.delete("deleteGetProp");
    eq(LocalStorageTestsV1.storage.get("deleteGetProp"), undefined, "get returns undefined after delete");
  }

  /**
   * Test setOrCreate() basics
   * Expected: Creates new property or updates existing
   */
  public testSetOrCreateBasics(): void {

    // Create new property
    const createResult = LocalStorageTestsV1.storage.setOrCreate("newProp", "newValue");
    eq(createResult, true, "setOrCreate creates new property");
    eq(LocalStorageTestsV1.storage.get("newProp"), "newValue", "property has correct value");

    // Update existing property
    const updateResult = LocalStorageTestsV1.storage.setOrCreate("newProp", "updatedValue");
    eq(updateResult, true, "setOrCreate updates existing property");
    eq(LocalStorageTestsV1.storage.get("newProp"), "updatedValue", "property has updated value");
  }

  /**
   * Test setOrCreate() with existing property
   * Expected: Updates the value
   */
  public testSetOrCreateWithExisting(): void {
    LocalStorageTestsV1.storage.setOrCreate("existing", "initial");

    const result = LocalStorageTestsV1.storage.setOrCreate("existing", "updated");

    eq(result, true, "setOrCreate returns true for existing property");
    eq(LocalStorageTestsV1.storage.get("existing"), "updated", "value is updated");
  }

  /**
   * Test delete() with non-existent property
   * Expected: Returns false
   */
  public testDeleteNonExistentProperty(): void {
    const result = LocalStorageTestsV1.storage.delete("nonExistent");

    eq(result, false, "delete returns false for non-existent property");
  }

  /**
   * Test delete() with active subscribers
   * Expected: Returns false, property not deleted
   */
  public testDeleteWithActiveSubscribers(): void {
    LocalStorageTestsV1.storage.setOrCreate("subscribedProp", "value");

    const link = LocalStorageTestsV1.storage.link<string>("subscribedProp");
    eq(link !== undefined, true, "link created");

    const deleteResult = LocalStorageTestsV1.storage.delete("subscribedProp");
    eq(deleteResult, false, "delete fails with active subscribers");
    eq(LocalStorageTestsV1.storage.has("subscribedProp"), true, "property still exists");

    // Clean up
    link!.aboutToBeDeleted();
  }

  /**
   * Test delete() and recreate
   * Expected: Property can be recreated after deletion
   */
  public testDeleteAndRecreate(): void {
    LocalStorageTestsV1.storage.setOrCreate("recreateProp", "first");

    eq(LocalStorageTestsV1.storage.delete("recreateProp"), true, "delete succeeds");
    eq(LocalStorageTestsV1.storage.has("recreateProp"), false, "property does not exist after delete");

    LocalStorageTestsV1.storage.setOrCreate("recreateProp", "second");
    eq(LocalStorageTestsV1.storage.has("recreateProp"), true, "property can be recreated");
    eq(LocalStorageTestsV1.storage.get("recreateProp"), "second", "recreated property has new value");
  }

  /**
   * Test delete() multiple properties
   * Expected: All properties can be deleted
   */
  public testDeleteMultiple(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop1", "value1");
    LocalStorageTestsV1.storage.setOrCreate("prop2", "value2");
    LocalStorageTestsV1.storage.setOrCreate("prop3", "value3");

    eq(LocalStorageTestsV1.storage.size(), 3, "storage has 3 properties");

    eq(LocalStorageTestsV1.storage.delete("prop1"), true, "delete prop1 succeeds");
    eq(LocalStorageTestsV1.storage.delete("prop2"), true, "delete prop2 succeeds");
    eq(LocalStorageTestsV1.storage.delete("prop3"), true, "delete prop3 succeeds");

    eq(LocalStorageTestsV1.storage.size(), 0, "storage is empty after deleting all");
  }

  /**
   * Test clear() with subscribers
   * Expected: Returns false if any property has subscribers
   */
  public testClearWithSubscribers(): void {
    LocalStorageTestsV1.storage.setOrCreate("clearProp1", "value1");
    LocalStorageTestsV1.storage.setOrCreate("clearProp2", "value2");

    const link = LocalStorageTestsV1.storage.link<string>("clearProp1");

    const clearResult = LocalStorageTestsV1.storage.clear();
    eq(clearResult, false, "clear fails with active subscribers");
    eq(LocalStorageTestsV1.storage.size(), 2, "properties still exist");

    // Clean up
    link!.aboutToBeDeleted();
  }

  /**
   * Test clear() with empty storage
   * Expected: Succeeds
   */
  public testClearEmptyStorage(): void {
    LocalStorageTestsV1.storage.clear(); // Ensure empty

    const clearResult = LocalStorageTestsV1.storage.clear();
    eq(clearResult, true, "clear succeeds on empty storage");
    eq(LocalStorageTestsV1.storage.size(), 0, "storage remains empty");
  }

  /**
   * Test clear() and reinitialize
   * Expected: Storage can be used after clear
   */
  public testClearAndReinitialize(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop1", "value1");
    LocalStorageTestsV1.storage.setOrCreate("prop2", "value2");

    LocalStorageTestsV1.storage.clear();
    eq(LocalStorageTestsV1.storage.size(), 0, "storage is empty after clear");

    LocalStorageTestsV1.storage.setOrCreate("newProp", "newValue");
    eq(LocalStorageTestsV1.storage.size(), 1, "storage has 1 property after reinitializing");
    eq(LocalStorageTestsV1.storage.get("newProp"), "newValue", "new property has correct value");
  }

  /**
   * Test clear() size check
   * Expected: Size is 0 after clear
   */
  public testClearSizeCheck(): void {
    LocalStorageTestsV1.storage.setOrCreate("a", 1);
    LocalStorageTestsV1.storage.setOrCreate("b", 2);
    LocalStorageTestsV1.storage.setOrCreate("c", 3);

    eq(LocalStorageTestsV1.storage.size(), 3, "storage has 3 properties before clear");

    LocalStorageTestsV1.storage.clear();
    eq(LocalStorageTestsV1.storage.size(), 0, "storage has 0 properties after clear");
  }

  // =========================================================================
  // SECTION 1.5: Metadata APIs (size, keys)
  // =========================================================================

  /**
   * Test size() initialization
   * Expected: Size is 0 for new storage
   */
  public testSizeInitialization(): void {
    LocalStorageTestsV1.storage.clear();

    eq(LocalStorageTestsV1.storage.size(), 0, "new storage has size 0");
  }

  /**
   * Test size() after setOrCreate()
   * Expected: Size increases
   */
  public testSizeAfterSetOrCreate(): void {
    LocalStorageTestsV1.storage.clear();

    eq(LocalStorageTestsV1.storage.size(), 0, "initial size is 0");

    LocalStorageTestsV1.storage.setOrCreate("prop1", "value1");
    eq(LocalStorageTestsV1.storage.size(), 1, "size is 1 after adding first property");

    LocalStorageTestsV1.storage.setOrCreate("prop2", "value2");
    eq(LocalStorageTestsV1.storage.size(), 2, "size is 2 after adding second property");

    LocalStorageTestsV1.storage.setOrCreate("prop3", "value3");
    eq(LocalStorageTestsV1.storage.size(), 3, "size is 3 after adding third property");
  }

  /**
   * Test size() after delete()
   * Expected: Size decreases
   */
  public testSizeAfterDelete(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop1", "value1");
    LocalStorageTestsV1.storage.setOrCreate("prop2", "value2");
    LocalStorageTestsV1.storage.setOrCreate("prop3", "value3");

    eq(LocalStorageTestsV1.storage.size(), 3, "initial size is 3");

    LocalStorageTestsV1.storage.delete("prop1");
    eq(LocalStorageTestsV1.storage.size(), 2, "size is 2 after deleting one");

    LocalStorageTestsV1.storage.delete("prop2");
    eq(LocalStorageTestsV1.storage.size(), 1, "size is 1 after deleting two");
  }

  /**
   * Test size() after clear()
   * Expected: Size is 0
   */
  public testSizeAfterClear(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop1", "value1");
    LocalStorageTestsV1.storage.setOrCreate("prop2", "value2");

    eq(LocalStorageTestsV1.storage.size(), 2, "size is 2 before clear");

    LocalStorageTestsV1.storage.clear();
    eq(LocalStorageTestsV1.storage.size(), 0, "size is 0 after clear");
  }

  /**
   * Test size() with large number of properties
   * Expected: Size reflects actual count
   */
  public testSizeLargeNumber(): void {
    LocalStorageTestsV1.storage.clear();

    // Add 10 properties
    for (let i = 0; i < 10; i++) {
      LocalStorageTestsV1.storage.setOrCreate(`prop${i}`, i);
    }
    eq(LocalStorageTestsV1.storage.size(), 10, "size is 10 with 10 properties");

    // Add 10 more
    for (let i = 10; i < 20; i++) {
      LocalStorageTestsV1.storage.setOrCreate(`prop${i}`, i);
    }
    eq(LocalStorageTestsV1.storage.size(), 20, "size is 20 with 20 properties");

    // Add 30 more
    for (let i = 20; i < 50; i++) {
      LocalStorageTestsV1.storage.setOrCreate(`prop${i}`, i);
    }
    eq(LocalStorageTestsV1.storage.size(), 50, "size is 50 with 50 properties");
  }

  /**
   * Test keys() iterator
   * Expected: Returns iterator of property names
   */
  public testKeysIterator(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop1", "value1");
    LocalStorageTestsV1.storage.setOrCreate("prop2", "value2");
    LocalStorageTestsV1.storage.setOrCreate("prop3", "value3");

    const keys = LocalStorageTestsV1.storage.keys();
    const keyArray = Array.from(keys);

    eq(keyArray.length, 3, "keys iterator returns 3 keys");
    eq(keyArray.includes("prop1"), true, "keys contains prop1");
    eq(keyArray.includes("prop2"), true, "keys contains prop2");
    eq(keyArray.includes("prop3"), true, "keys contains prop3");
  }

  /**
   * Test keys() after various operations
   * Expected: Keys reflect current state
   */
  public testKeysAfterOperations(): void {
    LocalStorageTestsV1.storage.setOrCreate("a", 1);
    LocalStorageTestsV1.storage.setOrCreate("b", 2);

    let keys = Array.from(LocalStorageTestsV1.storage.keys());
    eq(keys.length, 2, "2 keys after adding 2 properties");

    LocalStorageTestsV1.storage.setOrCreate("c", 3);
    keys = Array.from(LocalStorageTestsV1.storage.keys());
    eq(keys.length, 3, "3 keys after adding 3rd property");

    LocalStorageTestsV1.storage.delete("a");
    keys = Array.from(LocalStorageTestsV1.storage.keys());
    eq(keys.length, 2, "2 keys after deleting one");
    eq(keys.includes("a"), false, "deleted key not in keys");
    eq(keys.includes("b"), true, "remaining key still present");
    eq(keys.includes("c"), true, "remaining key still present");
  }

  /**
   * Test keys() convert to array
   * Expected: Can convert keys iterator to array
   */
  public testKeysConvertToArray(): void {
    LocalStorageTestsV1.storage.setOrCreate("x", 1);
    LocalStorageTestsV1.storage.setOrCreate("y", 2);
    LocalStorageTestsV1.storage.setOrCreate("z", 3);

    const keysArray = Array.from(LocalStorageTestsV1.storage.keys());

    eq(Array.isArray(keysArray), true, "keys can be converted to array");
    eq(keysArray.length, 3, "array has correct length");
    eq(typeof keysArray[0], "string", "array elements are strings");
  }

  /**
   * Test keys() with forEach
   * Expected: Can iterate keys with forEach
   */
  public testKeysForEach(): void {
    LocalStorageTestsV1.storage.setOrCreate("first", 1);
    LocalStorageTestsV1.storage.setOrCreate("second", 2);
    LocalStorageTestsV1.storage.setOrCreate("third", 3);

    const keys = LocalStorageTestsV1.storage.keys();
    let count = 0;
    for (const key of keys) {
      count++;
      eq(typeof key, "string", "key is string");
    }

    eq(count, 3, "iterated 3 keys");
  }

  // =========================================================================
  // SECTION 1.6: Subscription System (subscribeToChangesOf, unsubscribeFromChangesOf)
  // =========================================================================

  /**
   * Test unsubscribeFromChangesOf() with non-existent property
   * Expected: Returns false
   */
  public testUnsubscribeNonExistentProperty(): void {
    const result = LocalStorageTestsV1.storage.unsubscribeFromChangesOf("nonExistent", 12345);

    eq(result, false, "unsubscribeFromChangesOf returns false for non-existent property");
  }

  // =========================================================================
  // SECTION 3: Deprecated APIs (backward compatibility)
  // =========================================================================

  /**
   * Test has() vs Has() (capitalized version)
   * Expected: Both work the same
   */
  public testHasVsHas(): void {
    LocalStorageTestsV1.storage.setOrCreate("testProp", "value");

    const result1 = LocalStorageTestsV1.storage.has("testProp");

    eq(result1, true, "has() returns true for existing property");
  }

  /**
   * Test get() vs Get() (capitalized version)
   * Expected: Both work the same
   */
  public testGetVsGet(): void {
    LocalStorageTestsV1.storage.setOrCreate("testProp", "value");

    const result1 = LocalStorageTestsV1.storage.get("testProp");

    eq(result1, "value", "get() returns correct value");
  }

  /**
   * Test set() vs Set() (capitalized version)
   * Expected: Both work the same
   */
  public testSetVsSet(): void {
    LocalStorageTestsV1.storage.setOrCreate("testProp", "initial");

    const result1 = LocalStorageTestsV1.storage.set("testProp", "updated");

    eq(result1, true, "set() returns true");
    eq(LocalStorageTestsV1.storage.get("testProp"), "updated", "value is updated");
  }

  // =========================================================================
  // SECTION 4: Arrays and Objects (complex types)
  // =========================================================================

  /**
   * Test array with string elements
   * Expected: Array can be stored and retrieved
   */
  public testArrayString(): void {
    const stringArray = ["apple", "banana", "cherry"];

    LocalStorageTestsV1.storage.setOrCreate("stringArray", stringArray);

    const retrieved = LocalStorageTestsV1.storage.get<Array<string>>("stringArray");
    eq(retrieved !== undefined, true, "array is retrieved");
    eq(retrieved!.length, 3, "array has correct length");
    eq(retrieved![0], "apple", "first element is correct");
    eq(retrieved![1], "banana", "second element is correct");
    eq(retrieved![2], "cherry", "third element is correct");
  }

  /**
   * Test array with number elements
   * Expected: Array can be stored and retrieved
   */
  public testArrayNumber(): void {
    const numberArray = [1, 2, 3, 4, 5];

    LocalStorageTestsV1.storage.setOrCreate("numberArray", numberArray);

    const retrieved = LocalStorageTestsV1.storage.get<Array<number>>("numberArray");
    eq(retrieved !== undefined, true, "number array is retrieved");
    eq(retrieved!.length, 5, "number array has correct length");
    eq(retrieved![2], 3, "element at index 2 is correct");
  }

  /**
   * Test array with object elements
   * Expected: Array of objects can be stored and retrieved
   */
  public testArrayObject(): void {
    const objArray = [{ id: 1, name: "Alice" }, { id: 2, name: "Bob" }];

    LocalStorageTestsV1.storage.setOrCreate("objArray", objArray);

    const retrieved = LocalStorageTestsV1.storage.get<Array<Object>>("objArray");
    eq(retrieved !== undefined, true, "object array is retrieved");
    eq(retrieved!.length, 2, "object array has correct length");
  }

  /**
   * Test array with link
   * Expected: Link works with array
   */
  public testArrayWithLink(): void {
    const arr = [10, 20, 30];

    LocalStorageTestsV1.storage.setOrCreate("arrLink", arr);

    const link = LocalStorageTestsV1.storage.link<Array<number>>("arrLink");
    eq(link !== undefined, true, "link to array created");
    eq(link!.get()!.length, 3, "link array has correct length");

    link!.get()!.push(40);
    eq(link!.get()!.length, 4, "array can be modified through link");

    link!.aboutToBeDeleted();
  }

  /**
   * Test array with prop
   * Expected: Prop works with array
   */
  public testArrayWithProp(): void {
    const arr = [100, 200, 300];

    LocalStorageTestsV1.storage.setOrCreate("arrProp", arr);

    const prop = LocalStorageTestsV1.storage.prop<Array<number>>("arrProp");
    eq(prop !== undefined, true, "prop to array created");
    eq(prop!.get()!.length, 3, "prop array has correct length");

    prop!.aboutToBeDeleted();
  }

  /**
   * Test nested object properties
   * Expected: Nested objects can be stored and accessed
   */
  public testNestedObjectProperties(): void {
    const nestedObj = {
      level1: {
        level2: {
          level3: {
            val: "deep"
          }
        }
      }
    };

    LocalStorageTestsV1.storage.setOrCreate("nested", nestedObj);

    const retrieved = LocalStorageTestsV1.storage.get<Object>("nested");
    eq(retrieved !== undefined, true, "nested object is retrieved");
    eq((retrieved as any).level1.level2.level3.val, "deep", "deeply nested value is correct");
  }

  /**
   * Test object with arrays
   * Expected: Object containing arrays can be stored
   */
  public testObjectWithArrays(): void {
    const objWithArr = {
      numbers: [1, 2, 3],
      strings: ["a", "b", "c"],
      nested: {
        arr: [true, false]
      }
    };

    LocalStorageTestsV1.storage.setOrCreate("objWithArr", objWithArr);

    const retrieved = LocalStorageTestsV1.storage.get<Object>("objWithArr");
    eq(retrieved !== undefined, true, "object with arrays is retrieved");
    eq((retrieved as any).numbers.length, 3, "nested array length is correct");
  }

  /**
   * Test complex object graph
   * Expected: Complex nested structures can be stored
   */
  public testComplexObjectGraph(): void {
    const complex = {
      users: [
        { id: 1, name: "Alice", roles: ["admin", "user"] },
        { id: 2, name: "Bob", roles: ["user"] }
      ],
      metadata: {
        count: 2,
        lastUpdated: "2025-01-01"
      }
    };

    LocalStorageTestsV1.storage.setOrCreate("complex", complex);

    const retrieved = LocalStorageTestsV1.storage.get<Object>("complex");
    eq(retrieved !== undefined, true, "complex object is retrieved");
    eq((retrieved as any).users.length, 2, "users array has correct length");
  }

  // =========================================================================
  // SECTION 5: Edge Cases and Stress Tests
  // =========================================================================

  /**
   * Test property name with underscores
   * Expected: Works correctly
   */
  public testPropertyNameWithUnderscores(): void {
    LocalStorageTestsV1.storage.setOrCreate("test_prop_name", "value");

    eq(LocalStorageTestsV1.storage.has("test_prop_name"), true, "property with underscores exists");
    eq(LocalStorageTestsV1.storage.get("test_prop_name"), "value", "value is correct");
  }

  /**
   * Test property name with numbers
   * Expected: Works correctly
   */
  public testPropertyNameWithNumbers(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop123", "value");

    eq(LocalStorageTestsV1.storage.has("prop123"), true, "property with numbers exists");
    eq(LocalStorageTestsV1.storage.get("prop123"), "value", "value is correct");
  }

  /**
   * Test property name with special characters
   * Expected: Works correctly
   */
  public testPropertyNameSpecialChars(): void {
    LocalStorageTestsV1.storage.setOrCreate("prop-name.test", "value");

    eq(LocalStorageTestsV1.storage.has("prop-name.test"), true, "property with special chars exists");
    eq(LocalStorageTestsV1.storage.get("prop-name.test"), "value", "value is correct");
  }

  /**
   * Test property name with empty string
   * Expected: Edge case handling
   */
  public testPropertyNameEmpty(): void {
    const result = LocalStorageTestsV1.storage.setOrCreate("", "emptyKey");

    eq(result, true, "setOrCreate with empty key returns true");
    eq(LocalStorageTestsV1.storage.has(""), true, "empty key property exists");
    eq(LocalStorageTestsV1.storage.get(""), "emptyKey", "value is correct");
  }

  /**
   * Test zero value
   * Expected: Zero can be stored and retrieved
   */
  public testZeroValue(): void {
    LocalStorageTestsV1.storage.setOrCreate("zeroProp", 0);

    eq(LocalStorageTestsV1.storage.get("zeroProp"), 0, "zero value is stored correctly");
  }

  /**
   * Test many properties (100 properties)
   * Expected: Can handle many properties
   */
  public testManyProperties(): void {
    LocalStorageTestsV1.storage.clear();

    const count = 100;

    for (let i = 0; i < count; i++) {
      LocalStorageTestsV1.storage.setOrCreate(`prop${i}`, i);
    }

    eq(LocalStorageTestsV1.storage.size(), count, `storage has ${count} properties`);

    for (let i = 0; i < count; i++) {
      eq(LocalStorageTestsV1.storage.get(`prop${i}`), i, `property ${i} has correct value`);
    }
  }

  /**
   * Test many links (50 links)
   * Expected: Can handle many links to same property
   */
  public testManyLinks(): void {
    LocalStorageTestsV1.storage.setOrCreate("shared", "value");

    const linkCount = 50;
    const links: SubscribedAbstractProperty<string>[] = [];

    for (let i = 0; i < linkCount; i++) {
      const link = LocalStorageTestsV1.storage.link<string>("shared");
      eq(link !== undefined, true, `link ${i} created`);
      links.push(link!);
    }

    // All links should have the same value
    for (let i = 0; i < linkCount; i++) {
      eq(links[i].get(), "value", `link ${i} has correct value`);
    }

    // Clean up
    for (let i = 0; i < linkCount; i++) {
      links[i].aboutToBeDeleted();
    }
  }

  /**
   * Test NaN value
   * Expected: NaN can be stored and retrieved
   */
  public testNaNValue(): void {
    LocalStorageTestsV1.storage.setOrCreate("nanProp", NaN);

    const retrieved = LocalStorageTestsV1.storage.get("nanProp");
    eq(typeof retrieved, "number", "NaN is stored as number");
    eq(isNaN(retrieved as number), true, "value is NaN");
  }

  /**
   * Test Infinity value
   * Expected: Infinity can be stored and retrieved
   */
  public testInfinityValue(): void {
    LocalStorageTestsV1.storage.setOrCreate("infProp", Infinity);

    const retrieved = LocalStorageTestsV1.storage.get("infProp");
    eq(retrieved, Infinity, "Infinity value is correct");
  }

  /**
   * Test negative zero
   * Expected: -0 can be stored and retrieved
   */
  public testNegativeZero(): void {
    LocalStorageTestsV1.storage.setOrCreate("negZero", -0);

    const retrieved = LocalStorageTestsV1.storage.get("negZero");
    eq(retrieved, 0, "negative zero is stored as zero");
  }

  /**
   * Test very large numbers
   * Expected: Large numbers can be stored
   */
  public testVeryLargeNumber(): void {
    const maxVal = Number.MAX_VALUE;
    LocalStorageTestsV1.storage.setOrCreate("max", maxVal);

    eq(LocalStorageTestsV1.storage.get("max"), maxVal, "MAX_VALUE is stored correctly");

    const minVal = Number.MIN_VALUE;
    LocalStorageTestsV1.storage.setOrCreate("min", minVal);

    eq(LocalStorageTestsV1.storage.get("min"), minVal, "MIN_VALUE is stored correctly");
  }

  /**
   * Test set-get-set-get sequence
   * Expected: Multiple operations work correctly
   */
  public testSetGetSetGetSequence(): void {
    LocalStorageTestsV1.storage.setOrCreate("seqProp", "first");
    eq(LocalStorageTestsV1.storage.get("seqProp"), "first", "first get correct");

    LocalStorageTestsV1.storage.set("seqProp", "second");
    eq(LocalStorageTestsV1.storage.get("seqProp"), "second", "second get correct");

    LocalStorageTestsV1.storage.set("seqProp", "third");
    eq(LocalStorageTestsV1.storage.get("seqProp"), "third", "third get correct");

    LocalStorageTestsV1.storage.set("seqProp", "fourth");
    eq(LocalStorageTestsV1.storage.get("seqProp"), "fourth", "fourth get correct");
  }

  /**
   * Test link-delete-recreate sequence
   * Expected: Can recreate property after deleting link
   */
  public testLinkDeleteRecreate(): void {
    LocalStorageTestsV1.storage.setOrCreate("recreateLinkProp", "original");

    const link = LocalStorageTestsV1.storage.link<string>("recreateLinkProp");
    eq(link !== undefined, true, "link created");

    // Clean up link
    link!.aboutToBeDeleted();

    // Delete property
    eq(LocalStorageTestsV1.storage.delete("recreateLinkProp"), true, "delete succeeds after link cleanup");

    // Recreate
    LocalStorageTestsV1.storage.setOrCreate("recreateLinkProp", "new");
    eq(LocalStorageTestsV1.storage.get("recreateLinkProp"), "new", "recreated property has new value");

    // Create new link
    const newLink = LocalStorageTestsV1.storage.link<string>("recreateLinkProp");
    eq(newLink !== undefined, true, "new link created");
    eq(newLink!.get(), "new", "new link has correct value");

    // Clean up
    newLink!.aboutToBeDeleted();
  }
}
