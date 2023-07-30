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
  extends ObservedPropertyObjectAbstractPU<C>
  implements PeerChangeEventReceiverPU<C>,
  ObservedObjectEventsPUReceiver<C> {

  private source_: ObservedPropertyObjectAbstract<C>;
  private changeNotificationIsOngoing_: boolean = false;
        
  constructor(source: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);
    this.source_ = source;
    if (this.source_) {
      // register to the parent property
      this.source_.addSubscriber(this);
      // register to the ObservedObject
      ObservedObject.addOwningProperty(this.source_.getUnmonitored(), this);
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
      this.source_.removeSubscriber(this);

        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.source_.getUnmonitored(), this);
    }
    super.aboutToBeDeleted();
  }

  private isStorageLinkProp() : boolean {
    return  (this.source_ && this.source_ instanceof ObservedPropertyAbstract && (!(this.source_ instanceof ObservedPropertyAbstractPU)));
  }

  private setObject(newValue: C): void {
    if (!this.source_) {
        stateMgmtConsole.warn(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: setObject (assign a new value), @Link/@Consume: no linked parent property. Likely a consequence of earlier application error.`);
        return;
    }

    let oldValueObject = this.getUnmonitored();
    if (oldValueObject != undefined && oldValueObject != null) {
      ObservedObject.removeOwningProperty(oldValueObject, this);
    }
    this.source_.set(newValue)
    ObservedObject.addOwningProperty(this.getUnmonitored(), this);
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
      this.notifyPropertyHasChangedPU();
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
    this.notifyPropertyHasChangedPU();
  }

  public objectPropertyHasBeenReadPU(souceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
    objectPropertyHasBeenReadPU: contained ObservedObject property '${changedPropertyName}' has been read.`);
    this.notifyPropertyHasBeenReadPU();
  }

  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored.`);
    // unmonitored get access , no call to otifyPropertyRead !
    return (this.source_ ? this.source_.getUnmonitored() : undefined);
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: get`)
    this.notifyPropertyHasBeenReadPU()
    return this.getUnmonitored();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.getUnmonitored() == newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value  - nothing to do.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);
    
    // avoid circular notifications @Link -> source @State -> other but also back to same @Link
    this.changeNotificationIsOngoing_ = true;
    this.setObject(newValue);
    this.notifyPropertyHasChangedPU();
    this.changeNotificationIsOngoing_ = false;
  }
}
