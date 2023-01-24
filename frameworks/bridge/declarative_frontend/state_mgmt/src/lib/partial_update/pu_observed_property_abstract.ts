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

abstract class ObservedPropertyAbstractPU<T> 
    extends ObservedPropertyAbstract<T> 
{

  private dependentElementIds_: Set<number> = new Set<number>();

  constructor(subscribingView: IPropertySubscriber, viewName: PropertyInfo) {
    super(subscribingView, viewName);
  }

  protected notifyHasChanged(newValue: T) {
    stateMgmtConsole.error(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyHasChanged, DO NOT USE.`);
    /*
    stateMgmtConsole.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyHasChanged, notifying.`);
    this.subscribers_.forEach((subscribedId) => {
      var subscriber: IPropertySubscriber = SubscriberManager.Find(subscribedId)
      if (subscriber) {
        if ('hasChanged' in subscriber) {
          (subscriber as ISinglePropertyChangeSubscriber<T>).hasChanged(newValue);
        }
        if ('viewPropertyHasChanged' in subscriber) {
          (subscriber as ViewPU).viewPropertyHasChanged(this.info_, this.dependentElementIds_);
        } else if ('propertyHasChanged' in subscriber) {
          (subscriber as IMultiPropertiesChangeSubscriber).propertyHasChanged(this.info_);
        }
      } else {
        stateMgmtConsole.warn(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyHasChanged: unknown subscriber ID '${subscribedId}' error!`);
      }
    });
    */
  }

  protected notifyPropertyRead() {
    //stateMgmtConsole.error(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertyRead DO NOT USE with PU`);
    // FIXME remove function
   //    super.notifyPropertyRead();
    //    this.recordDependentUpdate();
  }

  protected notifyPropertryHasBeenReadPU() {
    stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: propertyHasBeenReadPU.`)
    this.subscribers_.forEach((subscribedId) => {
      var subscriber: IPropertySubscriber = SubscriberManager.Find(subscribedId)
      if (subscriber) {
        if ('propertyHasBeenReadPU' in subscriber) {
          (subscriber as unknown as PropertyEventsReceiverPU<T>).propertyHasBeenReadPU(this);
        }
      }
    });
    this.recordDependentUpdate();
  } 

  protected notifyPropertryHasChangedPU() {
    stateMgmtConsole.debug(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertryHasChangedPU.`)
    this.subscribers_.forEach((subscribedId) => {
      var subscriber: IPropertySubscriber = SubscriberManager.Find(subscribedId)
      if (subscriber) {
        if ('viewPropertyHasChanged' in subscriber) {
          (subscriber as ViewPU).viewPropertyHasChanged(this.info_, this.dependentElementIds_);
        } else if ('syncPeerHasChanged' in subscriber) {
          (subscriber as unknown as PropertyEventsReceiverPU<T>).syncPeerHasChanged(this);
        } else  {
          stateMgmtConsole.warn(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertryHasChangedPU: unknown subscriber ID '${subscribedId}' error!`);
        }
      }
    });
  }
  

  public markDependentElementsDirty(view: ViewPU) {
    // TODO ace-ets2bundle, framework, compilated apps need to update together
    // this function will be removed after a short transiition periode
    stateMgmtConsole.warn(`markDependentElementsDirty no longer supported. App will work ok, but
        please update your ace-ets2bundle and recompile your application!`);
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
  protected recordDependentUpdate() {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    if (elmtId < 0) {
      // not access recording 
      return;
    }
    stateMgmtConsole.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: recordDependentUpdate on elmtId ${elmtId}.`)
    this.dependentElementIds_.add(elmtId);
  }

  
  public purgeDependencyOnElmtId(rmElmtId: number): void {
    stateMgmtConsole.debug(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']:purgeDependencyOnElmtId ${rmElmtId}`);
    this.dependentElementIds_.delete(rmElmtId);
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
}