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

import { eq, gt, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class Utils {
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
  static currentAppApiVersion: number;
}

declare class PUV2ViewBase {
  protected get isViewV2(): boolean;
}

declare class ViewPU extends PUV2ViewBase{
  public debugInfoStateVars(): string;
  declareWatch(propStr: string, callback: (propName: string) => void): void;
  watchedProps: Map<string, (propName: string) => void>;
  get localStorage_(): LocalStorage;
  set localStorage_(instance: LocalStorage);
  get isViewV2(): boolean;

  // Add more

}

@Observed
class TestClass {
  testVar1 : number = 0;
  constructor(){

  }
}

declare abstract class ObservedPropertyAbstract<T> {

}

declare class LocalStorage extends NativeLocalStorage {
  protected storage_: Map<string, ObservedPropertyAbstract<any>>;

  static getShared(): LocalStorage;

  constructor(initializingProperties?: Object);

  initializeProps(initializingProperties?: Object): void;

  size(): number;

  get<T>(propName: string): T | undefined;

  set<T>(propName: string, newValue: T): boolean;

  setOrCreate<T>(propName: string, newValue: T): boolean;

  delete(propName: string): boolean;

  clear(): boolean;

  subscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean;

  unsubscribeFromChangesOf(propName: string, subscriberId: number): boolean;
}

declare class NativeLocalStorage {
  constructor();
  static GetShared(): LocalStorage;
}


/**
 * Singleton class SubscriberManager implements IPropertySubscriberLookup
 * public API to manage IPropertySubscriber
 */
declare class SubscriberManager {
  private subscriberById_;
  private static instance_;
  private static nextId_;
  private static finalizationRegistry_;
  /**
   * check subscriber is known
   * same as ES6 Map.prototype.has()
   *
   * @since 9
   */
  static Has(id: number): boolean;
  /**
   *
   * retrieve subscriber by id
   * same as ES6 Map.prototype.get()
   *
   *  @since 9
   */
  static Find(id: number): IPropertySubscriber;
  /**
   * unregister a subscriber
   * same as ES6 Map.prototype.delete()
   * @return boolean success or failure to delete
   *
   *  @since 9
   */
  static Delete(id: number): boolean;
  /**
   * add a new subscriber.
   * The subscriber must have a new (unused) id (@see MakeId() )
   * for add() to succeed.
   * same as Map.prototype.set()
   *
   *  @since 9
   */
  static Add(newSubsriber: IPropertySubscriber): boolean;
  /**
   * Update recycle custom node element id.
   */
  static UpdateRecycleElmtId(oldId: number, newId: number): boolean;
  /**
   *
   * @returns a globally unique id to be assigned to a IPropertySubscriber objet
   * Use MakeId() to assign a IPropertySubscriber object an id before calling @see add() .
   *
   *  @since 9
   */
  static MakeId(): number;
  /**
   *
   * @returns a global unique id for state variables.
   * Unlike MakeId, no need to get id from native side.
   *
   * @since 12
   */
  static MakeStateVariableId(): number;
  /**
   * Check number of registered Subscriber / registered IDs.
   * @returns number of registered unique ids.
   *
   *  @since 9
   */
  static NumberOfSubscribers(): number;
  /**
   *
   * internal (non-SDK) methods below
   *
   */
  /**
   * Get singleton, create it on first call
   * @returns SubscriberManager singleton
   *
   * internal function
   * This function will be removed soon, use static functions instead!
   * Note: Function gets used by transpiler output for both full update and partial update
   */
  static Get(): SubscriberManager;
  /**
   * Get singleton, create it on first call
   * @returns SubscriberManager singleton
   *
   * internal function
   */
  private static GetInstance;
  /**
   * for debug purposes dump all known subscriber's info to comsole
   *
   * not a public / sdk function
   */
  static DumpSubscriberInfo(): void;
  /**
   * not a public / sdk function
   * @see Has
   */
  has(id: number): boolean;
  /**
   * not a public / sdk function
   * @see Get
   */
  get(id: number): IPropertySubscriber;
  /**
   * not a public / sdk function
   * @see Delete
   */
  delete(id: number): boolean;
  /**
   * not a public / sdk function
   * @see Add
   */
  add(newSubscriber: IPropertySubscriber): boolean;
  private set;
  updateRecycleElmtId(oldId: number, newId: number): boolean;
  /**
   * Method for testing purposes
   * @returns number of subscribers
   *
   * not a public / sdk function
   */
  numberOfSubscribers(): number;
  /**
   * for debug purposes dump all known subscriber's info to comsole
   *
   * not a public / sdk function
   */
  dumpSubscriberInfo(): void;
  /**
   *
   * @returns a globally unique id to be assigned to a Subscriber
   */
  makeId(): number;
  /**
   * SubscriberManager is a singleton created by the framework
   * do not use
   *
   * internal method
   */
  private constructor();
}

interface IPropertySubscriber {
  id__(): number;
  /**
   *  inform the subscribed property
   * that the subscriber is about to be deleted
   * hence , unsubscribe
   */
  aboutToBeDeleted(owningView?: IPropertySubscriber): void;
}
/**
 * The ISinglePropertyChangeSubscriber<T> describes an
 * instance that subscribes to a source that manages a single app state property.
 * That instances expects to receive hasChanged() events with the new property value.
 * This property is of type T.
 */
interface ISinglePropertyChangeSubscriber<T> extends IPropertySubscriber {
  /**
   * get informed after the property has changed.
   */
  hasChanged(newValue: T): void;
}

export class LocalStorageTest1 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll(): void {}

  // Executed before every invidual tests. Can be empty
  public beforeEach(): void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}

  public getId(): string {
    return this.idString;
  }

  /// -- Test cases

  /* Test several functions of LocalStorage
  * Calls:
   setOrCreate
   clear
   size
  */
  public localStorageCreateAndClear(): void {

    eq((this as any as ViewPU).localStorage_.setOrCreate<boolean>("aBool", false), true, 'Test creation');
    eq((this as any as ViewPU).localStorage_.size(), 1, 'Size before clear')
    eq((this as any as ViewPU).localStorage_.clear(), true, 'Test clear');
    eq((this as any as ViewPU).localStorage_.size(), 0, 'Size after  clear')

  }

  /* Test several functions of LocalStorage
  * Calls:
   setOrCreate
   subscribeToChangesOf
   unsubscribeFromChangesOf
  */
  public localStorageBasicFuncs(): void {
    class TestSubscriber<C> implements ISinglePropertyChangeSubscriber<C> {
      private id_: number = SubscriberManager.MakeId();
      private label_: string;

      constructor(label: string) {
        SubscriberManager.Add(this);
        this.label_ = label;
      }

      // globally unique id
      id__(): number {
        return this.id_;
      }

      // inform the subscribed property
      // that the subscriber is about to be deleted
      // hence , unsubscribe
      aboutToBeDeleted(): void {
        console.log(`TestSubscriber aboutTOBeDeleted`);
        SubscriberManager.Delete(this.id__());
      }

      // TODO: Does not trigger
      hasChanged(newValue: C): void {
        console.log(`TestSubscriber '${this.label_}' property changed value (shown stringified): '${JSON.stringify(newValue)}' `);
      }
    }
    let boolChangeListener = new TestSubscriber<boolean>("boolChangeListener");

    // Must create before subscribeToChangesOf
    eq((this as any as ViewPU).localStorage_.setOrCreate<boolean>("aBool", false), true, 'Test creation');
    eq((this as any as ViewPU).localStorage_.subscribeToChangesOf("aBool", boolChangeListener), true, 'Test subscribe changes');
    eq((this as any as ViewPU).localStorage_.unsubscribeFromChangesOf("aBool", boolChangeListener.id__()), true, 'Test unsubscribe');
  }

  // TODO Add more tests
}