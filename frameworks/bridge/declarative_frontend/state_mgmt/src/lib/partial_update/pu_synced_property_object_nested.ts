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
 * SynchedPropertyNestedObjectPU
 * implementation of @ObjectLink decorated variables
 * 
 * all definitions in this file are framework internal
 * 
 */
class SynchedPropertyNestedObjectPU<C extends Object>
  extends ObservedPropertyAbstractPU<C>
  implements ObservedObjectEventsPUReceiver<C> {

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
    this.setValueInternal(obsObject);
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

  public objectPropertyHasChangedPU(eventSource: ObservedObject<C>, changedPropertyName: string) {
    stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: \
        objectPropertyHasChangedPU: contained ObservedObject property '${changedPropertyName}' has changed.`)
    this.notifyPropertyHasChangedPU();
  }


  public objectPropertyHasBeenReadPU(sourceObject: ObservedObject<C>, changedPropertyName : string) {
    stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: \
    objectPropertyHasBeenReadPU: contained ObservedObject property '${changedPropertyName}' has been read.`);
    this.notifyPropertyHasBeenReadPU();
  }
  
  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.obsObject_;
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: get`)
    this.notifyPropertyHasBeenReadPU()
    return this.obsObject_;
  }

  // set 'writes through` to the ObservedProperty
  public set(newValue: C): void {
    if (this.obsObject_ === newValue) {
      stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}IP, '${this.info() || "unknown"}']: set @ObjectLink with unchanged value - nothing to do.`);
      return;
    }

    stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: set: @ObjectLink set to new value: .`);

    if (this.setValueInternal(newValue)) {
      // notify value change to subscribing View
      this.notifyPropertyHasChangedPU();
    }
  }


  private setValueInternal(newValue: C): boolean {
    if (!this.checkIsObject(newValue)) {
      return false;
    }

    if (this.obsObject_ != undefined) {
      if (this.obsObject_ instanceof SubscribableAbstract) {
        // unregister from SubscribableAbstract object
        (this.obsObject_ as SubscribableAbstract).removeOwningProperty(this);
      } else if (ObservedObject.IsObservedObject(this.obsObject_)) {
        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.obsObject_, this);
      }
    }

    this.obsObject_ = newValue;

    if (this.obsObject_ != undefined) {
      if (this.obsObject_ instanceof SubscribableAbstract) {
        // register to  SubscribableAbstract object
        (this.obsObject_ as SubscribableAbstract).addOwningProperty(this);
      } else if (ObservedObject.IsObservedObject(this.obsObject_)) {
        // register to the ObservedObject
        ObservedObject.addOwningProperty(this.obsObject_, this);
      } else {
        stateMgmtConsole.error(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: set/init: @ObjectLink value is neither ObservedObject nor SubscribableAbstract. \
      value changes will bot be observed and UI will not update. forgot @Observed class decorator? Application error.`);
      }
    }
    return true;
  }
}

/** backward compatibility after typo in classname fix */
class SynchedPropertyNesedObjectPU<C extends Object> extends SynchedPropertyNestedObjectPU<C> {

}