/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

type ProvidedVarsMap = Map<string, ObservedPropertyAbstract<any>>;
type Context = any;

// Nativeview
// implemented in C++  for release
// and in utest/view_native_mock.ts for testing
abstract class View extends NativeView implements
  IMultiPropertiesChangeSubscriber, IMultiPropertiesReadSubscriber {

  private id_: number;
  private propsUsedForRender: Set<string> = new Set<string>();
  private isRenderingInProgress: boolean = false;

  private watchedProps: Map<string, (propName: string) => void>
    = new Map<string, (propName: string) => void>();

  // @Provide'd variables by this class and its ancestors
  protected providedVars_: ProvidedVarsMap;


  constructor(compilerAssignedUniqueChildId: string, parent: View) {
    super(compilerAssignedUniqueChildId, parent);
    this.id_ = SubscriberManager.Get().MakeId();
    this.providedVars_ = parent ? new Map(parent.providedVars_)
      : new Map<string, ObservedPropertyAbstract<any>>();
    SubscriberManager.Get().add(this);
    console.debug(`${this.constructor.name}: constructor done`);
  }

  // globally unique id, this is different from compilerAssignedUniqueChildId!
  id__(): number {
    return this.id_;
  }

  // inform the subscribed property
  // that the View and thereby all properties
  // are about to be deleted
  abstract aboutToBeDeleted(): void;

  abstract updateWithValueParams(params: Object): void;

  propertyHasChanged(info?: PropertyInfo): void {
    if (info) {
      if (this.propsUsedForRender.has(info)) {
        console.debug(`${this.constructor.name}: propertyHasChanged ['${info || "unknowm"}']. View needs update`);
        this.markNeedUpdate();
      } else {
        console.debug(`${this.constructor.name}: propertyHasChanged ['${info || "unknowm"}']. View does NOT need update`);
      }
      let cb = this.watchedProps.get(info)
      if (cb) {
        console.debug(`${this.constructor.name}: propertyHasChanged ['${info || "unknowm"}']. calling @Watch function`);
        cb.call(this, info);
      }
    } // if info avail.
  }

  propertyRead(info?: PropertyInfo): void {
    console.debug(`${this.constructor.name}: propertyRead ['${info || "unknowm"}'].`);
    if (info && (info != "unknown") && this.isRenderingInProgress) {
      this.propsUsedForRender.add(info);
    }
  }


  // for test purposes
  public propertiesNeededToRender(): Set<string> {
    return this.propsUsedForRender;
  }

  public aboutToRender(): void {
    console.log(`${this.constructor.name}: aboutToRender`);
    // reset
    this.propsUsedForRender = new Set<string>();
    this.isRenderingInProgress = true;
  }

  public aboutToContinueRender(): void {
    // do not reset
    //this.propsUsedForRender = new Set<string>();
    this.isRenderingInProgress = true;
  }

  public onRenderDone(): void {
    this.isRenderingInProgress = false;
    console.log(`${this.constructor.name}: onRenderDone: render performed get access to these properties: ${JSON.stringify(Array.from(this.propsUsedForRender))}.`);
  }


  /**
   * Function to be called from the constructor of the sub component
   * to register a @Watch varibale
   * @param propStr name of the variable. Note from @Provide and @Consume this is
   *      the variable name and not the alias!
   * @param callback application defined member function of sub-class
   */
  protected declareWatch(propStr: string, callback: (propName: string) => void): void {
    this.watchedProps.set(propStr, callback);
  }

  /**
   * This View @Provide's a variable under given name
   * Call this function from the constructor of the sub class
   * @param providedPropName either the variable name or the alias defined as
   *        decorator param
   * @param store the backing store object for this variable (not the get/set variable!)
   */
  protected addProvidedVar<T>(providedPropName: string, store: ObservedPropertyAbstract<T>) {
    if (this.providedVars_.has(providedPropName)) {
      throw new ReferenceError(`${this.constructor.name}: duplicate @Provide property with name ${providedPropName}.
      Property with this name is provided by one of the ancestor Views already.`);
    }
    this.providedVars_.set(providedPropName, store);
  }

  /**
   * Method for the sub-class to call from its constructor for resolving
   *       a @Consume variable and initializing its backing store
   *       with the yncedPropertyTwoWay<T> object created from the
   *       @Provide variable's backing store.
   * @param providedPropName the name of the @Provide'd variable.
   *     This is either the @Consume decortor parameter, or variable name.
   * @param consumeVarName the @Consume variable name (not the
   *            @Consume decortor parameter)
   * @returns initiaizing value of the @Consume backing store
   */
  protected initializeConsume<T>(providedPropName: string,
    consumeVarName: string): ObservedPropertyAbstract<T> {
    let providedVarStore = this.providedVars_.get(providedPropName);
    if (providedVarStore === undefined) {
      throw new ReferenceError(`${this.constructor.name}: missing @Provide property with name ${providedPropName}.
     Fail to resolve @Consume(${providedPropName}).`);
    }

    return providedVarStore.createLink(this, consumeVarName);
  }
}

function getContentStorage(view: View) : ContentStorage {
  return view.getContentStorage();
}

function getContext(view: View) : Context {
  return view.getContext();
}
