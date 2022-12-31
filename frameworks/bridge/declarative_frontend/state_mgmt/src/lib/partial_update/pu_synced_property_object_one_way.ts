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

class SynchedPropertyObjectOneWayPU<C extends Object>
  extends ObservedPropertyObjectAbstractPU<C>
  implements ISinglePropertyChangeSubscriber<C>, IMultiPropertiesChangeSubscriber {

  private wrappedValue_: C;
  private source_: ObservedPropertyAbstract<C>;

  constructor(source: ObservedPropertyAbstract<C> | C,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);

    if (source && (typeof (source) === "object") && ("notifyHasChanged" in source) && ("subscribeMe" in source)) {
      // code path for @(Local)StorageProp
      this.source_ = source as ObservedPropertyAbstract<C>;
      // subscribe to receive value change updates from LocalStorage source property
      this.source_.subscribeMe(this);
    } else {
      // code path for @Prop
      if (!ObservedObject.IsObservedObject(source)) {
        stateMgmtConsole.warn(`@Prop ${this.info()}  Provided source object's class 
           lacks @Observed class decorator. Object property changes will not be observed.`);
      }

      this.source_ = new ObservedPropertyObjectPU<C>(source as C, this, thisPropertyName);
    }

    // deep copy source Object and wrap it
    this.setWrapperValue(this.source_.get());
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor ready with wrappedValue '${JSON.stringify(this.wrappedValue_)}'.`);
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


  // this object is subscriber to this.source_
  // when source notifies a property change, copy its value to local backing store
  // the guard for newValue being an Object is needed because also property changes of wrappedValue_ 
  // are notified via this function. We ignore those, these are handled correctly by propertyHasChanged
  public hasChanged(newValue: C): void {
    if (typeof newValue == "object") {
      stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: hasChanged:  newValue '${JSON.stringify(newValue)}'.`);
      this.setWrapperValue(newValue);
      this.notifyHasChanged(ObservedObject.GetRawObject(this.wrappedValue_));
    }
  }

  public propertyHasChanged(propName : string) : void {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: propertyHasChanged '${propName}'.`);
    this.notifyHasChanged(ObservedObject.GetRawObject(this.wrappedValue_));
  }

  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}'.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  // get 'read through` from the ObservedObject
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: get returning ${JSON.stringify(this.wrappedValue_)}.`)
    this.notifyPropertyRead();
    return this.wrappedValue_;
  }

  // assignment to local variable in the form of this.aProp = <object value>
  // set 'writes through` to the ObservedObject
  public set(newValue: C): void {
    if (this.wrappedValue_ == newValue) {
      stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}IP, '${this.info() || "unknown"}']: set with unchanged value '${JSON.stringify(newValue)}'- ignoring.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: set to newValue: '${JSON.stringify(newValue)}'.`);
    if (!ObservedObject.IsObservedObject(newValue)) {
      stateMgmtConsole.warn(`@Prop ${this.info()} Set: Provided new object's class 
         lacks @Observed class decorator. Object property changes will not be observed.`);
    }

    this.setWrapperValue(newValue);
    this.notifyHasChanged(this.wrappedValue_);
  }

  public reset(sourceChangedValue: C): void {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: reset from '${JSON.stringify(this.wrappedValue_)}' to '${JSON.stringify(sourceChangedValue)}'.`);
    // if set causes an actual change, then, ObservedPropertyObject source_ will call hasChanged
    this.source_.set(sourceChangedValue);
  }

  private setWrapperValue(value: C): void {
    let rawValue = ObservedObject.GetRawObject(value);
    if (rawValue instanceof Array) {
      this.wrappedValue_ = ObservedObject.createNew([ ...rawValue ], this);
    } else {
      this.wrappedValue_ = ObservedObject.createNew({ ...rawValue }, this);
    }
  }
}
