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

  private obsObject_: C = undefined;

  private staticWatchId?: number;

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
    this.createSourceDependency(obsObject);
    this.setValueInternal(obsObject);
    this.setDecoratorInfo("@ObjectLink");
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

  public getUnmonitored(): C {
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: getUnmonitored.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.obsObject_;
  }

  // get 'read through` from the ObservedProperty
  public get(): C {
    stateMgmtProfiler.begin('SynchedPropertyNestedObjectPU.get');
    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get`)
    this.recordPropertyDependentUpdate();
    if (this.shouldInstallTrackedObjectReadCb) {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get: @Track optimised mode. Will install read cb func if value is an object`);
      ObservedObject.registerPropertyReadCb(this.obsObject_, this.onOptimisedObjectPropertyRead, this);
    } else {
      stateMgmtConsole.propertyAccess(`${this.debugInfo()}: get: compatibility mode. `);
    }
    stateMgmtProfiler.end();
    return this.obsObject_;
  }

  // parent ViewPU rerender, runs update lambda with child ViewPU that contains a @ObjectLink
  // calls ViewPU.updateStateVarsByElmtId, calls updateStateVars in application class, calls this 'set' function
  public set(newValue: C): void {
    if (this.obsObject_ === newValue) {
      stateMgmtConsole.debug(`SynchedPropertyNestedObjectPU[${this.id__()}IP, '${this.info() || 'unknown'}']: set @ObjectLink with unchanged value - nothing to do.`);
      return;
    }

    stateMgmtConsole.propertyAccess(`${this.debugInfo()}: set: value about to change.`);
    const oldValue = this.obsObject_;
    if (this.setValueInternal(newValue)) {
      this.createSourceDependency(newValue);
      // notify value change to subscribing View
      TrackedObject.notifyObjectValueAssignment(/* old value */ oldValue, /* new value */ this.obsObject_,
        this.notifyPropertyHasChangedPU,
        this.notifyTrackedObjectPropertyHasChanged, this);
    }
  }

  protected onOptimisedObjectPropertyRead(readObservedObject: C, readPropertyName: string, isTracked: boolean): void {
    stateMgmtProfiler.begin('SynchedPropertyNestedObjectPU.onOptimisedObjectPropertyRead');
    const renderingElmtId = this.getRenderingElmtId();
    if (renderingElmtId >= 0) {
      if (!isTracked) {
        stateMgmtConsole.applicationError(`${this.debugInfo()}: onOptimisedObjectPropertyRead read NOT TRACKED property '${readPropertyName}' during rendering!`);
        throw new Error(`Illegal usage of not @Track'ed property '${readPropertyName}' on UI!`);
      } else {
        stateMgmtConsole.debug(`${this.debugInfo()}: onOptimisedObjectPropertyRead: ObservedObject property '@Track ${readPropertyName}' read.`);
        if (this.getUnmonitored() === readObservedObject) {
          this.recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readPropertyName)
        }
      }
    }
    stateMgmtProfiler.end();
  }
  
  private createSourceDependency(sourceObject: C): void {
    if (ObservedObject.IsObservedObject(sourceObject)) {
      stateMgmtConsole.debug(`${this.debugInfo()} createSourceDependency: create dependency on source ObservedObject ...`);
      const fake = (sourceObject as Object)[TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY];
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

        // make sure the ObservedObject no longer has a read callback function
        // assigned to it
        ObservedObject.unregisterPropertyReadCb(this.obsObject_);
      // for interop
      } else if (InteropConfigureStateMgmt.instance.needsInterop() && this.staticWatchId && typeof this.obsObject_ === 'object' &&
        'removeWatchSubscriber' in this.obsObject_ && typeof this.obsObject_.removeWatchSubscriber === 'function') {
          this.obsObject_.removeWatchSubscriber(this.staticWatchId);
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
        this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.obsObject_);
      // for interop
      } else if (InteropConfigureStateMgmt.instance.needsInterop() && typeof this.obsObject_ === 'object' &&
        'addWatchSubscriber' in this.obsObject_ && typeof this.obsObject_.addWatchSubscriber === 'function') {
        const callback = () => {
            this.notifyPropertyHasChangedPU();
        };
        if (typeof InteropExtractorModule.createWatchFunc !== undefined && typeof InteropExtractorModule.createWatchFunc === 'function') {
          this.staticWatchId = InteropExtractorModule.createWatchFunc(callback, this.obsObject_);
        }
      } else {
        stateMgmtConsole.frequentApplicationError(`${this.debugInfoWithoutId()} set/init (method setValueInternal): assigned value is not
          be decorated by @Observed. Value changes will not be observed and UI will not update.`);
    }
    }
    return true;
  }
}

/** backward compatibility after typo in classname fix */
class SynchedPropertyNesedObjectPU<C extends Object> extends SynchedPropertyNestedObjectPU<C> {

}