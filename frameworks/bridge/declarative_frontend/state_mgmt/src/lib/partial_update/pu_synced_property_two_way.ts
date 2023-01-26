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
 * SynchedPropertyTwoWayPU
 * implementation of @Link and @Consume decorated variables of all types  and undefined.
 * 
 * all definitions in this file are framework internal
 */
class SynchedPropertyTwoWayPU<C extends Object> extends ObservedPropertyAbstractPU<C> {

  private source_: ObservedPropertyObjectAbstract<C>;
    
  constructor(source: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);
    if (source) {
      // register to the parent property
      this.source_ = source;
      this.source_.subscribeMe(this);
    }
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    if (this.source_ !== undefined) {
      this.source_.unlinkSuscriber(this.id__())
      this.source_ = undefined;
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
      stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: propertyHasChangedPU: contained ObservedObject '${eventSource.info()}' hasChanged'.`)
      this.notifyPropertryHasChangedPU();
  }

  /**
   * called when wrapped ObservedObject has changed poperty
   * @param souceObject 
   * @param changedPropertyName 
   */

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

  // set 'writes through` to source_ ObservedPropertyPU or parent SynchedPropertyOne/TwoWay
  public set(newValue: C): void {
    if (!this.source_) {
      stateMgmtConsole.error(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: set, no linked parent property.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);

    // if value changed then 'this' syncPeerHasChanged will be called
    this.source_.set(newValue);
  }
}


// backward compatibility

class SynchedPropertyObjectTwoWayPU<C extends Object> extends SynchedPropertyTwoWayPU<C> {
  constructor(source: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(source, owningChildView, thisPropertyName);
  }
}

class SynchedPropertySimpleTwoWayPU<S> extends SynchedPropertyTwoWayPU<S> {
  constructor(source: ObservedPropertyAbstract<S>, owningView: IPropertySubscriber, owningViewPropNme: PropertyInfo) {
    super(source, owningView, owningViewPropNme)
  }
}
