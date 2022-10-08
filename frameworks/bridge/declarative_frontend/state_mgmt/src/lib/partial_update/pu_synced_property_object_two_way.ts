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

class SynchedPropertyObjectTwoWayPU<C extends Object>
  extends ObservedPropertyObjectAbstractPU<C>
  implements ISinglePropertyChangeSubscriber<C> {

  private linkedParentProperty_: ObservedPropertyObjectAbstract<C>;
  private changeNotificationIsOngoing_: boolean = false;
    
  constructor(linkSource: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);
    this.linkedParentProperty_ = linkSource;
    // register to the parent property
    this.linkedParentProperty_.subscribeMe(this);

    // register to the ObservedObject
    ObservedObject.addOwningProperty(this.linkedParentProperty_.get(), this);
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    // unregister from parent of this link
    this.linkedParentProperty_.unlinkSuscriber(this.id__());

    // unregister from the ObservedObject
    ObservedObject.removeOwningProperty(this.linkedParentProperty_.getUnmonitored(), this);
    super.aboutToBeDeleted();
  }

  private setObject(newValue: C): void {
    this.linkedParentProperty_.set(newValue)
  }

  // this object is subscriber to ObservedObject
  // will call this cb function when property has changed
  hasChanged(newValue: C): void {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: contained ObservedObject hasChanged'.`)
      this.notifyHasChanged(this.linkedParentProperty_.getUnmonitored());
    }
  }


  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.linkedParentProperty_.getUnmonitored())}' .`);
    // unmonitored get access , no call to otifyPropertyRead !
    return this.linkedParentProperty_.getUnmonitored();
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: get`)
    this.notifyPropertyRead();
    return this.linkedParentProperty_.getUnmonitored();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.linkedParentProperty_.getUnmonitored() == newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);

    ObservedObject.removeOwningProperty(this.linkedParentProperty_.getUnmonitored(), this);
    
    // avoid circular notifications @Link -> source @State -> other but also back to same @Link
    this.changeNotificationIsOngoing_ = true;
    this.setObject(newValue);
    ObservedObject.addOwningProperty(this.linkedParentProperty_.getUnmonitored(), this);
    this.notifyHasChanged(newValue);
    this.changeNotificationIsOngoing_ = false;
  }
}
