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

class SynchedPropertySimpleTwoWayPU<T> extends ObservedPropertySimpleAbstractPU<T>
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
    this.source_.unlinkSuscriber(this.id__());
    this.source_ = undefined;
    super.aboutToBeDeleted();
  }

  // this object is subscriber to  SynchedPropertySimpleTwoWayPU
  // will call this cb function when property has changed
  // a set (newValue) is not done because get reads through for the source_
  hasChanged(newValue: T): void {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: hasChanged to '${newValue}'.`)
      this.notifyHasChanged(newValue);
    }
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored`);
    return this.source_.getUnmonitored();
  }

  // get 'read through` from the ObservedProperty
  public get(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: get`);
    this.notifyPropertyRead();
    return this.source_.getUnmonitored();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: T): void {
    if (this.source_.get() == newValue) {
      stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);

    // avoid circular notifications @Link -> source @State -> other but also to same @Link
    this.changeNotificationIsOngoing_ = true;

    // the source_ ObservedProeprty will call: this.hasChanged(newValue);
    this.source_.set(newValue);
    this.notifyHasChanged(newValue);

    this.changeNotificationIsOngoing_ = false;
  }
}
