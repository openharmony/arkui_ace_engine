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
 * ObservedPropertyObjectPU
 * implementation of @State and @Provide decorated variables of type class object
 *
 * all definitions in this file are framework internal
 * 
 * class that holds an actual property value of type T
 * uses its base class to manage subscribers to this
 * property.
*/

class ObservedPropertyObjectPU<T extends Object> extends ObservedPropertyObjectAbstractPU<T> {

  private wrappedValue_: T;

  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningView, propertyName);

    if (!localInitValue) {
      stateMgmtConsole.error(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: constructor @State/@Provide initial value must not be undefined. Application error!`);
      return;
    }
    this.setValueInternal(localInitValue);
  }

  aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber) {
    this.unsubscribeWrappedObject();
    if (unsubscribeMe) {
      this.unlinkSuscriber(unsubscribeMe.id__());
    }
    super.aboutToBeDeleted();
  }

  /**
   * Called by a SynchedPropertyObjectTwoWayPU (@Link, @Consume) that uses this as sync peer when it has changed
   * @param eventSource 
   */
  syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<T>) {
    stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}']: syncPeerHasChanged peer '${eventSource.info()}'.`);
    this.notifyPropertryHasChangedPU();
  }

  /**
   * Wraped ObservedObjectPU has changed
   * @param souceObject 
   * @param changedPropertyName 
   */
  public objectPropertyHasChangedPU(souceObject: ObservedObject<T>, changedPropertyName : string) {
    stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}']: \
        objectPropertyHasChangedPU: contained ObservedObject property '${changedPropertyName}' has changed.`)
    this.notifyPropertryHasChangedPU();
  }

  private unsubscribeWrappedObject() {
    if (this.wrappedValue_) {
      if (this.wrappedValue_ instanceof SubscribableAbstract) {
        (this.wrappedValue_ as SubscribableAbstract).removeOwningProperty(this);
      } else {
        ObservedObject.removeOwningProperty(this.wrappedValue_, this);
      }
    }
  }
  
  /*
    actually update this.wrappedValue_
    called needs to do value change check
    and also notify with this.aboutToChange();
  */
  private setValueInternal(newValue: T): boolean {
    if (typeof newValue !== 'object') {
      stateMgmtConsole.error(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] new value is NOT an object. Application error. Ignoring set.`);
      return false;
    }

    if (newValue == this.wrappedValue_){
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] newValue unchanged`);
      return false;
    }

    this.unsubscribeWrappedObject();

    if (ObservedObject.IsObservedObject(newValue)) {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] new value is an ObservedObject already`);
      ObservedObject.addOwningProperty(newValue, this);
      this.wrappedValue_ = newValue;
    } else if (newValue instanceof SubscribableAbstract) {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] new value is an SubscribaleAbstract, subscribiung to it.`);
      this.wrappedValue_ = newValue;
      (this.wrappedValue_ as unknown as SubscribableAbstract).addOwningProperty(this);
    } else {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] new value is an Object, needs to be wrapped in an ObservedObject.`);
      this.wrappedValue_ = ObservedObject.createNew(newValue, this);
    }
    return true;
  }

  public get(): T {
    stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}']: get`);
    this.notifyPropertryHasBeenReadPU();
    return this.wrappedValue_;
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}' .`);
    // unmonitored get access , no call to otifyPropertyRead !
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ == newValue) {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}']: set with unchanged value - ignoring.`);
      return;
    }
    stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}']: set, changed`);
    if (this.setValueInternal(newValue)) {
      this.notifyPropertryHasChangedPU();
    }
  }
}
