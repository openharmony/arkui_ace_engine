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
 * ObservedPropertyAbstractPU aka ObservedPropertyAbstract for partial update
 * 
 * all definitions in this file are framework internal
 */

abstract class ObservedPropertyAbstractPU<T> extends ObservedPropertyAbstract<T> 
implements ISinglePropertyChangeSubscriber<T>, IMultiPropertiesChangeSubscriber, IMultiPropertiesReadSubscriber
// these interfaces implementations are all empty functions, overwrite FU base class implementations.
{
  static readonly DelayedNotifyChangesEnum=class  {
    static readonly do_not_delay = 0;
    static readonly delay_none_pending = 1;
    static readonly delay_notification_pending = 2;
  };
  
  private owningView_ : ViewPU = undefined;
    
  // elmtIds dependent of variable assignment
  // inner Map for fine-rain dependencies on individual property changes
  private dependentElmtIdsByProperty_ = new class PropertyDependencies {

    private map_: Map<number, Set<string>> = new Map<number, Set<string>>();

    public getDependentElmtIds(changedObjectProperty: string | undefined, debugInfo : string): Set<number> {
      if (!changedObjectProperty) {
        stateMgmtConsole.debug(`${debugInfo}: variable value assignment: returning affected elmtIds ${JSON.stringify(this.map_.keys())}`);
        return new Set<number>(this.map_.keys());
      }
      let result = new Set<number>();
      this.map_.forEach((properties: Set<string>, elmtId: number) => {
        if (properties.has(changedObjectProperty)) {
          result.add(elmtId);
        }
      });
      stateMgmtConsole.debug(`${debugInfo}: changed object property '${changedObjectProperty}': returning affected elmtIds ${JSON.stringify(Array.from(result))}`);
      return result;
    }

    public addDependency(elmtId: number, readProperty: string | undefined, debugInfo : string): void {
      let propertyDependencies = this.map_.get(elmtId);
      if (!propertyDependencies) {
        propertyDependencies = new Set<string>();
        this.map_.set(elmtId, propertyDependencies);
        stateMgmtConsole.debug(`${debugInfo} - add elmtId ${elmtId} - updated list of dependent elmtIds: ${JSON.stringify(Array.from(this.map_.keys()))} .`);
      } else {
        stateMgmtConsole.debug(`${debugInfo} - elmtId ${elmtId} known already - unchanged list of dependent elmtIds: ${JSON.stringify(this.map_.keys())} .`);
      }
    
      if (readProperty) {
        /* record dependency on given property */
        propertyDependencies.add(readProperty);
        stateMgmtConsole.debug(`   ... for elmtId ${elmtId} added dependency for object property '${readProperty}' - updated dependent property list ${JSON.stringify(Array.from(propertyDependencies))} .`);
      }
    }

    public unregisterDependenciesForElmtId(rmElmtId: number, debugInfo : string): boolean {
      const removedOK = this.map_.delete(rmElmtId);
      stateMgmtConsole.debug(`${debugInfo} - removed dependency on elmtId ${rmElmtId} - resulting dependency list: ${JSON.stringify(this.map_.keys())} .`);
      return removedOK;
    }
  }; // inner class PropertyDependencies

  // PU code stores object references to dependencies directly as class variable
  // SubscriberManager is not used for lookup in PU code path to speedup updates
  protected subscriberRefs_: Set<IPropertySubscriber>;
  
  // when owning ViewPU is inActive, delay notifying changes
  private delayedNotification_: number = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay;
  private elmtIdsNeedDelayedRerender_ : Set<number> | undefined = undefined;

  constructor(subscriber: IPropertySubscriber, viewName: PropertyInfo) {
    super(subscriber, viewName);
    Object.defineProperty(this, 'owningView_', {writable: true, enumerable: false});
    Object.defineProperty(this, 'subscriberRefs_',
      {writable: true, enumerable: false, value: new Set<IPropertySubscriber>()});
    if(subscriber) {
      if (subscriber instanceof ViewPU) {
        this.owningView_ = subscriber;
      } else {
        this.subscriberRefs_.add(subscriber);
      }
    }
  }

  aboutToBeDeleted() {
    super.aboutToBeDeleted();
    this.subscriberRefs_.clear();
    this.owningView_ = undefined;
  }

  /*
    Virtualized version of the subscription mechanism - add subscriber
    Overrides implementation in ObservedPropertyAbstract<T>
  */
  public addSubscriber(subscriber: ISinglePropertyChangeSubscriber<T>):void {
    if (subscriber) {
      // ObservedPropertyAbstract will also add subscriber to
      // SubscriberManager map and to its own Set of subscribers as well
      // Something to improve in the future for PU path.
      // subscribeMe should accept IPropertySubscriber interface
      super.subscribeMe(subscriber as ISinglePropertyChangeSubscriber<T>);
      this.subscriberRefs_.add(subscriber);
    }
  }

  /*
    Virtualized version of the subscription mechanism - remove subscriber
    Overrides implementation in ObservedPropertyAbstract<T>
  */
  public removeSubscriber(subscriber: IPropertySubscriber, id?: number):void {
    if (subscriber) {
      this.subscriberRefs_.delete(subscriber);
      if (!id) {
        id = subscriber.id__();
      }
    }
    super.unlinkSuscriber(id);
  }


  /**
   * put the property to delayed notification mode
   * feature is only used for @StorageLink/Prop, @LocalStorageLink/Prop
   */
  public enableDelayedNotification() : void {
  if (this.delayedNotification_ != ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending) {
      stateMgmtConsole.debug(`${this.constructor.name}: enableDelayedNotification.`);
      this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_none_pending;
    }
  }

  /*
     when moving from inActive to active state the owning ViewPU calls this function
     This solution is faster than ViewPU polling each variable to send back a viewPropertyHasChanged event
     with the elmtIds

    returns undefined if variable has _not_ changed
    returns dependentElementIds_ Set if changed. This Set is empty if variable is not used to construct the UI
  */
  public moveElmtIdsForDelayedUpdate(): Set<number> | undefined {
    /* TODO: further optimisation possibility: memorize which elmtIds actually need re-render instead of forcing all dependent elmtIds to render */
    const result = (this.delayedNotification_ == ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending)
      ? this.dependentElmtIdsByProperty_.getDependentElmtIds(/* like var value assignment */ undefined, "moveElmtIdsForDelayedUpdate")
      : undefined;
    stateMgmtConsole.debug(`${this.constructor.name}: moveElmtIdsForDelayedUpdate: elmtIds that need delayed update ${result ? Array.from(result).toString() : 'no delayed notifications'} .`);
    this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay;
    return result;
  }

  protected notifyPropertyRead() {
    stateMgmtConsole.error(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
        notifyPropertyRead, DO NOT USE with PU. Use notifyPropertyHasBeenReadPU`);
  }


  /**
 * Wrapped ObservedObjectPU has changed
 * @param souceObject 
 * @param changedPropertyName 
 */
  public objectPropertyHasChangedPU(souceObject: ObservedObject<T>, changedPropertyName: string) {
    stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
          objectPropertyHasChangedPU: contained ObservedObject property '${changedPropertyName}' has changed.`)
    this.notifyPropertyHasChangedPU(/* object property has changed */ changedPropertyName);
  }

  public objectPropertyHasBeenReadPU(sourceObject: ObservedObject<T>, changedPropertyName: string) {
    if (this.owningView_ && !this.owningView_.isRenderInProgress()) {
      // only notify read while owning ViewPU render is in progress
      stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
      objectPropertyHasBeenReadPU render is not in progress`);
      return;
    }

    stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
      objectPropertyHasBeenReadPU: contained ObservedObject property '${changedPropertyName}' has been read.`);
    this.notifyPropertyHasBeenReadPU(/* property has been read */ changedPropertyName);
  }


  protected notifyPropertyHasBeenReadPU(readProperty : string | undefined /* undefined means variable read */) {
    if (this.owningView_ && !this.owningView_.isRenderInProgress()) {
      // only notify read while render is in progress
      return;
    }

    stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertyHasBeenReadPU: ${readProperty ? 'caused by object property ' + readProperty + ' read' : 'caused by value read'}`)
    this.subscriberRefs_.forEach((subscriber) => {
      if (subscriber) {
        // TODO
        // propertyHasBeenReadPU is not use in the code
        // defined by interface that is not used either: PropertyReadEventListener
        // Maybe compiler generated code has it?
        if ('propertyHasBeenReadPU' in subscriber) {
          (subscriber as unknown as PropertyReadEventListener<T>).propertyHasBeenReadPU(this, readProperty);
        }
      }
    });
    this.recordDependentUpdate(readProperty);
  } 

  /* notify a 'set' operation, three scenarios:
  1- value assignment ':=' to this variable, either simple or object type
  2- object property change
  3- syncPeerHasChanged
  */
  protected notifyPropertyHasChangedPU(changedProperty : string | undefined /* undefined means new variable value assignment */) {
    stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertyHasChangedPU: ${changedProperty ? 'caused by object property ' + changedProperty + ' change' : 'caused by value assignment'}`)
    if (this.owningView_) {
      if (this.delayedNotification_ == ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay) {
        // send viewPropertyHasChanged right away
        // if an object property has changed, only mark elmtIds dependent on this elmtId of needing update.
        // if variable was assigned a new simple or object type value, then, changedProperty is undefined, implies dependentElementIds_ needs rerender.
      let elmtIdsNeedRerender = this.dependentElmtIdsByProperty_.getDependentElmtIds(changedProperty, "notifyPropertyHasChangedPU");
        this.owningView_.viewPropertyHasChanged(this.info_, elmtIdsNeedRerender);
      } else {
        // mark this @StorageLink/Prop or @LocalStorageLink/Prop variable has having changed and notification of viewPropertyHasChanged delivery pending
        this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending;
      }
    }
    this.subscriberRefs_.forEach((subscriber) => {
      if (subscriber) {
        if ('syncPeerHasChanged' in subscriber) {
          (subscriber as unknown as PeerChangeEventReceiverPU<T>).syncPeerHasChanged(this, changedProperty);
        } else  {
          stateMgmtConsole.warn(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertryHasChangedPU: unknown subscriber ID 'subscribedId' error!`);
        }
      }
    });
  }  

  
  public markDependentElementsDirty(view: ViewPU) {
    // TODO ace-ets2bundle, framework, complicated apps need to update together
    // this function will be removed after a short transition period.
    stateMgmtConsole.warn(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: markDependentElementsDirty no longer supported. App will work ok, but
        please update your ace-ets2bundle and recompile your application!`);
  }

  public numberOfSubscrbers(): number {
    return this.subscriberRefs_.size + (this.owningView_ ? 1 : 0);
  }

  /*
   type checking for any supported type, as required for union type support
    see 1st parameter for explanation what is allowed

    FIXME this expects the Map, Set patch to go in
  */

  protected checkIsSupportedValue(value: T): boolean {
    return this.checkNewValue(
      `undefined, null, number, boolean, string, or Object but not function`,
      value,
      () => ((typeof value == "object" && typeof value != "function")
        || typeof value == "number" || typeof value == "string" || typeof value == "boolean")
        || (value == undefined || value == null)
    );
  }

  /*
    type checking for allowed Object type value
    see 1st parameter for explanation what is allowed

      FIXME this expects the Map, Set patch to go in
    */
  protected checkIsObject(value: T): boolean {
    return this.checkNewValue(
      `undefined, null, Object including Array and instance of SubscribableAbstract and excluding function, Set, and Map`,
      value,
      () => (value == undefined || value == null || (typeof value == "object"))
    );
  }

  /*
    type checking for allowed simple types value
    see 1st parameter for explanation what is allowed
 */
  protected checkIsSimple(value: T): boolean {
    return this.checkNewValue(
      `undefined, number, boolean, string`,
      value,
      () => (value == undefined || typeof value == "number" || typeof value == "string" || typeof value == "boolean")
    );
  }
    
  private static readonly mapDeco = new Map<string, string>([
    ["ObservedPropertyObjectPU", "@State/@Provide"],
    ["ObservedPropertySimplePU", "@State/@Provide (error, should not be used)"],
    ["SynchedPropertyObjectOneWayPU", "@Prop"],
    ["SynchedPropertySimpleOneWayPU", "@Prop  (error, should not be used)"],
    ["SynchedPropertyObjectTwoWayPU", "@Link/@Consume"],
    ["SynchedPropertySimpleTwoWayPU", "@Link/@Consume (error, should not be used)"],
    ["SynchedPropertyNestedObjectPU", "@ObjectLink (only class-objects supported"],
    ["SynchedPropertyNesedObjectPU", "@ObjectLink (only class-objects supported"]
  ]);

  protected checkNewValue(isAllowedComment : string, newValue: T, validator: (value: T) => boolean) : boolean {
    if (validator(newValue)) {
      return true;
    } 

    // report error
    // current implementation throws an Exception
    errorReport.varValueCheckFailed({
      customComponent: this.owningView_? this.owningView_.constructor.name : "unknown owningView / internal error",
      variableDeco: ObservedPropertyAbstractPU.mapDeco.get(this.constructor.name),
      variableName: this.info(),
      expectedType: isAllowedComment,
      value: newValue
    });

    // never gets here if errorReport.varValueCheckFailed throws an exception
    // but should nto depend on its implementation
    return false;
  }

  
  /**
   * factory function for concrete 'object' or 'simple' ObservedProperty object
   * depending if value is Class object
   * or simple type (boolean | number | string)
   * @param value
   * @param owningView
   * @param thisPropertyName
   * @returns either
   */
  static CreateObservedObject<C>(value: C, owningView: IPropertySubscriber, thisPropertyName: PropertyInfo)
    : ObservedPropertyAbstract<C> {
    return (typeof value === "object") ?
      new ObservedPropertyObject(value, owningView, thisPropertyName)
      : new ObservedPropertySimple(value, owningView, thisPropertyName);
  }


  /**
   * during 'get' access recording take note of the created component and its elmtId
   * and add this component to the list of components who are dependent on this property
   */
  protected recordDependentUpdate(readProperty : string | undefined /* undefined means variable read */) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    if (elmtId < 0) {
      // not access recording 
      return;
    }
    this.dependentElmtIdsByProperty_.addDependency(elmtId, readProperty, "recordDependentUpdate");
  }

  
  public purgeDependencyOnElmtId(rmElmtId: number): void {
    // this.dependentElementIds_.delete(rmElmtId);
    this.dependentElmtIdsByProperty_.unregisterDependenciesForElmtId(rmElmtId, "purgeDependencyOnElmtId");
  }

  public SetPropertyUnchanged(): void {
    // function to be removed
    // keep it here until transpiler is updated.
  }

  // FIXME check, is this used from AppStorage.
  // unified Appstorage, what classes to use, and the API
  public createLink(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstractPU<T> {
    throw new Error("Can not create a AppStorage 'Link' from a @State property. ");
  }

  public createProp(subscribeOwner?: IPropertySubscriber,
    linkPropName?: PropertyInfo): ObservedPropertyAbstractPU<T> {
    throw new Error("Can not create a AppStorage 'Prop' from a @State property. ");
  }

  /*
    Below empty functions required to keep as long as this class derives from FU version
    ObservedPropertyAbstract. Need to overwrite these functions to do nothing for PU
    */
    protected notifyHasChanged(_: T) {
      stateMgmtConsole.error(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
          notifyHasChanged, DO NOT USE with PU. Use syncPeerHasChanged() or objectPropertyHasChangedPU()`);
    }
  
    hasChanged(_: T): void {
      // unused for PU
      // need to overwrite impl of base class with empty function.
    }
  
    propertyHasChanged(_?: PropertyInfo): void {
      // unused for PU
      // need to overwrite impl of base class with empty function.
    }
  
    propertyRead(_?: PropertyInfo): void {
      // unused for PU
      // need to overwrite impl of base class with empty function.
    }
}