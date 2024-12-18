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
 * SynchedPropertySimpleTwoWay
 * 
 * all definitions in this file are framework internal
 */
class SynchedPropertySimpleTwoWay<T> extends ObservedPropertySimpleAbstract<T>
  implements ISinglePropertyChangeSubscriber<T> {

  private source_: ObservedPropertyAbstract<T>;
  private changeNotificationIsOngoing_: boolean = false;

  constructor(source: ObservedPropertyAbstract<T>, owningView: IPropertySubscriber, owningViewPropNme: PropertyInfo) {
    super(owningView, owningViewPropNme);
    this.source_ = source;
    this.source_.subscribeMe(this);
  }

  /*
  like a destructor, need to call this before deleting
  the property.
*/
  aboutToBeDeleted() {
    if (this.source_) {
        this.source_.unlinkSuscriber(this.id__());
        this.source_ = undefined;
    }
    super.aboutToBeDeleted();
  }

  // this object is subscriber to  SynchedPropertySimpleTwoWay
  // will call this cb function when property has changed
  // a set (newValue) is not done because get reads through for the source_
  hasChanged(newValue: T): void {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`SynchedPropertySimpleTwoWay[${this.id__()}, '${this.info() || 'unknown'}']: hasChanged to '${newValue}'.`);
      this.notifyHasChanged(newValue);
    }
  }

  // get 'read through` from the ObservedProperty
  public get(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}']: get`);
    if (!this.source_) {
      stateMgmtConsole.error(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}'] source_ is undefined: get value is undefined.`);
      return undefined;
    }
    this.notifyPropertyRead();
    return this.source_.get();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: T): void {
    if (!this.source_) {
      stateMgmtConsole.error(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}'] source_ is undefined: set new value ignoring.`);
      return;
    }
    if (this.source_.get() === newValue) {
      stateMgmtConsole.debug(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}']: set to newValue: '${newValue}'.`);
    // the source_ ObservedProeprty will call: this.hasChanged(newValue);
    // the purpose of the changeNotificationIsOngoing_ is to avoid 
    // circular notifications @Link -> source @State -> other but alos same @Link
    this.changeNotificationIsOngoing_ = true;
    this.source_.set(newValue);
    this.notifyHasChanged(newValue);
    this.changeNotificationIsOngoing_ = false;
  }

  /**
* These functions are meant for use in connection with the App Stoage and
* business logic implementation.
* the created Link and Prop will update when 'this' property value
* changes.
*/
  public createLink(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstract<T> {
    return new SynchedPropertySimpleTwoWay(this, subscribeOwner, linkPropName);
  }

  public createProp(subscribeOwner?: IPropertySubscriber,
    propPropName?: PropertyInfo): ObservedPropertyAbstract<T> {
    return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, propPropName);
  }

}
