/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
   
    if (!this.checkIsSupportedValue(localInitValue)) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: constructor: initial value type unsupported. Leaving variable uninitialized. Application error.`);
      return;
    }

    if (!localInitValue || typeof localInitValue !== 'object') {
      // undefined, null, simple type: 
      // nothing to subscribe to in case of new value undefined || null || simple type 
      this.wrappedValue_ = localInitValue;
    } else if (localInitValue instanceof SubscribableAbstract) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: constructor: initial value  is an SubscribableAbstract, subscribiung to it.`);
      this.wrappedValue_ = localInitValue;
      (this.wrappedValue_ as unknown as SubscribableAbstract).addOwningProperty(this);
    } else if (ObservedObject.IsObservedObject(localInitValue)) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: constructor: initial value  is an ObservedObject already`);
      ObservedObject.addOwningProperty(localInitValue, this);
      ObservedObject.setReadingProperty(localInitValue, this);
      this.wrappedValue_ = localInitValue;
    } else {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: constructor: initial value is an Object, needs to be wrapped in an ObservedObject.`);
      this.wrappedValue_ = ObservedObject.createNew(localInitValue, this);
      ObservedObject.setReadingProperty(this.wrappedValue_, this);
    }
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
  syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<T>, changedObjectProperty : string | undefined) {
    stateMgmtConsole.debug(`${this.debugInfo()}: syncPeerHasChanged: from peer \
          '${eventSource && eventSource.debugInfo && eventSource.debugInfo()}', property '${changedObjectProperty}'.`);
    this.notifyPropertyHasChangedPU(changedObjectProperty);
  }
  
  private unsubscribeWrappedObject() {
    if (this.wrappedValue_) {
      if (this.wrappedValue_ instanceof SubscribableAbstract) {
        (this.wrappedValue_ as SubscribableAbstract).removeOwningProperty(this);
      } else {
        ObservedObject.removeOwningProperty(this.wrappedValue_, this);
        ObservedObject.unsetReadingProperty(this.wrappedValue_);
      }
    }
  }

  public get(): T {
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get`);
    ObservedObject.setReadingProperty(this.getUnmonitored(), this);
    this.recordObservedVariableDependency();   
     return this.wrappedValue_;
  }

  public getUnmonitored(): T {
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: getUnmonitored.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ === newValue) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: set with unchanged value - ignoring.`);
      return;
    }

    if (newValue === this.wrappedValue_) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || "unknown"}']: set: newValue unchanged`);
      return;
    }

    if (!this.checkIsSupportedValue(newValue)) {
      stateMgmtConsole.debug(`${this.debugInfo()}: set: new value type unsupported. Leaving variable unchanged. Application error.`);
      return;
    }

    stateMgmtConsole.debug(`${this.debugInfo()}: set, value about to change ...`);

    this.unsubscribeWrappedObject();
    if (!newValue || typeof newValue !== 'object') {
      // undefined, null, simple type: 
      // nothing to subscribe to in case of new value undefined || null || simple type 
      this.wrappedValue_ = newValue;
      this.notifyPropertyHasChangedPU(/* var value assignment */ undefined);
    } else if (newValue instanceof SubscribableAbstract) {
      stateMgmtConsole.debug(`${this.debugInfo()}: set: new value is an SubscribableAbstract, subscribiung to it.`);
      this.wrappedValue_ = newValue;
      (this.wrappedValue_ as unknown as SubscribableAbstract).addOwningProperty(this);
      this.notifyPropertyHasChangedPU(/* var value assignment */ undefined);
    } else {
      const oldValue = this.wrappedValue_;
      if (ObservedObject.IsObservedObject(newValue)) {
        stateMgmtConsole.debug(`${this.debugInfo()}: set: new value is an ObservedObject already`);
        ObservedObject.addOwningProperty(newValue, this);
        ObservedObject.setReadingProperty(newValue, this);
        this.wrappedValue_ = newValue;
      } else {
        stateMgmtConsole.debug(`${this.debugInfo()}: set: new value is an Object, needs to be wrapped in an ObservedObject.`);
        this.wrappedValue_ = ObservedObject.createNew(newValue, this);
        ObservedObject.setReadingProperty(this.wrappedValue_, this);
      }

   //   const changedPropertyNames: string | Set<string> = ObservedPropertyAbstractPU.findChangedObjectProperties(oldValue, this.wrappedValue_);
     // FIXME enable optimisation if (changedPropertyNames instanceof Set) {
       // stateMgmtConsole.debug(`${this.debugInfo()}: set: notifying individual class object property changes ...`);
    //    (changedPropertyNames as Set<string>).forEach((changedPropertyName) => this.notifyPropertyHasChangedPU(changedPropertyName));
    //  } else {
    //    stateMgmtConsole.debug(`${this.debugInfo()}: set: ${changedPropertyNames as string} .`);
        this.notifyPropertyHasChangedPU(/* var value assignment */ undefined);
      //}
    }
  }
}

// class definitions for backward compatibility
class ObservedPropertyObjectPU<T> extends ObservedPropertyPU<T> {

}

class ObservedPropertySimplePU<T> extends ObservedPropertyPU<T> {
  
}
