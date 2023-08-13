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

class ObservedPropertyPU<T> extends ObservedPropertyAbstractPU<T>
  implements PeerChangeEventReceiverPU<T>, ObservedObjectEventsPUReceiver<T> {

  private wrappedValue_: T;

  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningView, propertyName);
   
    this.setValueInternal(localInitValue);
  }

  aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber) {
    this.unsubscribeWrappedObject();
    this.removeSubscriber(unsubscribeMe);
    super.aboutToBeDeleted();
  }


  public debugInfoDecorator() : string {
    return `@State/@Provide (class ObservedPropertyPU)`;
  }

  /**
   * Called by a SynchedPropertyObjectTwoWayPU (@Link, @Consume) that uses this as sync peer when it has changed
   * @param eventSource 
   */
  syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<T>) {
    stateMgmtConsole.debug(`${this.debugInfo()}: syncPeerHasChanged: from peer '${eventSource && eventSource.debugInfo && eventSource.debugInfo()}'.`);
    this.notifyPropertyHasChangedPU();
  }

  /**
   * Wraped ObservedObjectPU has changed
   * @param souceObject 
   * @param changedPropertyName 
   */
  public objectPropertyHasChangedPU(souceObject: ObservedObject<T>, changedPropertyName : string) {
    stateMgmtConsole.debug(`${this.debugInfo()}: objectPropertyHasChangedPU: contained ObservedObject property '${changedPropertyName}' has changed.`)
    this.notifyPropertyHasChangedPU();
  }

  public objectPropertyHasBeenReadPU(souceObject: ObservedObject<T>, changedPropertyName : string) {
    stateMgmtConsole.debug(`${this.debugInfo()}: objectPropertyHasBeenReadPU: contained ObservedObject property '${changedPropertyName}' has been read.`);
    this.notifyPropertyHasBeenReadPU();
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
    if (newValue == this.wrappedValue_) {
      stateMgmtConsole.debug(`${this.debugInfo()}: setValueInternal: newValue unchanged`);
      return false;
    }

    if (!this.checkIsSupportedValue(newValue)) {
      return false;
    }

    this.unsubscribeWrappedObject();
    if (!newValue || typeof newValue !== 'object') {
      // undefined, null, simple type: 
      // nothing to subscribe to in case of new value undefined || null || simple type 
      this.wrappedValue_ = newValue;
    } else if (newValue instanceof SubscribableAbstract) {
      stateMgmtConsole.debug(`${this.debugInfo()}: setValueInternal: new value is an SubscribableAbstract, subscribing to it.`);
      this.wrappedValue_ = newValue;
      (this.wrappedValue_ as unknown as SubscribableAbstract).addOwningProperty(this);
    } else if (ObservedObject.IsObservedObject(newValue)) {
      stateMgmtConsole.debug(`${this.debugInfo()}: setValueInternal: new value is an ObservedObject already`);
      ObservedObject.addOwningProperty(newValue, this);
      this.wrappedValue_ = newValue;
    } else {
      stateMgmtConsole.debug(`${this.debugInfo()}: setValueInternal: new value is an Object, needs to be wrapped in an ObservedObject.`);
      this.wrappedValue_ = ObservedObject.createNew(newValue, this);
    }
    return true;
  }

  public get(): T {
    stateMgmtConsole.debug(`${this.debugInfo()}: get`);
    this.notifyPropertyHasBeenReadPU();
    return this.wrappedValue_;
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`${this.debugInfo()}: getUnmonitored.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ == newValue) {
      stateMgmtConsole.debug(`${this.debugInfo()}: set: unchanged value - ignoring.`);
      return;
    }
    stateMgmtConsole.debug(`${this.debugInfo()}: set: value about to changed.`);
    if (this.setValueInternal(newValue)) {
      this.notifyPropertyHasChangedPU();
    }
  }
}

// class definitions for backward compatibility
class ObservedPropertyObjectPU<T> extends ObservedPropertyPU<T> {

}

class ObservedPropertySimplePU<T> extends ObservedPropertyPU<T> {
  
}
