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

class SynchedPropertySimpleOneWayPU<T> extends ObservedPropertySimpleAbstractPU<T> {

  private wrappedValue_: T;
  private source_: ObservedPropertyAbstract<T>;

  constructor(source: ObservedPropertyAbstract<T>, subscribeMe?: IPropertySubscriber, info?: PropertyInfo) {
    super(subscribeMe, info);
    // add a test here that T is a simple type
    // subscribe to receive value chnage updates from source.
    this.source_ = source;
    this.source_.subscribeMe(this);

    // use own backing store for value to avoid
    // value changes to be propagated back to source
    this.wrappedValue_ = source.getUnmonitored();
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


  // this object is subscriber to  source
  // when source notifies a change, copy its value to local backing store
  hasChanged(newValue: T): void {
    console.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: hasChanged to '${newValue}'.`)
    this.wrappedValue_ = this.source_.getUnmonitored();
    this.notifyHasChanged(newValue);
  }

  public getUnmonitored(): T {
    console.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}' .`);
    // unmonitored get access , no call to otifyPropertyRead !
    return this.wrappedValue_;
  }

  // get 'read through` from the ObservedProperty
  public get(): T {
    console.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: get returns '${this.wrappedValue_}'`);
    this.notifyPropertyRead();
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ == newValue) {
      console.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set with unchanged value '${this.wrappedValue_}'- ignoring.`);
      return;
    }

    console.debug(`SynchedPropertySimpleOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set from '${this.wrappedValue_} to '${newValue}'.`);
    this.wrappedValue_ = newValue;
    this.notifyHasChanged(newValue);
  }
}

