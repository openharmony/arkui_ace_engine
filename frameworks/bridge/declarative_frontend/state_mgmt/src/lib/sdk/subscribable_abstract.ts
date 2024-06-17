/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * 
 * SubscribableAbstract
 * 
 * This class is part of the SDK.
 * @since 10
 * 
 * SubscribableAbstract is an abstract class that manages subscribers 
 * to value changes. These subscribers are the implementation of 
 * @State, @Link, @Provide, @Consume decorated variables inside the 
 * framework. Each using @State, @Link, etc., decorated variable in 
 * a @Component will make its own subscription. When the component 
 * is created the subscription is added, and before the component 
 * is deleted it unsubscribes
 * 
 * An application may extend SubscribableAbstract for a custom class 
 * that manages state data. @State, @Link, @Provide, @Consume 
 * decorated variables can hold an Object that is instance of 
 * SubscribableAbstract.
 * 
 * About lifecycle: It is legal use for two @Components with two @State
 * decorated variables to share the same SubscribableAbstract object.
 * Each such decorated variable implementation makes its own
 * subscription to the SubscribableAbstract object. Hence, when both variables
 * have unsubscribed the SubscribableAbstract custom class may do its own 
 * de-initialization, e.g. release held external resources.
 *
 * How to extend:
 * A subclass manages the get and set to one or several properties on its own.
 * The subclass needs to notify all relevant value changes to the framework for the
 * UI to be updated. Notification should only be given for class properties that
 * are used to generate the UI.
 *
 * A subclass must call super() in its constructor to let this base class
 * initialize itself.
 *
 * A subclass must call 'notifyPropertyHasChanged*(' after the relevant property
 * has changes. The framework will notify all dependent components to re-render.
 *
 * A sub-class may overwrite the 'addOwningProperty' function to add own
 * functionality, but it must call super.addowningOwningProperty(..). E.g.
 * the sub-class could connect to external resources upon the first subscriber.
 *
 * A sub-class may also overwrite the 'removeOwningProperty' function or
 * 'removeOwningPropertyById' function to add own functionality,
 * but it must call super.removeOwningProperty(..).
 * E.g. the sub-class could release held external resources upon loosing the
 * last subscriber.
 *
 */

abstract class SubscribableAbstract {

  // keeps track of all subscribing properties
  private owningProperties_: Set<number>;

  /**
   * make sure to call super() from subclass constructor!
   * 
   * @since 10
   */
  constructor() {
    this.owningProperties_ = new Set<number>();
    stateMgmtConsole.debug(`SubscribableAbstract: construcstor done`);
  }

  /**
  * A subsclass must call this function whenever one of its properties has
   * changed that is used to construct the UI.
   * @param propName name of the change property
   * @param newValue the property value after the change
   * 
   * @since 10
   */
  protected notifyPropertyHasChanged(propName: string, newValue: any) {
    stateMgmtConsole.debug(`SubscribableAbstract: notifyPropertyHasChanged '${propName}'.`);
    this.owningProperties_.forEach((subscribedId) => {
      let owningProperty: IPropertySubscriber = SubscriberManager.Find(subscribedId);
      if (!owningProperty) {
        stateMgmtConsole.error(`SubscribableAbstract: notifyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
        return;
      }

      // PU code path
      if ('onTrackedObjectPropertyCompatModeHasChangedPU' in owningProperty) {
        (owningProperty as unknown as ObservedObjectEventsPUReceiver<any>).onTrackedObjectPropertyCompatModeHasChangedPU(this, propName);
      }
      
      // FU code path
      if ('hasChanged' in owningProperty) {
        (owningProperty as ISinglePropertyChangeSubscriber<any>).hasChanged(newValue);
      }
      if ('propertyHasChanged' in owningProperty) {
        (owningProperty as IMultiPropertiesChangeSubscriber).propertyHasChanged(propName);
      }
    });
  }

  /**
   * Provides the current number of subscribers.
   * Application may use this function to determine a shared object has no more remaining subscribers and can be deleted.
   * @returns number of current subscribers
   * 
   * @since 10
   */
  public numberOfSubscribers(): number {
    return this.owningProperties_.size;
  }

  /**
   * Method used by the framework to add subscribing decorated variables
   * Subclass may overwrite this function but must call the function of the base
   * class from its own implementation.
   * @param subscriber new subscriber that implements ISinglePropertyChangeSubscriber
   * and/or IMultiPropertiesChangeSubscriber interfaces
   * 
   * @since 10
   */

  public addOwningProperty(subscriber: IPropertySubscriber): void {
    stateMgmtConsole.debug(`SubscribableAbstract: addOwningProperty: subscriber '${subscriber.id__()}'.`);
    this.owningProperties_.add(subscriber.id__());
  }

  /**
   * Method used by the framework to unsubscribing decorated variables
   * Subclass may overwrite this function but must call the function of the base
   * class from its own implementation.
   * @param subscriber subscriber that implements ISinglePropertyChangeSubscriber
   * and/or IMultiPropertiesChangeSubscriber interfaces
   * 
   * @since 10
   */
  public removeOwningProperty(property: IPropertySubscriber): void {
    return this.removeOwningPropertyById(property.id__());
  }

  /**
   * Same as @see removeOwningProperty() but by Subscriber id.
   * @param subscriberId 
  * 
   * framework internal function, not to be used by applications.
   */
  public removeOwningPropertyById(subscriberId: number): void {
    stateMgmtConsole.debug(`SubscribableAbstract: removeOwningProperty '${subscriberId}'.`);
    this.owningProperties_.delete(subscriberId);
  }

  /**
   * flush all subscribers / owning properties
   * This is needed when copying a SubscribableAbstract object to the localObject or @prop / SynchedPropertyObjectOneWay
   * - shallowCopy: copies the _reference to original_ Set. Hence, we must not modify this Set but assign a new Set
   * - deepCopy also (deep-) copies this class' owningProperties_ Set, incl. the numbers it includes. Assigning a new Set fixes.
   * 
   */
  public clearOwningProperties() {
    this.owningProperties_ = new Set<number>();
  }
}

/**
 *  SubscribaleAbstract class with typo in its nam,e
 * 
 * @depreciated, use SubscribableAbstract
 */

abstract class SubscribaleAbstract extends SubscribableAbstract {
}
