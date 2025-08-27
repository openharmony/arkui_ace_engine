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

  public staticWatchId?: number;

  public _setInteropValueForStaticState?: setValue<T>;

  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo) {
    super(owningView, propertyName);
   
    this.setValueInternal(localInitValue);
    this.setDecoratorInfo('@State');
  }

  aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber) {
    this.unsubscribeWrappedObject();
    this.removeSubscriber(unsubscribeMe);
    super.aboutToBeDeleted();
  }

  /**
   * Called by a SynchedPropertyObjectTwoWayPU (@Link, @Consume) that uses this as sync peer when it has changed
   * @param eventSource 
   */
  public syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<T>, isSync: boolean = false) : void {
    stateMgmtConsole.debug(`${this.debugInfo()}: syncPeerHasChanged: from peer ${eventSource && eventSource.debugInfo && eventSource.debugInfo()}'.`);
    this.notifyPropertyHasChangedPU(isSync);
  }

  public syncPeerTrackedPropertyHasChanged(eventSource: ObservedPropertyAbstractPU<T>,
    changedTrackedObjectPropertyName: string, isSync: boolean = false): void {
    stateMgmtConsole.debug(`${this.debugInfo()}: syncPeerTrackedPropertyHasChanged: from peer ${eventSource && eventSource.debugInfo && eventSource.debugInfo()}', changed property '${changedTrackedObjectPropertyName}'.`);
    this.notifyTrackedObjectPropertyHasChanged(changedTrackedObjectPropertyName, isSync);
  }

  /**
   * Wrapped ObservedObjectPU has changed
   * @param souceObject 
   * @param changedPropertyName 
   */
  public objectPropertyHasChangedPU(souceObject: ObservedObject<T>, changedPropertyName : string) {
    stateMgmtConsole.debug(`${this.debugInfo()}: objectPropertyHasChangedPU: contained ObservedObject property \ 
                                                '${changedPropertyName}' has changed.`);
    this.notifyPropertyHasChangedPU();
  }

  private unsubscribeWrappedObject() {
    if (this.wrappedValue_) {
      if (this.wrappedValue_ instanceof SubscribableAbstract) {
        (this.wrappedValue_ as SubscribableAbstract).removeOwningProperty(this);
      // for interop
      } else if (InteropConfigureStateMgmt.instance.needsInterop() && this.staticWatchId && typeof this.wrappedValue_ === 'object' &&
        'removeWatchSubscriber' in this.wrappedValue_ && typeof this.wrappedValue_.removeWatchSubscriber === 'function') {
          this.wrappedValue_.removeWatchSubscriber(this.staticWatchId);
      } else {
        ObservedObject.removeOwningProperty(this.wrappedValue_, this);

        // make sure the ObservedObject no longer has a read callback function
        // assigned to it
        ObservedObject.unregisterPropertyReadCb(this.wrappedValue_);
      }
    }
  }

  /*
    actually update this.wrappedValue_
    called needs to do value change check
    and also notify with this.aboutToChange();
  */
  private setValueInternal(newValue: T): boolean {
    stateMgmtProfiler.begin('ObservedPropertyPU.setValueInternal');
    if (newValue === this.wrappedValue_) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || 'unknown'}'] newValue unchanged`);
      stateMgmtProfiler.end();
      return false;
    }

    if (!this.checkIsSupportedValue(newValue)) {
      stateMgmtProfiler.end();
      return false;
    }

    this.unsubscribeWrappedObject();

    // for interop
    if (InteropConfigureStateMgmt.instance.needsInterop() && newValue && typeof newValue === 'object' && isStaticProxy(newValue)) {
      this.wrappedValue_ = InteropExtractorModule.getInteropObservedObject(newValue, this);
      stateMgmtProfiler.end();
      return true;
    }

    if (!newValue || typeof newValue !== 'object') {
      // undefined, null, simple type: 
      // nothing to subscribe to in case of new value undefined || null || simple type 
      this.wrappedValue_ = newValue;
    } else if (newValue instanceof SubscribableAbstract) {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: setValueInternal: new value is an SubscribableAbstract, subscribing to it.`);
      this.wrappedValue_ = newValue;
      (this.wrappedValue_ as unknown as SubscribableAbstract).addOwningProperty(this);
    } else if (ObservedObject.IsObservedObject(newValue)) {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: setValueInternal: new value is an ObservedObject already`);
      ObservedObject.addOwningProperty(newValue, this);
      this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(newValue);
      this.wrappedValue_ = newValue;
    } else {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: setValueInternal: new value is an Object, needs to be wrapped in an ObservedObject.`);
      this.wrappedValue_ = ObservedObject.createNew(newValue, this);
      this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.wrappedValue_);
    }
    stateMgmtProfiler.end();
    return true;
  }

  public get(): T {
    stateMgmtProfiler.begin('ObservedPropertyPU.get');
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get`);
    this.recordPropertyDependentUpdate();
    if (this.shouldInstallTrackedObjectReadCb) {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get: @Track optimised mode. Will install read cb func if value is an object`);
      ObservedObject.registerPropertyReadCb(this.wrappedValue_, this.onOptimisedObjectPropertyRead, this);
    } else {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get: compatibility mode. `);
    }
    stateMgmtProfiler.end();
    return this.wrappedValue_;
  }

  public getUnmonitored(): T {
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: getUnmonitored.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  public set(newValue: T): void {
    if (this.wrappedValue_ === newValue) {
      stateMgmtConsole.debug(`ObservedPropertyObjectPU[${this.id__()}, '${this.info() || 'unknown'}']: set with unchanged value - ignoring.`);
      return;
    }
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: set: value about to changed.`);
    const oldValue = this.wrappedValue_;
    if (this.setValueInternal(newValue)) {
      TrackedObject.notifyObjectValueAssignment(/* old value */ oldValue, /* new value */ this.wrappedValue_,
        this.notifyPropertyHasChangedPU,
        this.notifyTrackedObjectPropertyHasChanged, this);
      // for interop
      if (InteropConfigureStateMgmt.instance.needsInterop()) {
        InteropExtractorModule.setStaticValueForInterop(this, newValue);
      }
    }
  }

  protected onOptimisedObjectPropertyRead(readObservedObject: T, readPropertyName: string, isTracked: boolean) : void {
    stateMgmtProfiler.begin('ObservedProperty.onOptimisedObjectPropertyRead');
    const renderingElmtId = this.getRenderingElmtId();
    if (renderingElmtId >= 0) {
      if (!isTracked) {
        stateMgmtConsole.applicationError(`${this.debugInfo()}: onOptimisedObjectPropertyRead read NOT TRACKED property '${readPropertyName}' during rendering!`);
        throw new Error(`Illegal usage of not @Track'ed property '${readPropertyName}' on UI!`);
      } else {
        stateMgmtConsole.debug(`${this.debugInfo()}: onOptimisedObjectPropertyRead: ObservedObject property '@Track ${readPropertyName}' read.`);
        // only record dependency when
        // 1 - currently rendering or re-rendering
        //    TODO room for further optimization: if not an expression in updateFunc, only first time render needs to record
        //    because there can be change to depended variables unless one of the bindings is a JS expression
        // 2 - the changed ObservedObject is the wrapped object. The situation where it can be different is after a value assignment.
        if (this.getUnmonitored() === readObservedObject) {
          this.recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readPropertyName);
        }
      }
    }
    stateMgmtProfiler.end();
  }
}

// class definitions for backward compatibility
class ObservedPropertyObjectPU<T> extends ObservedPropertyPU<T> {

}

class ObservedPropertySimplePU<T> extends ObservedPropertyPU<T> {
  
}
