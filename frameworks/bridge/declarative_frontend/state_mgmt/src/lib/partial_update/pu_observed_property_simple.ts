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
 * ObservedPropertySimplePU
 * implementation of @State and @Provide decorated variables of types (T=) boolean | number | string | enum
 *
 * Holds an actual property value of type T
 * uses its base class to manage subscribers to this
 * property.
 * 
 * all definitions in this file are framework internal
*/
class ObservedPropertySimplePU<T> extends ObservedPropertySimpleAbstractPU<T>
  implements ISinglePropertyChangeSubscriber<T>, PeerChangeEventReceiverPU<T> {

  private wrappedValue_: T;

  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningView, propertyName);

    // TODO undefined and null support remove this if statement
    if (typeof localInitValue === "object") {
      throw new SyntaxError("ObservedPropertySimple constructor: @State/@Provide value must not be an object")!
    }

    this.setValueInternal(localInitValue);
  }

  aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber) {
    this.removeSubscriber(unsubscribeMe);
    super.aboutToBeDeleted();
  }

  /**
 * Called by a @Link - SynchedPropertySimpleTwoWay that uses this as sync peer when it has changed
 * @param eventSource 
 */
  syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<T>) {
    stateMgmtConsole.debug(`ObservedPropertySimple[${this.id__()}, '${this.info() || "unknown"}']: syncPeerHasChanged peer '${eventSource.info()}'.`);
    this.notifyPropertyHasChangedPU();
  }

  /*
    actually update this.wrappedValue_
    called needs to do value change check
    and also notify with this.aboutToChange();
  */
  private setValueInternal(newValue: T): boolean {
    stateMgmtConsole.debug(`ObservedPropertySimplePU[${this.id__()}, '${this.info() || "unknown"}'] set new value`);
    if (this.wrappedValue_ != newValue) {
      this.wrappedValue_ = newValue;
      return true;
    }
    return false;
  }

  public getUnmonitored(): T {
    stateMgmtConsole.debug(`ObservedPropertySimple[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  public get(): T {
    stateMgmtConsole.debug(`ObservedPropertySimple[${this.id__()}, '${this.info() || "unknown"}']: get.`);
    this.notifyPropertyHasBeenReadPU()
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ == newValue) {
      stateMgmtConsole.debug(`ObservedPropertySimple[${this.id__()}, '${this.info() || "unknown"}']: set with unchanged value - ignoring.`);
      return;
    }
    stateMgmtConsole.debug(`ObservedPropertySimple[${this.id__()}, '${this.info() || "unknown"}']: set changed value.`);
    if (this.setValueInternal(newValue)) {
      this.notifyPropertyHasChangedPU();
    }
  }
}
