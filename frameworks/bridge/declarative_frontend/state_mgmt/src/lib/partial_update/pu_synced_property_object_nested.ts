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

class SynchedPropertyNesedObjectPU<C extends Object>
  extends ObservedPropertyObjectAbstractPU<C>
  implements ISinglePropertyChangeSubscriber<C> {

  private obsObject_: C;

  /**
   * Construct a Property of a su component that links to a variable of parent view that holds an ObservedObject
   * example
   *   this.b.$a with b of type PC and a of type C, or
   *   this.$b[5] with this.b of type PC and array item b[5] of type C;
   *
   * @param subscribeMe
   * @param propName
   */
  constructor(obsObject: C,
    owningChildView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningChildView, propertyName);
    this.obsObject_ = obsObject;

    // register to the ObservedObject
    ObservedObject.addOwningProperty(this.obsObject_, this);
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    // unregister from the ObservedObject
    ObservedObject.removeOwningProperty(this.obsObject_, this);
    super.aboutToBeDeleted();
  }


  // this object is subscriber to ObservedObject
  // will call this cb function when property has changed
  hasChanged(newValue: C): void {
    console.debug(`SynchedPropertyNesedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: contained ObservedObject hasChanged'.`)
    this.notifyHasChanged(this.obsObject_);
  }


  public getUnmonitored(): C {
    // console.debug(`SynchedPropertyNesedObject[${this.id()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}' .`);
    // unmonitored get access , no call to otifyPropertyRead !
    return this.obsObject_;
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    console.debug(`SynchedPropertyNesedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: get`)
    this.notifyPropertyRead();
    return this.obsObject_;
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.obsObject_ == newValue) {
      console.debug(`SynchedPropertyNesedObjectPu[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
      return;
    }

    console.debug(`SynchedPropertyNesedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);

    // unsubscribe from the old value ObservedObject
    ObservedObject.removeOwningProperty(this.obsObject_, this);

    this.obsObject_ = newValue;

    // subscribe to the new value ObservedObject
    ObservedObject.addOwningProperty(this.obsObject_, this);

    // notify value change to subscribing View
    this.notifyHasChanged(this.obsObject_);
  }
}
