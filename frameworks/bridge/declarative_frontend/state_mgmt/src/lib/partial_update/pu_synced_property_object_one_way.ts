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


type SyncSourceHasChangedCb<T> = (source : ObservedPropertyAbstract<T>) => void;

class SynchedPropertyObjectOneWayPU<C extends Object>
  extends ObservedPropertyObjectAbstractPU<C> {

  // inner anonymous class to handler hasChanged
  // notifications from @Prop source
  // separate subscriber needed to avoid confusing 
  // hasChanged events from wrappedValue's ObservedObject
  private sourceChangeObserver_ = new class<C> {
    private source_: ObservedPropertyAbstract<C> = undefined;
    private id_: number;
    private notifySourceHasChanged_: SyncSourceHasChangedCb<C>;
  
    constructor(notifySourceHasChanged: SyncSourceHasChangedCb<C>) {
      this.id_ = SubscriberManager.MakeId();
      SubscriberManager.Add(this);
        this.notifySourceHasChanged_ = notifySourceHasChanged;
    }
  
    // globally unique id
    public id__(): number {
      return this.id_;
    }

    // only use for delayed object init
    // re-settign source to other value is unsupported.
    public setSource(source: ObservedPropertyAbstractPU<C>) : void{
      if (source) {
        this.source_ = source;
        this.source_.subscribeMe(this);
      }
    }
  
    /**
     *  inform the subscribed property
     * that the subscriber is about to be deleted
     * hence , unsubscribe
     */
    public aboutToBeDeleted(owningView?: IPropertySubscriber): void {
      if (this.source_) {
        this.source_.unlinkSuscriber(this.id__());
      }
      this.source_ = undefined;
      SubscriberManager.Delete(this.id__())
    }


    // implements  ISinglePropertyChangeSubscriber<T>:
    // this object is subscriber to this.source_
    // when source notifies a change, copy its value to local backing store
    public hasChanged(newValue: C): void {
      // stateMgmtConsole.debug(`SynchedPropertyNesedObjectPU[${this.id__()}]: hasChanged. DO NOT HANDLE.`)
      //  this.notifySourceHasChanged_ (this.source_);
    }

    /**
     * Emited when source has changed
     * @param eventSource 
     */
    public syncPeerHasChanged(eventSource : ObservedPropertyAbstractPU<C>) {
      if (eventSource && this.source_ == eventSource) {
        // should always be the case!
        stateMgmtConsole.debug(`SynchedPropertyNesedObjectPU[${this.id__()}]: syncPeerHasChanged(): Source '${eventSource.info()}' has changed'.`)
        this.notifySourceHasChanged_(this.source_);
      } else {
        stateMgmtConsole.warn(`SynchedPropertyNesedObjectPU[${this.id__()}]: syncPeerHasChanged Unexpected situation. Ignorning event.`)
      }
    }
  
    
    public set(sourceChangedValue : C) : void {
      // if set causes an actual change, then, ObservedPropertyObject source_ will call hasChanged
      this.source_.set(sourceChangedValue);
    }
  }(this.sourceHasChanged.bind(this));

  private wrappedValue_: C;

  constructor(source: ObservedPropertyAbstract<C> | C,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo) {
    super(owningChildView, thisPropertyName);

    if (source && (typeof (source) === "object") && ("notifyHasChanged" in source) && ("subscribeMe" in source)) {
      // code path for @(Local)StorageProp, the souce is a ObservedPropertyObject in aLocalStorage)
      this.sourceChangeObserver_.setSource(source as ObservedPropertyAbstractPU<C>)
      this.setWrappedValue((source as ObservedPropertyAbstract<C>).get());
    } else {
      // code path for @Prop
      if (!ObservedObject.IsObservedObject(source)) {
        stateMgmtConsole.warn(`@Prop ${this.info()}  Provided source object's class 
           lacks @Observed class decorator. Object property changes will not be observed.`);
      }

      this.sourceChangeObserver_.setSource(
        new ObservedPropertyObjectPU<C>(source as C, /* do not subscribe 'this' */ undefined, thisPropertyName)
      );

      // deep copy source Object and wrap it
      this.setWrappedValue(source as C);
    }

    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor ready with wrappedValue '${JSON.stringify(this.wrappedValue_)}'.`);
  }

  /*
  like a destructor, need to call this before deleting
  the property.
  */
  aboutToBeDeleted() {
    this.sourceChangeObserver_.aboutToBeDeleted();
    super.aboutToBeDeleted();
  }

  protected sourceHasChanged(source: ObservedPropertyObjectPU<C>): void {
    const newValue = source.getUnmonitored();
    if (typeof newValue == "object") {
      stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: hasChanged:  newValue '${JSON.stringify(newValue)}'.`);
      this.setWrappedValue(newValue);
      // this.notifyHasChanged(ObservedObject.GetRawObject(this.wrappedValue_));
      this.notifyPropertryHasChangedPU();
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
    this.notifyPropertryHasChangedPU();
  }

  public getUnmonitored(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: getUnmonitored returns '${JSON.stringify(this.wrappedValue_)}'.`);
    // unmonitored get access , no call to notifyPropertyRead !
    return this.wrappedValue_;
  }

  // get 'read through` from the ObservedObject
  public get(): C {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: get returning ${JSON.stringify(this.wrappedValue_)}.`)
    // this.notifyPropertyRead();
    this.notifyPropertryHasBeenReadPU()
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
    //    this.notifyHasChanged(this.wrappedValue_);
    this.notifyPropertryHasChangedPU();
  }

  public reset(sourceChangedValue: C): void {
    stateMgmtConsole.debug(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: reset from '${JSON.stringify(this.wrappedValue_)}' to '${JSON.stringify(sourceChangedValue)}'.`);
    this.sourceChangeObserver_.set(sourceChangedValue);
  }

  private setWrappedValue(value: C): void {
    this.wrappedValue_ = ObservedObject.GetDeepCopyOfObject(value);
    ObservedObject.addOwningProperty(this.wrappedValue_, this);
  }
}
