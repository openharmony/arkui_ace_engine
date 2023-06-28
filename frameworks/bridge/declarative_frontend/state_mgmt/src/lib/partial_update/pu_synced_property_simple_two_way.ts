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
 * SynchedPropertySimpleTwoWayPU
 * implementation of @Link and @Consume decorated variables of types boolean | number | string | enum
 *
 * all definitions in this file are framework internal
 */

class SynchedPropertySimpleTwoWayPU<T> extends ObservedPropertySimpleAbstractPU<T>
  implements PeerChangeEventReceiverPU<T> {

  private source_: ObservedPropertyAbstract<T>;
  private changeNotificationIsOngoing_: boolean = false;

  constructor(source: ObservedPropertyAbstract<T>, owningView: IPropertySubscriber, owningViewPropNme: PropertyInfo) {
    super(owningView, owningViewPropNme);
    this.source_ = source;
    if (this.source_) {
      this.source_.addSubscriber(this);
    } else {
      stateMgmtConsole.error(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor @Link/@Consume source must not be undefined. Application error!`);
    }
  }

  /*
  like a destructor, need to call this before deleting
  the property.
*/
  aboutToBeDeleted() {
    if (this.source_) {
        this.source_.removeSubscriber(this);
        this.source_ = undefined;
    }
    super.aboutToBeDeleted();
  }

  /**
   * Called when sync peer ObservedPropertySimple or SynchedPropertySimpletTwoWay has chnaged value
   * that peer can be in either parent or child component if 'this' is used for a @Link
   * that peer can be in either acestor or descendant component if 'this' is used for a @Consume
   * @param eventSource 
   */
  syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<T>) {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: propertyHasChangedPU, property ${eventSource.info()}`);
      this.notifyPropertyHasChangedPU();
    }
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored`);
    return (this.source_ ? this.source_.getUnmonitored() : undefined);
  }

  // get 'read through` from the ObservedProperty
  public get(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: get`);
    this.notifyPropertyHasBeenReadPU()
    return this.getUnmonitored();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: T): void {
    if (!this.source_) {
        stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set, no source, returning.`);
        return;
    }

    if (this.source_.get() == newValue) {
      stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertySimpleTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);

    // avoid circular notifications @Link -> source @State -> other but also to same @Link
    this.changeNotificationIsOngoing_ = true;

    // the source_ ObservedProeprty will call: this.hasChanged(newValue);
    this.source_.set(newValue);
    this.notifyPropertyHasChangedPU();

    this.changeNotificationIsOngoing_ = false;
  }
}
