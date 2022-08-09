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

/*
  Overview of the Observed Property class hiararchy

  ObservedPropertyAbstract
     |-- ObservedSimplePropertyAbstract - boolean, number, string
     |         |-- ObservedSimpleProperty - owns the property
     |         |-- SynchedSimplePropertyOneWay - one way sync from ObservedSimpleProperty
     |         |        |--SynchedPropertySimpleOneWaySubscribing - one way sync
     |         |           from ObservedSimpleProperty, return value of AppStorage.prop(..)
     |         |-- SynchedSimplePropertyTwoWay - two way sync with ObservedSimpleProperty
     |
     |-- ObservedObjectPropertyAbstract - Object proxied by ObservedObject
               |-- ObservedObjectProperty - owns the property
               |-- SynchedObjectPropertyTwoWay - two way sync with ObservedObjectProperty

*/

/*
   manage subscriptions to a property
   managing the property is left to sub
   classes
   Extended by ObservedProperty, SyncedPropertyOneWay
   and SyncedPropertyTwoWay
*/
abstract class ObservedPropertyAbstract<T>  {
  protected subscribers_: Set<number>
  private id_: number;
  private info_?: PropertyInfo;

  // indicates if the perperty has changed
  // settting the flag to true at startup implies 
  // that any delayed initialization in View.setInitiallyProvidedValue()
  // will _not_ trigger any change notifcations to subscribers.
  //  markDependentElementsIsPending will be set to false in (initial) render() function
  // hence, from this moment, the first change will be notified to subscribers
  private markDependentElementsIsPending: boolean = false;
  private dependentElementIds_: Set<number> = new Set<number>();

  constructor(subscribeMe?: IPropertySubscriber, info?: PropertyInfo) {
    this.subscribers_ = new Set<number>();
    this.id_ = SubscriberManager.Get().MakeId();
    SubscriberManager.Get().add(this);
    if (subscribeMe) {
      this.subscribers_.add(subscribeMe.id__());
    }
    if (info) {
      this.info_ = info;
    }
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__())
  }

  id__(): number {
    return this.id_;
  }

  public info(): PropertyInfo {
    return this.info_;
  }
  public setInfo(propName: PropertyInfo) {
    if (propName && propName != "") {
      this.info_ = propName;
    }
  }

  // get property and notify 'get' access
  public abstract get(): T;

  // get property, do not notify 'get' access
  public abstract getUnmonitored(): T;

  // set property to new value and notify
  // 'set' access
  public abstract set(newValue: T): void;

  // subscribe to 'get' and/or 'set' access notifications of this property
  // what is notified depends on availability of callback funcs of the subscribing object
  // typically used with Views. Do not use for creating Link or Prop relatinships
  public subscribeMe(subscriber: ISinglePropertyChangeSubscriber<T>): void {
    console.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: subscribeMe: Property new subscriber '${subscriber.id__()}'`);
    this.subscribers_.add(subscriber.id__());
  }

  /*
    the inverse function of createOneWaySync or createTwoWaySync
  */
  public unlinkSuscriber(subscriberId: number): void {
    this.subscribers_.delete(subscriberId);
  }

  protected notifyHasChanged(newValue: T) {
    console.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyHasChanged, dependent elmtIds [${Array.from(this.dependentElementIds_)}].`);
    console.debug(`   ... notifying ${this.subscribers_.size} subscribers (these might not all be 'set' access subscribers).`);
    var registry: IPropertySubscriberLookup = SubscriberManager.Get();
    this.subscribers_.forEach((subscribedId) => {
      var subscriber: IPropertySubscriber = registry!.get(subscribedId)
      if (subscriber) {
        if ('hasChanged' in subscriber) {
          (subscriber as ISinglePropertyChangeSubscriber<T>).hasChanged(newValue);
        }
        if ('propertyHasChanged' in subscriber) {
          (subscriber as IMultiPropertiesChangeSubscriber).propertyHasChanged(this.info_);
        }
      } else {
        console.error(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyHasChanged: unknown subscriber ID '${subscribedId}' error!`);
      }
    });

    // for properties owned by a View"
    // markDependentElementsDirty needs to be executed
    this.markDependentElementsIsPending = true;
  }

  protected notifyPropertyRead() {
    console.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: propertyRead.`)
    var registry: IPropertySubscriberLookup = SubscriberManager.Get();
    this.subscribers_.forEach((subscribedId) => {
      var subscriber: IPropertySubscriber = registry!.get(subscribedId)
      if (subscriber) {
        if ('propertyRead' in subscriber) {
          (subscriber as IMultiPropertiesReadSubscriber).propertyRead(this.info_);
        }
      }
    });
    this.recordDependentUpdate();
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
   */
  public abstract createLink(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<T>;
  public abstract createProp(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<T>;

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
    return (typeof value === "object") ?
      new ObservedPropertyObject(value, owningView, thisPropertyName)
      : new ObservedPropertySimple(value, owningView, thisPropertyName);
  }


  /**
   * during 'get' access recording take note of the created component and its elmtId
   * and add this component to the list of components who are dependent on this property
   */
  protected recordDependentUpdate() {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    if (elmtId < 0) {
      // not access recording 
      return;
    }
    console.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: recordDependentUpdate on elmtId ${elmtId}.`)
    this.dependentElementIds_.add(elmtId);
  }

  public markDependentElementsDirty(view: View) {
    if (!this.markDependentElementsIsPending) {
      return;
    }
    if (this.dependentElementIds_.size > 0) {
      console.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']:markDependentElementsDirty`);
      this.dependentElementIds_.forEach(elmtId => {
        view.markElemenDirtyById(elmtId)
        console.debug(`   - elmtId ${elmtId}.`);
      });
    }
    this.markDependentElementsIsPending = false;
  }

  public purgeDependencyOnElmtId(rmElmtId: ElementIdOnSecondRender): void {
    console.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']:purgeDependencyOnElmtId ${rmElmtId}`);
    this.dependentElementIds_.delete(rmElmtId);
  }

  public SetPropertyUnchanged() : void {
    // function to be removed
    // keep it here until transpiler is updated.
  }
}
