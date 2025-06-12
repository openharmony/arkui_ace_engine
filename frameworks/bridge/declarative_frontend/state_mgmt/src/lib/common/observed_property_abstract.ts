/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
 * ObservedPropertyAbstract base class for the implementation o all state variables
 * Its base class SubscribedAbstractProperty<T> provides all public / SDK functions.
 * 
 * This class and all other definitons in this file are framework 
 * internal / non-SDK.
 * 
 */

type SynchedPropertyFactoryFunc = <T>(source: ObservedPropertyAbstract<T>) => ObservedPropertyAbstract<T>;

/*
   manage subscriptions to a property
   managing the property is left to sub
   classes
   Extended by ObservedProperty, SyncedPropertyOneWay
   and SyncedPropertyTwoWay
*/
abstract class ObservedPropertyAbstract<T> extends SubscribedAbstractProperty<T> implements AbstractProperty<T> {
  protected subscribers_: Set<number>;
  private id_: number;
  protected info_?: PropertyInfo;
  protected isFake_: boolean = false;
  constructor(subscribeMe?: IPropertySubscriber, info?: PropertyInfo) {
    super();
    this.subscribers_ = new Set<number>();
    this.id_ = SubscriberManager.MakeStateVariableId();
    SubscriberManager.Add(this);
    if (subscribeMe) {
      this.subscribers_.add(subscribeMe.id__());
    }
    if (info) {
      this.info_ = info;
    }
  }

  aboutToBeDeleted() {
    SubscriberManager.Delete(this.id__());
  }

  id__(): number {
    return this.id_;
  }

  public info(): PropertyInfo {
    return this.info_;
  }

  public setInfo(propName: PropertyInfo) {
    if (propName && propName !== '') {
      this.info_ = propName;
    }
  }

  public __isFake_ObservedPropertyAbstract_Internal(): boolean {
    return this.isFake_;
  }

  public __setIsFake_ObservedPropertyAbstract_Internal(isFake: boolean): void {
    this.isFake_ = isFake;
  }

  // Partial Update "*PU" classes will overwrite
  public getUnmonitored(): T {
    return this.get();
  }

  // update the element id for recycle custom component
  public updateElmtId(oldElmtId: number, newElmtId: number): void {
    if (this.subscribers_.has(oldElmtId)) {
      this.subscribers_.delete(oldElmtId);
      this.subscribers_.add(newElmtId);
    }
  }

  // Method name is used to check object is of type ObservedPropertyAbstract
  // Do NOT override in derived classed, use addSubscriber
  public subscribeMe(subscriber: ISinglePropertyChangeSubscriber<T>): void {
    stateMgmtConsole.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || 'unknown'}']: subscribeMe: Property new subscriber '${subscriber.id__()}'`);
    this.subscribers_.add(subscriber.id__());
  }

  /*
    the inverse function of createOneWaySync or createTwoWaySync
    Do NOT override in derived classed, use removeSubscriber
  */
  public unlinkSuscriber(subscriberId: number): void {
    this.subscribers_.delete(subscriberId);
  }

  /*
    Virtualized version of the subscription mechanism - add subscriber
  */
  public addSubscriber(subscriber: ISinglePropertyChangeSubscriber<T>):void {
    if (subscriber) {
      this.subscribeMe(subscriber);
    }
  }

  /*
    Virtualized version of the subscription mechanism - remove subscriber
  */
  public removeSubscriber(subscriber: IPropertySubscriber, id?: number):void {
    if (id) {
      this.unlinkSuscriber(id);
    } else if (subscriber) {
      this.unlinkSuscriber(subscriber.id__());
    }
  }

  // FU code path callback
  protected notifyHasChanged(newValue: T) {
    stateMgmtProfiler.begin('ObservedPropertyAbstract.notifyHasChanged');
    stateMgmtConsole.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || 'unknown'}']: notifyHasChanged, notifying.`);
    this.subscribers_.forEach((subscribedId) => {
      let subscriber: IPropertySubscriber = SubscriberManager.Find(subscribedId);
      if (subscriber) {
        // FU code path
        if ('hasChanged' in subscriber) {
          (subscriber as ISinglePropertyChangeSubscriber<T>).hasChanged(newValue);
        }
        if ('propertyHasChanged' in subscriber) {
          (subscriber as IMultiPropertiesChangeSubscriber).propertyHasChanged(this.info_);
        }
      } else {
        stateMgmtConsole.warn(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || 'unknown'}']: notifyHasChanged: unknown subscriber ID '${subscribedId}' error!`);
      }
    });
    stateMgmtProfiler.end();
  }

  protected notifyPropertyRead() {
    stateMgmtProfiler.begin('ObservedPropertyAbstract.notifyPropertyRead');
    stateMgmtConsole.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || 'unknown'}']: propertyRead.`);
    this.subscribers_.forEach((subscribedId) => {
      var subscriber: IPropertySubscriber = SubscriberManager.Find(subscribedId)
      if (subscriber) {
        if ('propertyRead' in subscriber) {
          (subscriber as IMultiPropertiesReadSubscriber).propertyRead(this.info_);
        }
      }
    });
    stateMgmtProfiler.end();
  }

  /*
  return numebr of subscribers to this property
  mostly useful for unit testin
  */
  public numberOfSubscrbers(): number {
    return this.subscribers_.size;
  }


  /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   * 
   * These functions are depreciated and will be removed
   * these are replaced with createSync
   */
  public abstract createLink(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<T>;
  public abstract createProp(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<T>;

  /**
   * provide a factory function that creates a SynchedPropertyXXXX of choice
   * that uses 'this' as source 
   * @param factoryFunc 
   * @returns 
   */
  public createSync(factoryFunc: SynchedPropertyFactoryFunc): ObservedPropertyAbstract<T> {
    return factoryFunc<T>(this);
  }

  /**
   * depreciated SDK function, not used anywhere by the framework
   */
  public createTwoWaySync(subscribeMe?: IPropertySubscriber, info?: string): SubscribedAbstractProperty<T> {
    stateMgmtConsole.warn("Using depreciated method 'createTwoWaySync'!");
    return this.createLink(subscribeMe, info);
  }

  /**
   * depreciated SDK function, not used anywhere by the framework
   */
  public createOneWaySync(subscribeMe?: IPropertySubscriber, info?: string): SubscribedAbstractProperty<T> {
    stateMgmtConsole.warn("Using depreciated method 'createOneWaySync' !");
    return this.createProp(subscribeMe, info);
  }

  /**
   * factory function for concrete 'object' or 'simple' ObservedProperty object
   * depending if value is Class object
   * or simple type (boolean | number | string)
   * @param value
   * @param owningView
   * @param thisPropertyName
   * @returns either
   */
  static CreateObservedObject<C>(value: C, owningView: IPropertySubscriber, thisPropertyName: PropertyInfo)
    : ObservedPropertyAbstract<C> {
    return (typeof value === 'object') ?
      new ObservedPropertyObject(value, owningView, thisPropertyName)
      : new ObservedPropertySimple(value, owningView, thisPropertyName);
  }
}
