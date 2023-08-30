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

class SynchedPropertyTwoWayPU<C> extends ObservedPropertyAbstractPU<C>
  implements PeerChangeEventReceiverPU<C>, ObservedObjectEventsPUReceiver<C> {

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
    } else {
      throw new SyntaxError(`${this.debugInfo()}: constructor: source variable in parent/ancestor @Component must be defined. Application error!`);
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

  public debugInfoDecorator() : string {
    return `@Link/@Consume (class SynchedPropertyTwoWayPU)`;
  }

  private isStorageLinkProp() : boolean {
    return  (this.source_ && this.source_ instanceof ObservedPropertyAbstract && (!(this.source_ instanceof ObservedPropertyAbstractPU)));
  }

  private setObject(newValue: C): void {
    if (!this.source_) {
      throw new SyntaxError(`${this.debugInfo()}: setObject (assign a new value), no source variable in parent/ancestor \
                                                    @Component. Application error.`);

    }

    if (this.getUnmonitored() === newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value - ignoring.`);
      return;
    }

    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: set: value has changed.`);

    if (this.checkIsSupportedValue(newValue)) {
    // the source_ ObservedProperty will call: this.syncPeerHasChanged(newValue);
    this.source_.set(newValue)
    }
  }


  /**
   * Called when sync peer ObservedPropertyObject or SynchedPropertyObjectTwoWay has changed value
   * that peer can be in either parent or child component if 'this' is used for a @Link
   * that peer can be in either ancestor or descendant component if 'this' is used for a @Consume
   * @param eventSource 
   */
  syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<C>) {
    if (!this.changeNotificationIsOngoing_) {
      stateMgmtConsole.debug(`${this.debugInfo()}: syncPeerHasChanged: from peer '${eventSource && eventSource.debugInfo && eventSource.debugInfo()}' .`)
      this.notifyPropertyHasChangedPU();
    }
  }

  /**
   * called when wrapped ObservedObject has changed poperty
   * @param souceObject 
   * @param changedPropertyName 
   */
  public objectPropertyHasChangedPU(sourceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`${this.debugInfo()}: objectPropertyHasChangedPU: property '${changedPropertyName}' of \
    object value has changed.`)
    
    this.notifyPropertyHasChangedPU();
  }

  public objectPropertyHasBeenReadPU(sourceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`${this.debugInfo()}: objectPropertyHasBeenReadPU: property '${changedPropertyName}' of object value has been read.`);
    this.notifyPropertyHasBeenReadPU();
  }

  public getUnmonitored(): C {
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: getUnmonitored.`);
    // unmonitored get access , no call to otifyPropertyRead !
    return (this.source_ ? this.source_.getUnmonitored() : undefined);
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get`)
    this.notifyPropertyHasBeenReadPU()
    return this.getUnmonitored();
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.getUnmonitored() === newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value  - nothing to do.`);
      return;
    }

    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: set: value about to change.`);
    
    // avoid circular notifications @Link -> source @State -> other but also back to same @Link
    this.changeNotificationIsOngoing_ = true;
    this.setObject(newValue);
    this.notifyPropertyHasChangedPU();
    this.changeNotificationIsOngoing_ = false;
  }
}

// class definitions for backward compatibility
class SynchedPropertyObjectTwoWayPU<C> extends SynchedPropertyTwoWayPU<C> {

}

class SynchedPropertySimpleTwoWayPU<T> extends SynchedPropertyTwoWayPU<T> {
  
}

