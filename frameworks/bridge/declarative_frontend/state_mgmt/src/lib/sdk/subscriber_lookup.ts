/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

/**
 * Singleton class SubscriberManager implements IPropertySubscriberLookup 
 * public API to manage IPropertySubscriber
 */

class SubscriberManager {

  private subscriberById_: Map<number, IPropertySubscriber>;

  private static instance_: SubscriberManager;

  private static nextId_: number = 0;

  /**
    * check subscriber is known
    * same as ES6 Map.prototype.has()
    * 
    * @since 9
    */
  public static Has(id: number): boolean {
    return SubscriberManager.GetInstance().has(id);
  }

  /**
   * 
   * retrieve subscriber by id
   * same as ES6 Map.prototype.get()
   * 
   *  @since 9
   */
  public static Find(id: number): IPropertySubscriber {
    return SubscriberManager.GetInstance().get(id);
  }

  /**
   * unregister a subscriber
   * same as ES6 Map.prototype.delete()
   * @return boolean success or failure to delete
   * 
   *  @since 9
   */
  public static Delete(id: number): boolean {
    return SubscriberManager.GetInstance().delete(id);
  }

  /**
  * add a new subscriber.
  * The subscriber must have a new (unused) id (@see MakeId() )
  * for add() to succeed.
  * same as Map.prototype.set()
  * 
  *  @since 9
  */
  public static Add(newSubsriber: IPropertySubscriber): boolean {
    return SubscriberManager.GetInstance().add(newSubsriber);
  }

  /**
   * Update recycle custom node element id.
   */
  public static UpdateRecycleElmtId(oldId: number, newId: number): boolean {
    return SubscriberManager.GetInstance().updateRecycleElmtId(oldId, newId);
  }

  /**
  * 
  * @returns a globally unique id to be assigned to a IPropertySubscriber objet
  * Use MakeId() to assign a IPropertySubscriber object an id before calling @see add() .
  * 
  *  @since 9
 */
  public static MakeId(): number {
    return SubscriberManager.GetInstance().makeId();
  }

  /**
   * 
   * @returns a global unique id for state variables.
   * Unlike MakeId, no need to get id from native side.
   * 
   * @since 12
   */
  public static MakeStateVariableId(): number {
    return SubscriberManager.nextId_--;
  }

  /**
   * Check number of registered Subscriber / registered IDs.
   * @returns number of registered unique ids.
   * 
   *  @since 9
   */

  public static NumberOfSubscribers(): number {
    return SubscriberManager.GetInstance().numberOfSubscribers();
  }

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
   * Note: Fnction gets used by transpiler output for both full update and partial update
   */
   public static Get() : SubscriberManager {
    if (!SubscriberManager.instance_) {
      SubscriberManager.instance_ = new SubscriberManager();
    }
    return SubscriberManager.instance_;
   }

  /**
   * Get singleton, create it on first call
   * @returns SubscriberManager singleton
   * 
   * internal function
   */
  private static GetInstance() : SubscriberManager {
    if (!SubscriberManager.instance_) {
      SubscriberManager.instance_ = new SubscriberManager();
    }
    return SubscriberManager.instance_;
  }

  /**
   * for debug purposes dump all known subscriber's info to comsole
   * 
   * not a public / sdk function
   */
  public static DumpSubscriberInfo(): void {
    SubscriberManager.GetInstance().dumpSubscriberInfo();
  }

  /**
   * not a public / sdk function
   * @see Has
   */
  public has(id: number): boolean {
    return this.subscriberById_.has(id);
  }

  /**
   * not a public / sdk function
   * @see Get
   */
  public get(id: number): IPropertySubscriber {
    return this.subscriberById_.get(id);
  }

  /**
 * not a public / sdk function
 * @see Delete
 */
  public delete(id: number): boolean {
    if (!this.has(id)) {
      stateMgmtConsole.warn(`SubscriberManager.delete unknown id ${id} `);
      return false;
    }
    return this.subscriberById_.delete(id);
  }

  /**
 * not a public / sdk function
 * @see Add
 */
  public add(newSubsriber: IPropertySubscriber): boolean {
    if (this.has(newSubsriber.id__())) {
      return false;
    }
    this.subscriberById_.set(newSubsriber.id__(), newSubsriber);
    return true;
  }

  public updateRecycleElmtId(oldId: number, newId: number): boolean {
    if (!this.has(oldId)) {
      return false;
    }
    const subscriber = this.get(oldId);
    this.subscriberById_.delete(oldId);
    this.subscriberById_.set(newId, subscriber);
    return true;
  }

  /**
   * Method for testing purposes
   * @returns number of subscribers
   * 
   * not a public / sdk function
   */
  public numberOfSubscribers(): number {
    return this.subscriberById_.size;
  }

  /**
   * for debug purposes dump all known subscriber's info to comsole
   * 
   * not a public / sdk function
   */
  public dumpSubscriberInfo(): void {
    stateMgmtConsole.debug('Dump of SubscriberManager +++ (sart)');
    for (let [id, subscriber] of this.subscriberById_) {
      stateMgmtConsole.debug(`Id: ${id} -> ${subscriber['info'] ? subscriber['info']() : 'unknown'}`);
    }
    stateMgmtConsole.debug('Dump of SubscriberManager +++ (end)');
  }

  /**
   * 
   * @returns a globally unique id to be assigned to a Subscriber
   */
  makeId(): number {
    return ViewStackProcessor.MakeUniqueId();
  }

  /**
   * SubscriberManager is a singleton created by the framework
   * do not use
   * 
   * internal method
   */
  private constructor() {
    this.subscriberById_ = new Map<number, IPropertySubscriber>();
    stateMgmtConsole.debug('SubscriberManager has been created.');
  }
}
