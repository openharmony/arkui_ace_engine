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
 * ObservedPropertyOPU
 * implementation of @State and @Provide decorated variables of all types
 *
 * all definitions in this file are framework internal
 * 
 * class that holds an actual property value of type T
 * uses its base class to manage subscribers to this
 * property.
*/

class ObservedPropertyPU<T> extends  ObservedPropertyAbstractPU<T> {

  private wrappedValue_: T;

  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningView, propertyName);

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

  private unsubscribeWrappedObject() : void {
    if (this.wrappedValue_ == undefined) {
      return;
    }
    if (this.wrappedValue_ instanceof SubscribaleAbstract) {
      (this.wrappedValue_ as SubscribaleAbstract).removeOwningProperty(this);
    } else if (ObservedObject.IsObservedObject(this.wrappedValue_)) {
      ObservedObject.removeOwningProperty(this.wrappedValue_, this);
    }
    // nothing to do for simple type warappedValue_
  }
  
  /*
    actually update this.wrappedValue_
    called needs to do value change check
    and also notify with this.aboutToChange();
  */
  private setValueInternal(newValue: T): boolean {

    if (newValue == this.wrappedValue_) {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] newValue unchanged`);
      return false;
    }

    this.unsubscribeWrappedObject();

    if (newValue == undefined) {
      stateMgmtConsole.warn(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] setValue: Warning: new value is undefined. This can cause issues.`);
      this.wrappedValue_ = newValue
    } else if (ObservedObject.IsObservedObject(newValue)) {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] setValue: new value is an ObservedObject already`);
      ObservedObject.addOwningProperty(newValue, this);
      this.wrappedValue_ = newValue;
    } else if (newValue instanceof SubscribaleAbstract) {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] setValue: new value is an SubscribaleAbstract, subscribiung to it.`);
      this.wrappedValue_ = newValue;
      (this.wrappedValue_ as unknown as SubscribaleAbstract).addOwningProperty(this);
    } else if (typeof newValue === 'object') {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] setValue: new value is an Object, needs to be wrapped in an ObservedObject.`);
      this.wrappedValue_ = ObservedObject.createNew(newValue, this);
    } else if (typeof newValue === 'string' || typeof newValue === 'number' || typeof newValue === 'boolean') {
      stateMgmtConsole.debug(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] setValue: new value is simple type.`);
      this.wrappedValue_ = newValue
    } else {
      stateMgmtConsole.error(`ObservedPropertyObject[${this.id__()}, '${this.info() || "unknown"}'] setValue: new value is unsupported type. Application error!`);
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

// backward compatibility

class ObservedPropertySimplePU<S> extends ObservedPropertyPU<S> {
  constructor(localInitValue: S, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(localInitValue, owningView, propertyName);
  }
}

class ObservedPropertyObjectPU<C extends Object> extends ObservedPropertyPU<C> {
  constructor(localInitValue: C, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(localInitValue, owningView, propertyName);
  }
}

abstract class ObservedPropertyObjectAbstractPU<C extends Object> extends ObservedPropertyAbstractPU<C> {
  constructor(owningView: IPropertySubscriber, thisPropertyName: PropertyInfo) {
    super(owningView, thisPropertyName)
  }
}

abstract class ObservedPropertySimpleAbstractPU<T> extends ObservedPropertyAbstractPU<T>  {
  constructor(owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningView, propertyName);
  }
}
