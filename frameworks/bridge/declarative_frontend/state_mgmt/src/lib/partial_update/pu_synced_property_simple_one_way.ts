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
 * SynchedPropertySimpleOneWayPU
 * implementation of @Prop decorated variable of types boolean | number | string | enum
 * 
 * all definitions in this file are framework internal
 */

class SynchedPropertySimpleOneWayPU<T> extends ObservedPropertySimpleAbstractPU<T>
  implements PeerChangeEventReceiverPU<T>  {

  private wrappedValue_: T;
  private source_: ObservedPropertyAbstract<T>;

  // true for @Prop code path, 
  // false for @(Local)StorageProp
  private sourceIsOwnObject: boolean;

  constructor(source: ObservedPropertyAbstract<T> | T, subscribeMe?: IPropertySubscriber, thisPropertyName?: PropertyInfo) {
    super(subscribeMe, thisPropertyName);

    // Check that source is ObservedPropertyAbstruct
    if (source && (typeof (source) === "object") && ("notifyHasChanged" in source) && ("subscribeMe" in source)) {
      // code path for @(Local)StorageProp
      this.source_ = source;
      this.sourceIsOwnObject = false;
      this.source_.addSubscriber(this);
      // subscribe to receive value change updates from LocalStorage source property
    } else {
      // code path for @Prop
      this.source_ = new ObservedPropertySimplePU<T>(source as T, this, thisPropertyName);
      this.sourceIsOwnObject = true;
    }

    // use own backing store for value to avoid
    // value changes to be propagated back to source
    this.wrappedValue_ = this.source_.getUnmonitored();
  }

  /*
    like a destructor, need to call this before deleting
    the property.
  */
  aboutToBeDeleted() {
    if (this.source_) {
      this.source_.removeSubscriber(this);
      if (this.sourceIsOwnObject == true && this.source_.numberOfSubscrbers()==0){
         stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: aboutToBeDeleted. owning source_ ObservedPropertySimplePU, calling its aboutToBeDeleted`);
         this.source_.aboutToBeDeleted();
      }
      this.source_ = undefined;
      this.sourceIsOwnObject= false;
    }
    super.aboutToBeDeleted();
  }

  public syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<T>) {  
    if (eventSource && (eventSource == this.source_)) {
      // defensive, should always be the case
      stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
       syncPeerHasChanged peer '${eventSource.info()}'.`);
       this.setWrappedValue(eventSource.getUnmonitored());
       this.notifyPropertyHasChangedPU();
       }
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored.`);
    // unmonitored get access, no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  // get 'read through` from the ObservedProperty
  public get(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: get returns '${this.wrappedValue_}'`);
    this.notifyPropertyHasBeenReadPU()
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ == newValue) {
      stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set with unchanged value '${this.wrappedValue_}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set from '${this.wrappedValue_} to '${newValue}'.`);
    this.setWrappedValue(newValue);
    this.notifyPropertyHasChangedPU();
  }

  public reset(sourceChangedValue: T): void {
    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: reset from '${this.wrappedValue_} to '${sourceChangedValue}'.`);
    // if set causes an actual change, then, ObservedPropertySimple source_ will call hasChanged
    if (this.source_ !== undefined) {
      // if set causes an actual change, then, ObservedPropertySimple source_ will call hasChanged
      this.source_.set(sourceChangedValue);
    }
  }

  private setWrappedValue(newValue: T): void {
    this.wrappedValue_ = newValue;
  }
}

