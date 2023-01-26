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
 * SynchedPropertyObjectTwoWayPU
 * implementation of @Link and @Consume decorated variables of type class object
 * 
 * all definitions in this file are framework internal
 */
class SynchedPropertyObjectTwoWayPU<C extends Object>
  extends ObservedPropertyObjectAbstractPU<C> {

  private source_: ObservedPropertyObjectAbstract<C>;
  private changeNotificationIsOngoing_: boolean = false;
    
  constructor(source: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);
    if (source) {
      // register to the parent property
      this.source_ = source;
      this.source_.subscribeMe(this);

    // register to the ObservedObject
    ObservedObject.addOwningProperty(this.source_.get(), this);
    } else {
      stateMgmtConsole.error(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor @Link/@Consume source must not be undefined. Application error!`);
    }
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    // unregister from parent of this link
    if (this.source_) {
        this.source_.unlinkSuscriber(this.id__());
    
        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.source_.getUnmonitored(), this);
    }
    super.aboutToBeDeleted();
  }

  /**
   * Called when sync peer ObservedPropertyObject or SynchedPropertyObjectTwoWay has chnaged value
   * that peer can be in either parent or child component if 'this' is used for a @Link
   * that peer can be in either acestor or descendant component if 'this' is used for a @Consume
   * @param eventSource 
   */
  syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<C>) {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: propertyHasChangedPU: contained ObservedObject '${eventSource.info()}' hasChanged'.`)
      this.notifyPropertryHasChangedPU();
    }
  }

  /**
   * called when wrapped ObservedObject has changed poperty
   * @param souceObject 
   * @param changedPropertyName 
   */
  public objectPropertyHasChangedPU(souceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
        objectPropertyHasChangedPU: contained ObservedObject property '${changedPropertyName}' has changed.`)
    this.notifyPropertryHasChangedPU();
  }


  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${(this.source_ ? JSON.stringify(this.source_.getUnmonitored()) : "undefined")}' .`);
    // unmonitored get access , no call to otifyPropertyRead !
    return (this.source_ ? this.source_.getUnmonitored() : undefined);
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: get`)
    this.notifyPropertryHasBeenReadPU()
    return this.getUnmonitored();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.getUnmonitored() == newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);
    
    // avoid circular notifications @Link -> source @State -> other but also back to same @Link
    this.changeNotificationIsOngoing_ = true;
    this.setObject(newValue);
    ObservedObject.addOwningProperty(this.getUnmonitored(), this);
    this.notifyPropertryHasChangedPU();
    this.changeNotificationIsOngoing_ = false;
  }

  private setObject(newValue: C): void {
    if (!this.source_) {
        stateMgmtConsole.warn(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: setObject, no linked parent property.`);
        return;
    }

    let oldValueObject = this.getUnmonitored();
    if (oldValueObject) {
      ObservedObject.removeOwningProperty(oldValueObject, this);
    }
    this.source_.set(newValue)
  }
}
