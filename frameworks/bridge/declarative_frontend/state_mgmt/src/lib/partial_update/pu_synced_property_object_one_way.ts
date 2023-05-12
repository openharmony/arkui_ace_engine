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
 * SynchedPropertyObjectOneWayPU
 * implementatio  of @Prop decorated variables of type class object
 * 
 * all definitions in this file are framework internal
 * 
 */


type SyncSourceHasChangedCb<T> = (source : ObservedPropertyAbstract<T>) => void;

class SynchedPropertyObjectOneWayPU<C extends Object>
  extends ObservedPropertyObjectAbstractPU<C>
  implements PeerChangeEventReceiverPU<C>,
  ObservedObjectEventsPUReceiver<C> {

  private wrappedValue_: C;
  private source_: ObservedPropertyAbstract<C>;

  // true for @Prop code path, 
  // false for @(Local)StorageProp
  private sourceIsOwnObject : boolean;

  constructor(source: ObservedPropertyAbstract<C> | C,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);

    if (source && (typeof (source) === "object") && ("subscribeMe" in source)) {
      // code path for @(Local)StorageProp, the souce is a ObservedPropertyObject in aLocalStorage)
      this.source_ = source as ObservedPropertyAbstractPU<C>;
      this.sourceIsOwnObject = false;
      // subscribe to receive value change updates from LocalStorage source property
      this.source_.subscribeMe(this);
    } else {
      // code path for @Prop
      if (!ObservedObject.IsObservedObject(source)) {
        stateMgmtConsole.warn(`@Prop ${this.info()}  Provided source object's class 
           lacks @Observed class decorator. Object property changes will not be observed.`);
      }
      stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor @Prop wrapping source in a new ObservedPropertyObjectPU`);
      this.source_ = new ObservedPropertyObjectPU<C>(source as C, this, thisPropertyName);
      this.sourceIsOwnObject = true;
    }

    // deep copy source Object and wrap it
    this.setWrappedValue(this.source_.get());

    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor ready with wrappedValue '${JSON.stringify(this.wrappedValue_)}'.`);
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    if (this.source_) {
      this.source_.unlinkSuscriber(this.id__());
      if (this.sourceIsOwnObject == true && this.source_.numberOfSubscrbers()==0){
        stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: aboutToBeDeleted. owning source_ ObservedPropertySimplePU, calling its aboutToBeDeleted`);
        this.source_.aboutToBeDeleted();
     }

      this.source_ = undefined;
    }
    super.aboutToBeDeleted();
  }

  public syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<C>) {
    if (eventSource && this.source_ == eventSource) {
      // defensive programming: should always be the case!
      stateMgmtConsole.debug(`SynchedPropertyNesedObjectPU[${this.id__()}]: syncPeerHasChanged(): Source '${eventSource.info()}' has changed'.`)
      const newValue = this.source_.getUnmonitored();
      if (typeof newValue == "object") {
        stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: hasChanged:  newValue '${JSON.stringify(newValue)}'.`);
        this.setWrappedValue(newValue);
        this.notifyPropertyHasChangedPU();
      }
    } else {
      stateMgmtConsole.warn(`SynchedPropertyNesedObjectPU[${this.id__()}]: syncPeerHasChanged Unexpected situation. Ignorning event.`)
    }
  }

  /**
   * event emited by wrapped ObservedObject, when one of its property values changes
   * @param souceObject 
   * @param changedPropertyName 
   */
  public objectPropertyHasChangedPU(souceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
        objectPropertyHasChangedPU: contained ObservedObject property '${changedPropertyName}' has changed.`)
    this.notifyPropertyHasChangedPU();
  }

  public objectPropertyHasBeenReadPU(souceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
    objectPropertyHasBeenReadPU: contained ObservedObject property '${changedPropertyName}' has been read.`);
    this.notifyPropertyHasBeenReadPU();
  }

  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}'.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  // get 'read through` from the ObservedObject
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: get returning ${JSON.stringify(this.wrappedValue_)}.`)
    this.notifyPropertyHasBeenReadPU()
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

    this.setWrappedValue(newValue);
    this.notifyPropertyHasChangedPU();
  }

  public reset(sourceChangedValue: C): void {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: reset from '${JSON.stringify(this.wrappedValue_)}' to '${JSON.stringify(sourceChangedValue)}'.`);
    // if set causes an actual change, then, ObservedPropertyObject source_ will call syncPeerHasChanged
    this.source_.set(sourceChangedValue);
  }

  private setWrappedValue(value: C): void {
    let rawValue = ObservedObject.GetRawObject(value);
    let copy: C;
    
    // FIXME: Proper object deep copy missing here!
    if (rawValue instanceof Array) {
      copy = ObservedObject.createNew([ ...rawValue ], this) as unknown as C;
    } else {
      copy = ObservedObject.createNew({ ...rawValue }, this);
    }
    Object.setPrototypeOf(copy, Object.getPrototypeOf(rawValue));
    ObservedObject.addOwningProperty(this.wrappedValue_, this);
    this.wrappedValue_ = copy;
  }
}
