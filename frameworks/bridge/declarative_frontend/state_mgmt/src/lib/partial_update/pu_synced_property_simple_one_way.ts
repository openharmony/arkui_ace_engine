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

class SynchedPropertySimpleOneWayPU<T> extends ObservedPropertySimpleAbstractPU<T> {

  private wrappedValue_: T;
  private source_: ObservedPropertyAbstract<T>;

  constructor(source: ObservedPropertyAbstract<T> | T, subscribeMe?: IPropertySubscriber, thisPropertyName?: PropertyInfo) {
    super(subscribeMe, thisPropertyName)

    if (source == undefined) {
      stateMgmtConsole.log(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor @Prop source undefined.`);
      this.source_ = undefined;
      return;
    }

    if ((typeof (source) === "object") && ("notifyHasChanged" in source) && ("subscribeMe" in source)) {
      // code path for @(Local)StorageProp
      this.source_ = source as ObservedPropertyAbstract<T>;
      // subscribe to receive value chnage updates from LocalStorge source property
      this.source_.subscribeMe(this);
    } else {
      // code path for @Prop
      this.source_ = new ObservedPropertySimplePU<T>(source as T, this, thisPropertyName);
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
      this.source_.unlinkSuscriber(this.id__());
      this.source_ = undefined;
    }
    super.aboutToBeDeleted();
  }

  public syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<T>) {
    if (this.source_ == undefined) {
      stateMgmtConsole.warn(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
       syncPeerHasChanged peer '${eventSource ? eventSource.info() : "no eventSource info"}' but source_ undefned. Internal error.`);
      return;
    }

    if (eventSource && (eventSource == this.source_)) {
      // defensive, should always be the case
      stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
       syncPeerHasChanged peer '${eventSource.info()}'.`);
       this.setWrappedValue(eventSource.getUnmonitored());
       this.notifyPropertryHasChangedPU();
       }
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}' .`);
    // unmonitored get access , no call to otifyPropertyRead !
    return this.wrappedValue_;
  }

  // get 'read through` from the ObservedProperty
  public get(): T {
    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: get returns '${this.wrappedValue_}'`);
    this.notifyPropertryHasBeenReadPU()
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ == newValue) {
      stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set with unchanged value '${this.wrappedValue_}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set from '${this.wrappedValue_} to '${newValue}'.`);
    this.setWrappedValue(newValue);
    this.notifyPropertryHasChangedPU();
  }

  public reset(sourceChangedValue: T): void {
    stateMgmtConsole.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: reset from '${this.wrappedValue_} to '${sourceChangedValue}'.`);
    if (this.source_ !== undefined) {
      // if set causes an actual change, then, ObservedPropertySimple source_ will call hasChanged
      this.source_.set(sourceChangedValue);
    }
  }

  private setWrappedValue(newValue: T): void {
    this.wrappedValue_ = newValue;
  }
}

