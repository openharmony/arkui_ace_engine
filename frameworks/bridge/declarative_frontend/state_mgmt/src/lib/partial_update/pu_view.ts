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
 *
 *  * ViewPU - View for Partial Update
 *
* all definitions in this file are framework internal
*/

/**
 * WeakRef
 * ref to an Object that does not prevent the Object from getting GC'ed
 * current version of tsc does not know about WeakRef
 * but Ark runtime supports it
 *
 */
declare class WeakRef<T extends Object> {
  constructor(o: T);
  deref(): T;
}

type ProvidedVarsMapPU = Map<string, ObservedPropertyAbstractPU<any>>;

// denotes a missing elemntId, this is the case during initial render
const UndefinedElmtId = -1;

// function type of partial update function
type UpdateFunc = (elmtId: number, isFirstRender: boolean) => void;
// function type of recycle node update function
type RecycleUpdateFunc = (elmtId: number, isFirstRender: boolean, recycleNode: ViewPU) => void;

// NativeView
// implemented in C++  for release
// and in utest/view_native_mock.ts for testing
abstract class ViewPU extends NativeViewPartialUpdate
  implements IViewPropertiesChangeSubscriber {

  // Array.sort() converts array items to string to compare them, sigh!
  static readonly compareNumber = (a: number, b: number): number => {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
  };

  private id_: number;

  private parent_: ViewPU = undefined;
  private childrenWeakrefMap_ = new Map<number, WeakRef<ViewPU>>();

  // flag for initgial rendering or re-render on-going.
  private isRenderInProgress: boolean = false;

  // flag if active of inActive
  // inActive means updates are delayed
  private isActive_ : boolean = true;

  private runReuse_: boolean = false;

  private paramsGenerator_: () => Object;

  // flag if {aboutToBeDeletedInternal} is called and the instance of ViewPU has not been GC.
  private isDeleting_: boolean = false;

  private watchedProps: Map<string, (propName: string) => void>
    = new Map<string, (propName: string) => void>();

  private recycleManager: RecycleManager = undefined;

  // @Provide'd variables by this class and its ancestors
  protected providedVars_: ProvidedVarsMapPU;

  // Set of dependent elmtIds that need partial update
  // during next re-render
  protected dirtDescendantElementIds_: Set<number>
    = new Set<number>();

  // registry of update functions
  // the key is the elementId of the Component/Element that's the result of this function
  protected updateFuncByElmtId: Map<number, { updateFunc: UpdateFunc, componentName: string }>
    = new Map<number,{ updateFunc: UpdateFunc, componentName: string }>();

  // set of all @Local/StorageLink/Prop variables owned by this ViwPU
  private ownStorageLinksProps_ : Set<ObservedPropertyAbstractPU<any>> = new Set<ObservedPropertyAbstractPU<any>>();

  // my LocalStorage instance, shared with ancestor Views.
  // create a default instance on demand if none is initialized
  protected localStoragebackStore_: LocalStorage = undefined;

  protected get localStorage_() {
    if (!this.localStoragebackStore_ && this.parent_) {
      stateMgmtConsole.debug(`${this.debugInfo()}: constructor: get localStorage_ : Using LocalStorage instance of the parent View.`);
      this.localStoragebackStore_ = this.parent_.localStorage_;
    }

    if (!this.localStoragebackStore_) {
      stateMgmtConsole.info(`${this.debugInfo()}: constructor: is accessing LocalStorage without being provided an instance. Creating a default instance.`);
      this.localStoragebackStore_ = new LocalStorage({ /* empty */ });
    }
    return this.localStoragebackStore_;
  }

  protected set localStorage_(instance: LocalStorage) {
    if (!instance) {
      // setting to undefined not allowed
      return;
    }
    if (this.localStoragebackStore_) {
      stateMgmtConsole.applicationError(`${this.debugInfo()}: constructor: is setting LocalStorage instance twice. Application error.`);
    }
    this.localStoragebackStore_ = instance;
  }

  /**
   * Create a View
   *
   * 1. option: top level View, specify
   *    - compilerAssignedUniqueChildId must specify
   *    - parent=undefined
   *    - localStorage  must provide if @LocalSTorageLink/Prop variables are used
   *      in this View or descendant Views.
   *
   * 2. option: not a top level View
   *    - compilerAssignedUniqueChildId must specify
   *    - parent must specify
   *    - localStorage do not specify, will inherit from parent View.
   *
  */
  constructor(parent: ViewPU, localStorage: LocalStorage, elmtId : number = -1) {
    super();
    // if set use the elmtId also as the ViewPU object's subscribable id.
    // these matching is requiremrnt for updateChildViewById(elmtId) being able to
    // find the child ViewPU object by given elmtId
    this.id_= elmtId == -1 ? SubscriberManager.MakeId() : elmtId;
    this.providedVars_ = parent ? new Map(parent.providedVars_)
      : new Map<string, ObservedPropertyAbstractPU<any>>();

    this.localStoragebackStore_ = undefined;
    stateMgmtConsole.log(`ViewPU constructor: Creating @Component '${this.constructor.name}' from parent '${parent?.constructor.name}}'`);
    if (parent) {
      // this View is not a top-level View
      this.setCardId(parent.getCardId());
      // Call below will set this.parent_ to parent as well
      parent.addChild(this);
    } else if (localStorage) {
      this.localStorage_ = localStorage;
      stateMgmtConsole.debug(`${this.debugInfo()}: constructor: Using LocalStorage instance provided via @Entry.`);
    }

    SubscriberManager.Add(this);
    stateMgmtConsole.debug(`${this.debugInfo()}: constructor: done`);
  }

  // globally unique id, this is different from compilerAssignedUniqueChildId!
  id__(): number {
    return this.id_;
  }

  updateId(elmtId: number): void {
    this.id_ = elmtId;
  }

  // inform the subscribed property
  // that the View and thereby all properties
  // are about to be deleted
  abstract aboutToBeDeleted(): void;

  aboutToReuse(params: Object): void {}

  aboutToRecycle(): void {}

  // super class will call this function from
  // its aboutToBeDeleted implementation
  protected aboutToBeDeletedInternal(): void {
    stateMgmtConsole.debug(`${this.debugInfo()}: aboutToBeDeletedInternal`);

    // tell UINodeRegisterProxy that all elmtIds under
    // this ViewPU should be treated as already unregistered

    stateMgmtConsole.debug(`${this.constructor.name}: aboutToBeDeletedInternal `);

    UINodeRegisterProxy.accountElmtIdsAsUnregistered(Array.from(this.updateFuncByElmtId.keys()));

    if (this.hasRecycleManager()) {
      this.getRecycleManager().purgeAllCachedRecycleNode();
    }

    // unregister the elmtId of this ViewPU / its CustomNode object
    UINodeRegisterProxy.consume(this.id__());

    // unregistration of ElementIDs
    stateMgmtConsole.debug(`${this.debugInfo()}: onUnRegElementID`);
    // request list of all (global) elmtIds of deleted UINodes that need to be unregistered
    UINodeRegisterProxy.obtainDeletedElmtIds();
    this.purgeDeletedElmtIdsRecursively();
    UINodeRegisterProxy.dump();
    stateMgmtConsole.debug(`${this.debugInfo()}: onUnRegElementID  - DONE`);


    this.updateFuncByElmtId.clear();
    this.watchedProps.clear();
    this.providedVars_.clear();
    this.ownStorageLinksProps_.clear();
    if (this.parent_) {
      this.parent_.removeChild(this);
    }
    this.localStoragebackStore_ = undefined;
    this.isDeleting_ = true;
  }

  
  public debugInfo() : string {
    return `@Component '${this.constructor.name}'[${this.id__()}]`;
  }

  // dump info about known elmtIds to a string
  // use function only for debug output and DFX.
  public debugInfoRegisteredElmtIds() : string {
    let result : string = "";
    let sepa : string ="";
    this.updateFuncByElmtId.forEach((value: { updateFunc: UpdateFunc; componentName: string; }, elmtId: number) => {
      result += `${sepa}${value.componentName}[${elmtId}]`;
      sepa=", ";
    });
    return result;
  }

  // for given elmtIds look up their component name/type and format a string out of this info
  // use function only for debug output and DFX.
  public debugInfoElmtIds(elmtIds : Array<number>) : string {
    let result : string = "";
    let sepa : string ="";
    elmtIds.forEach((elmtId: number) => {
      result += `${sepa}${this.debugInfoElmtId(elmtId)}`;
      sepa=", ";
    });
    return result;
  }

  public debugInfoElmtId(elmtId : number) : string {
    const compName : string | undefined = this.updateFuncByElmtId.get(elmtId)?.componentName;
    return `${compName ? compName : 'unknown component type'}[${elmtId}]`;
  }

  public dumpStateVars() : void {
    stateMgmtConsole.debug(`${this.debugInfo()}:  State variables:`);
    Object.getOwnPropertyNames(this)
      .filter((varName: string) => varName.startsWith("__"))
      .forEach((varName) => {
        const prop: any = Reflect.get(this, varName);
        const observedProp = prop as ObservedPropertyAbstractPU<any>;
        if ("debugInfoDecorator" in prop) {
          stateMgmtConsole.debug(`${observedProp.debugInfoDecorator()} '${observedProp.info()}'[${observedProp.id__()}] ${observedProp.debugInfoSubscribers()}`);
          stateMgmtConsole.debug(`   ... ${observedProp.debugInfoSyncPeers()}`);
          stateMgmtConsole.debug(`   ... ${observedProp.debugInfoDependentElmtIds()}`);
        }
      });
  }

  /**
 * ArkUI engine will call this function when the corresponding CustomNode's active status change.
 * @param active true for active, false for inactive
 */
  public setActiveInternal(active: boolean): void {
    if (this.isActive_ == active) {
      stateMgmtConsole.debug(`${this.debugInfo()}: setActive ${active} with unchanged state - ignoring`);
      return;
    }
    stateMgmtConsole.debug(`${this.debugInfo()}: setActive ${active ? ' inActive -> active' : 'active -> inActive'}`);
    this.isActive_ = active;
    if (this.isActive_) {
      this.onActiveInternal()
    } else {
      this.onInactiveInternal();
    }
  }

  private onActiveInternal(): void {
    if (!this.isActive_) {
      return;
    }

    stateMgmtConsole.debug(`${this.debugInfo()}: onActiveInternal`);
    this.performDelayedUpdate();
    for (const child of this.childrenWeakrefMap_.values()) {
      const childViewPU: ViewPU | undefined = child.deref();
      if (childViewPU) {
        childViewPU.setActiveInternal(this.isActive_);
      }
    }
  }


  private onInactiveInternal(): void {
    if (this.isActive_) {
      return;
    }

    stateMgmtConsole.debug(`${this.debugInfo()}: onInactiveInternal`);
    for (const storageProp of this.ownStorageLinksProps_) {
      storageProp.enableDelayedNotification();
    }

    for (const child of this.childrenWeakrefMap_.values()) {
      const childViewPU: ViewPU | undefined = child.deref();
      if (childViewPU) {
        childViewPU.setActiveInternal(this.isActive_);
      }
    }
  }

  private setParent(parent: ViewPU) {
    if (this.parent_ && parent) {
      stateMgmtConsole.warn(`${this.debugInfo()}: setChild: changing parent to '${parent?.debugInfo()} (unsafe operation)`);
    }
    this.parent_ = parent;
  }

  /**
   * add given child and set 'this' as its parent
   * @param child child to add
   * @returns returns false if child with given child's id already exists
   *
   * framework internal function
   * Note: Use of WeakRef ensures child and parent do not generate a cycle dependency.
   * The add. Set<ids> is required to reliably tell what children still exist.
   */
  public addChild(child: ViewPU): boolean {
    if (this.childrenWeakrefMap_.has(child.id__())) {
      stateMgmtConsole.warn(`${this.debugInfo()}: addChild '${child?.debugInfo()}' id already exists ${child.id__()}. Internal error!`);
      return false;
    }
    this.childrenWeakrefMap_.set(child.id__(), new WeakRef(child));
    child.setParent(this);
    return true;
  }

  /**
   * remove given child and remove 'this' as its parent
   * @param child child to add
   * @returns returns false if child with given child's id does not exist
   */
  public removeChild(child: ViewPU): boolean {
    const hasBeenDeleted = this.childrenWeakrefMap_.delete(child.id__());
    if (!hasBeenDeleted) {
      stateMgmtConsole.warn(`${this.debugInfo()}: removeChild '${child?.debugInfo()}', child id ${child.id__()} not known. Internal error!`);
    } else {
      child.setParent(undefined);
    }
    return hasBeenDeleted;
  }

  /**
   * Retrieve child by given id
   * @param id
   * @returns child if in map and weak ref can still be downreferenced
   */
  public getChildById(id: number) {
    const childWeakRef = this.childrenWeakrefMap_.get(id);
    return childWeakRef ? childWeakRef.deref() : undefined;
  }

  protected abstract purgeVariableDependenciesOnElmtId(removedElmtId: number);
  protected abstract initialRender(): void;
  protected abstract rerender(): void;
  protected abstract updateRecycleElmtId(oldElmtId: number, newElmtId: number): void;
  protected updateStateVars(params: {}) : void {
    stateMgmtConsole.error(`${this.debugInfo()}: updateStateVars unimplemented. Pls upgrade to latest eDSL transpiler version. Application error.`)
  }

  protected initialRenderView(): void {
    this.isRenderInProgress = true;
    this.initialRender();
    this.isRenderInProgress = false;
  }

  private UpdateElement(elmtId: number): void {
    if (elmtId == this.id__()) {
      // do not attempt to update itself.
      // a @Prop can add a dependency of the ViewPU onto itself. Ignore it.
      return;
    }
    // do not process an Element that has been marked to be deleted
    const updateFunc1: { updateFunc: UpdateFunc, componentName: string } | UpdateFunc = this.updateFuncByElmtId.get(elmtId);
    let updateFunc: UpdateFunc | undefined;

    if (typeof updateFunc1 === 'function') {
      // adapt old toolchains
      updateFunc = updateFunc1
    } else {
      updateFunc = updateFunc1?.updateFunc
    }
    const componentName : string = updateFunc1 && updateFunc1.componentName ? updateFunc1.componentName : "unknown component type";

    if ((updateFunc == undefined) || (typeof updateFunc !== "function")) {
      stateMgmtConsole.error(`${this.debugInfo()}: update function of elmtId ${elmtId} not found, internal error!`);
    } else {
      stateMgmtConsole.debug(`${this.debugInfo()}: updateDirtyElements: re-render of ${componentName} elmtId ${elmtId} start ...`);
      this.isRenderInProgress = true;
      updateFunc(elmtId, /* isFirstRender */ false);
      // continue in native JSView
      // Finish the Update in JSView::JsFinishUpdateFunc
      // this function appends no longer used elmtIds (as receded by VSP) to the given allRmElmtIds array
      this.finishUpdateFunc(elmtId);
      this.isRenderInProgress = false;
      stateMgmtConsole.debug(`${this.debugInfo()}: updateDirtyElements: re-render of ${componentName} elmtId ${elmtId} - DONE`);
    }
  }

  /**
   * force a complete rerender / update by executing all update functions
   * exec a regular rerender first
   *
   * @param deep recurse all children as well
   *
   * framework internal functions, apps must not call
   */
  public forceCompleteRerender(deep: boolean = false): void {
    stateMgmtConsole.warn(`${this.debugInfo()}: forceCompleteRerender - start.`);

    // see which elmtIds are managed by this View
    // and clean up all book keeping for them
    this.purgeDeletedElmtIds();

    Array.from(this.updateFuncByElmtId.keys()).sort(ViewPU.compareNumber).forEach(elmtId => this.UpdateElement(elmtId));

    if (deep) {
      this.childrenWeakrefMap_.forEach((weakRefChild: WeakRef<ViewPU>) => {
        const child = weakRefChild.deref();
        if (child) {
          (child as ViewPU).forceCompleteRerender(true);
        }
      });
    }
    stateMgmtConsole.warn(`${this.debugInfo()}: forceCompleteRerender - end`);
  }

  /**
   * force a complete rerender / update on specific node by executing update function.
   *
   * @param elmtId which node needs to update.
   *
   * framework internal functions, apps must not call
   */
  public forceRerenderNode(elmtId: number): void {
    // see which elmtIds are managed by this View
    // and clean up all book keeping for them
    this.purgeDeletedElmtIds();
    this.UpdateElement(elmtId);

    // remove elemtId from dirtDescendantElementIds.
    this.dirtDescendantElementIds_.delete(elmtId);
  }

  public updateStateVarsOfChildByElmtId(elmtId, params: Object) : void {
    stateMgmtConsole.debug(`${this.debugInfo()}: updateChildViewById(${elmtId}) - start`);

    if (elmtId<0) {
      stateMgmtConsole.warn(`${this.debugInfo()}: updateChildViewById(${elmtId}) - invalid elmtId - internal error!`);
      return ;
    }
    let child : ViewPU = this.getChildById(elmtId);
    if (!child) {
      stateMgmtConsole.warn(`${this.debugInfo()}: updateChildViewById(${elmtId}) - no child with this elmtId - internal error!`);
      return;
    }
    child.updateStateVars(params);
    stateMgmtConsole.debug(`${this.debugInfo()}: updateChildViewById(${elmtId}) - end`);
  }

  // implements IMultiPropertiesChangeSubscriber
  viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void {
    stateMgmtTrace.scopedTrace(() => {
      if (this.isRenderInProgress) {
        stateMgmtConsole.applicationError(`${this.debugInfo()}: State variable '${varName}' has changed during render! It's illegal to change @Component state while build (initial render or re-render) is on-going. Application error!`);
      }

      this.syncInstanceId();

      if (dependentElmtIds.size && !this.isFirstRender()) {
        if (!this.dirtDescendantElementIds_.size && !this.runReuse_) {
          // mark ComposedElement dirty when first elmtIds are added
          // do not need to do this every time
          this.markNeedUpdate();
        }
        stateMgmtConsole.debug(`${this.debugInfo()}: viewPropertyHasChanged property: elmtIds that need re-render due to state variable change: ${this.debugInfoElmtIds(Array.from(dependentElmtIds))} .`)
        for (const elmtId of dependentElmtIds) {
          this.dirtDescendantElementIds_.add(elmtId);
        }
        stateMgmtConsole.debug(`   ... updated full list of elmtIds that need re-render [${this.debugInfoElmtIds(Array.from(this.dirtDescendantElementIds_))}].`)
      } else {
        stateMgmtConsole.debug(`${this.debugInfo()}: viewPropertyHasChanged: state variable change adds no elmtIds for re-render`);
        stateMgmtConsole.debug(`   ... unchanged full list of elmtIds that need re-render [${this.debugInfoElmtIds(Array.from(this.dirtDescendantElementIds_))}].`)
      }

      let cb = this.watchedProps.get(varName)
      if (cb) {
        stateMgmtConsole.debug(`   ... calling @Watch function`);
        cb.call(this, varName);
      }

      this.restoreInstanceId();
    }, "ViewPU.viewPropertyHasChanged", this.constructor.name, varName, dependentElmtIds.size);
  }


  private performDelayedUpdate(): void {
    stateMgmtTrace.scopedTrace(() => {
    stateMgmtConsole.debug(`${this.debugInfo()}: performDelayedUpdate start ...`);
    this.syncInstanceId();

    for (const storageProp of this.ownStorageLinksProps_) {
      const changedElmtIds = storageProp.moveElmtIdsForDelayedUpdate();
      if (changedElmtIds) {
        const varName = storageProp.info();
        if (changedElmtIds.size && !this.isFirstRender()) {
          for (const elmtId of changedElmtIds) {
            this.dirtDescendantElementIds_.add(elmtId);
          }
        }

        stateMgmtConsole.debug(`${this.debugInfo()}: performDelayedUpdate: all elmtIds that need re-render [${Array.from(this.dirtDescendantElementIds_).toString()}].`)

        const cb = this.watchedProps.get(varName)
        if (cb) {
          stateMgmtConsole.debug(`   ... calling @Watch function`);
          cb.call(this, varName);
        }
      }
    } // for all ownStorageLinksProps_
    this.restoreInstanceId();

    if (this.dirtDescendantElementIds_.size) {
      this.markNeedUpdate();
    }

    }, "ViewPU.performDelayedUpdate", this.constructor.name);
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
  protected addProvidedVar<T>(providedPropName: string, store: ObservedPropertyAbstractPU<T>) {
    if (this.providedVars_.has(providedPropName)) {
      throw new ReferenceError(`${this.constructor.name}: duplicate @Provide property with name ${providedPropName}.
      Property with this name is provided by one of the ancestor Views already.`);
    }
    this.providedVars_.set(providedPropName, store);
  }

  /**
   * Method for the sub-class to call from its constructor for resolving
   *       a @Consume variable and initializing its backing store
   *       with the SyncedPropertyTwoWay<T> object created from the
   *       @Provide variable's backing store.
   * @param providedPropName the name of the @Provide'd variable.
   *     This is either the @Consume decorator parameter, or variable name.
   * @param consumeVarName the @Consume variable name (not the
   *            @Consume decorator parameter)
   * @returns initializing value of the @Consume backing store
   */
  protected initializeConsume<T>(providedPropName: string,
    consumeVarName: string): ObservedPropertyAbstractPU<T> {
    let providedVarStore : ObservedPropertyAbstractPU<any> = this.providedVars_.get(providedPropName);
    if (providedVarStore === undefined) {
      throw new ReferenceError(`${this.debugInfo()} missing @Provide property with name ${providedPropName}.
          Fail to resolve @Consume(${providedPropName}).`);
    }

    const factory = <T>(source: ObservedPropertyAbstract<T>) => {
      const result : ObservedPropertyAbstractPU<T> = ((source instanceof ObservedPropertySimple) || (source instanceof ObservedPropertySimplePU))
          ? new SynchedPropertyObjectTwoWayPU<T>(source, this, consumeVarName) 
          : new SynchedPropertyObjectTwoWayPU<T>(source, this, consumeVarName);
      return result;
    };
    return providedVarStore.createSync(factory) as  ObservedPropertyAbstractPU<T>;
  }


  /**
   * given the elmtId of a child or child of child within this custom component
   * remember this component needs a partial update
   * @param elmtId
   */
  public markElemenDirtyById(elmtId: number): void {
    // TODO ace-ets2bundle, framework, compilated apps need to update together
    // this function will be removed after a short transiition periode
    stateMgmtConsole.applicationError(`${this.debugInfo()}: markElemenDirtyById no longer supported.
        Please update your ace-ets2bundle and recompile your application. Application error!`);
  }

  /**
   * For each recorded dirty Element in this custom component
   * run its update function
   *
   */
  public updateDirtyElements() {
    do {
        stateMgmtConsole.debug(`${this.debugInfo()}: updateDirtyElements (re-render): sorted dirty elmtIds: ${Array.from(this.dirtDescendantElementIds_).sort(ViewPU.compareNumber)}, starting ....`);

        // see which elmtIds are managed by this View
        // and clean up all book keeping for them
        this.purgeDeletedElmtIds();

        // process all elmtIds marked as needing update in ascending order.
        // ascending order ensures parent nodes will be updated before their children
        // prior cleanup ensure no already deleted Elements have their update func executed
        Array.from(this.dirtDescendantElementIds_).sort(ViewPU.compareNumber).forEach(elmtId => {
            this.UpdateElement(elmtId);
            this.dirtDescendantElementIds_.delete(elmtId);
        });

        if (this.dirtDescendantElementIds_.size) {
          stateMgmtConsole.applicationError(`${this.debugInfo()}: New UINode objects added to update queue while re-render! - Likely caused by @Component state change during build phase, not allowed. Application error!`);
        }
    } while(this.dirtDescendantElementIds_.size);
    stateMgmtConsole.debug(`${this.debugInfo()}: updateDirtyElements (re-render) - DONE, dump of ViewPU in next lines`);
    this.dumpStateVars();
  }

  //  given a list elementIds removes these from state variables dependency list and from elmtId -> updateFunc map
  protected purgeDeletedElmtIds(): void {
    stateMgmtConsole.debug(`purgeDeletedElmtIds @Component '${this.constructor.name}' (id: ${this.id__()}) `)
    // request list of all (global) elmtIds of deleted UINodes that need to be unregistered
    UINodeRegisterProxy.obtainDeletedElmtIds();
    UINodeRegisterProxy.dump();
    if (!UINodeRegisterProxy.hasElmtIdsPendingUnregister()) {
      stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIds - no elmtIds to unregister (globally) - done!`)
      return;
    }
    this.purgeDeletedElmtIdsInternal();
    UINodeRegisterProxy.dump();
  }

  // function called from elementRegister to the root ViewPU of the page
  public purgeDeletedElmtIdsRecursively (): void {
    stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIdsRecursively  - start`);
    // request list of all (global) elmtIds of deleted UINodes that need to be unregistered
    UINodeRegisterProxy.obtainDeletedElmtIds();
    this.purgeDeletedElmtIdsRecursivelyInternal();
    UINodeRegisterProxy.dump();
    stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIdsRecursively  - DONE`);
    this.dumpStateVars();
  }


  private purgeDeletedElmtIdsRecursivelyInternal() : void {
    if (!UINodeRegisterProxy.hasElmtIdsPendingUnregister()) {
      stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIdsRecursively - registry has no more elmtIds needing unregister, therefore, can terminate recursion.`);
      return;
    }
    this.purgeDeletedElmtIdsInternal();

    this.childrenWeakrefMap_.forEach((weakRefChild: WeakRef<ViewPU>) => {
      const child = weakRefChild.deref();
      if (child) {
        if (!UINodeRegisterProxy.hasElmtIdsPendingUnregister()) {
          stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIdsRecursively - registry has no more elmtIds needing unregister (globally), therefore, can terminate recursion.`); 
          return;
        }
        (child as ViewPU).purgeDeletedElmtIdsRecursively();
      }
    });
  }

  private purgeDeletedElmtIdsInternal(): void {
    stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIds -  start.`);

    const elmtIdsOfThisView = this.updateFuncByElmtId.keys();
    for (const rmElmtId of elmtIdsOfThisView) {
      if (UINodeRegisterProxy.consume(rmElmtId)) {
        stateMgmtConsole.debug(`   ... purging elmtId ${rmElmtId}: remove it from updateFuncByElmtId and from state variables' dependency lists.`);
        // remove entry from Map elmtId -> update function
        this.updateFuncByElmtId.delete(rmElmtId);

        // for each state var, remove dependent elmtId (if present)
        // purgeVariableDependenciesOnElmtId needs to be generated by the compiler
        this.purgeVariableDependenciesOnElmtIdOwnFunc(rmElmtId);

        if (!UINodeRegisterProxy.hasElmtIdsPendingUnregister()) {
          stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIdsInternal - registry has no more elmtIds needing unregister (globally), therefore, can terminate for this @Component early.`);
          return;
        }
      } // for all elmtIds that need to unregister

    }

    stateMgmtConsole.debug(`${this.debugInfo()}: purgeDeletedElmtIds: DONE `);
    stateMgmtConsole.debug(`   ... remaining known child components and their elmtIds ${this.debugInfoRegisteredElmtIds()} .`);
  }

    purgeVariableDependenciesOnElmtIdOwnFunc(elmtId : number) : void {
      Object.getOwnPropertyNames(this).filter((varName => varName.startsWith("__"))).forEach((stateVarName) => {
        let variable = Reflect.get(this, stateVarName) as Object;
        if ("purgeDependencyOnElmtId" in variable) {
          (variable as ObservedPropertyAbstractPU<any>).purgeDependencyOnElmtId(elmtId);
        }
      });
    }

  // executed on first render only
  // kept for backward compatibility with old ace-ets2bundle
  public observeComponentCreation(compilerAssignedUpdateFunc: UpdateFunc): void {
    if (this.isDeleting_) {
      stateMgmtConsole.error(`View ${this.constructor.name} elmtId ${this.id__()} is already in process of destrucion, will not execute observeComponentCreation `);
      return;
    }
    const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    stateMgmtConsole.debug(`${this.debugInfo()}: First render for elmtId ${elmtId} start ....`);
    compilerAssignedUpdateFunc(elmtId, /* is first render */ true);
    // in observeComponentCreation function we do not get info about the component name, in 
    // observeComponentCreation2 we do.
    this.updateFuncByElmtId.set(elmtId, { updateFunc: compilerAssignedUpdateFunc, componentName: "unknown" }  );
    stateMgmtConsole.debug(`${this.debugInfo()}: First render for elmtId ${elmtId} - DONE.`);
  }

  // executed on first render only
  // added July 2023, replaces observeComponentCreation
  // classObject is the ES6 class object , mandatory to specify even the class lacks the pop function.
  // - prototype : Object is present for every ES6 class
  // - pop : () => void, static function present for JSXXX classes such as Column, TapGesture, etc.
  public observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: { prototype : Object, pop?: () => void }): void {
    if (this.isDeleting_) {
      stateMgmtConsole.error(`View ${this.constructor.name} elmtId ${this.id__()} is already in process of destrucion, will not execute observeComponentCreation2 `);
      return;
    }
    const _componentName : string =  (classObject && ("name" in classObject)) ? Reflect.get(classObject, "name") as string : "unspecified UINode";
    const _popFunc : () => void = (classObject && "pop" in classObject) ? classObject.pop! : () => {};
    const updateFunc = (elmtId: number, isFirstRender: boolean) => {
      stateMgmtConsole.debug(`${this.debugInfo()}: ${isFirstRender ? `First render` : `Re-render/update`} start ....`);
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      compilerAssignedUpdateFunc(elmtId, isFirstRender);
      if (!isFirstRender) {
        _popFunc();
      }
      ViewStackProcessor.StopGetAccessRecording();
      stateMgmtConsole.debug(`${this.debugInfo()}: ${isFirstRender ? `First render` : `Re-render/update`} - DONE ....`);
    };

    const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();

    updateFunc(elmtId, /* is first render */ true );
    this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, componentName: _componentName } );
  }


  getOrCreateRecycleManager(): RecycleManager {
    if (!this.recycleManager) {
      this.recycleManager = new RecycleManager
    }
    return this.recycleManager;
  }

  getRecycleManager(): RecycleManager {
    return this.recycleManager;
  }

  hasRecycleManager(): boolean {
    return !(this.recycleManager === undefined);
  }

  initRecycleManager(): void {
    if (this.recycleManager) {
      stateMgmtConsole.error(`${this.debugInfo()}: init recycleManager multiple times. Internal error.`);
      return;
    }
    this.recycleManager = new RecycleManager;
  }

  /**
   * @function observeRecycleComponentCreation
   * @description custom node recycle creation
   * @param name custom node name
   * @param recycleUpdateFunc custom node recycle update which can be converted to a normal update function
   * @return void
   */
  public observeRecycleComponentCreation(name: string, recycleUpdateFunc: RecycleUpdateFunc): void {
    // convert recycle update func to update func
    const compilerAssignedUpdateFunc: UpdateFunc = (element, isFirstRender) => {
      recycleUpdateFunc(element, isFirstRender, undefined)
    };
    let node: ViewPU;
    // if there is no suitable recycle node, run a normal creation function.
    if (!this.hasRecycleManager() || !(node = this.getRecycleManager().popRecycleNode(name))) {
      stateMgmtConsole.debug(`${this.constructor.name}[${this.id__()}]: cannot init node by recycle, crate new node`);
      this.observeComponentCreation(compilerAssignedUpdateFunc);
      return;
    }

    // if there is a suitable recycle node, run a recycle update function.
    const newElmtId: number = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    const oldElmtId: number = node.id__();
    // store the current id and origin id, used for dirty element sort in {compareNumber}
    recycleUpdateFunc(newElmtId, /* is first render */ true, node);
    const oldEntry: { updateFunc: UpdateFunc, componentName: string } | undefined = this.updateFuncByElmtId.get(oldElmtId);
    this.updateFuncByElmtId.delete(oldElmtId);
    this.updateFuncByElmtId.set(newElmtId, {
      updateFunc: compilerAssignedUpdateFunc,
      componentName: oldEntry ? oldEntry.componentName : "unknown"
    });
    node.updateId(newElmtId);
    node.updateRecycleElmtId(oldElmtId, newElmtId);
    SubscriberManager.UpdateRecycleElmtId(oldElmtId, newElmtId);
  }

  aboutToReuseInternal() {
    this.runReuse_ = true;
    stateMgmtTrace.scopedTrace(() => {
      this.aboutToReuse(this?.paramsGenerator_());
    }, "aboutToReuse", this.constructor.name);
    this.updateDirtyElements();
    this.childrenWeakrefMap_.forEach((weakRefChild) => {
      const child = weakRefChild.deref();
      if (child) {
        child.aboutToReuseInternal();
      }
    });
    this.runReuse_ = false;
  }

  aboutToRecycleInternal() {
    this.runReuse_ = true;
    stateMgmtTrace.scopedTrace(() => {
      this.aboutToRecycle();
    }, "aboutToRecycle", this.constructor.name);
    this.childrenWeakrefMap_.forEach((weakRefChild) => {
      const child = weakRefChild.deref();
      if (child) {
        child.aboutToRecycleInternal();
      }
    });
    this.runReuse_ = false;
  }

  // add current JS object to it's parent recycle manager
  public recycleSelf(name: string): void {
    if (this.parent_ && !this.parent_.isDeleting_) {
      this.parent_.getOrCreateRecycleManager().pushRecycleNode(name, this);
    } else {
      this.resetRecycleCustomNode();
      stateMgmtConsole.error(`${this.constructor.name}[${this.id__()}]: recycleNode must have a parent`);
    }
  }

  // performs the update on a branch within if() { branch } else if (..) { branch } else { branch }
  public ifElseBranchUpdateFunction(branchId : number, branchfunc : () => void ) : void {
    const oldBranchid : number = If.getBranchId();

    if (branchId == oldBranchid) {
      stateMgmtConsole.debug(`${this.debugInfo()}: ifElseBranchUpdateFunction: IfElse branch unchanged, no work to do.`);
      return;
    }

    // branchid identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
    // ifElseNode stores the most recent branch, so we can compare
    // removedChildElmtIds will be filled with the elmtIds of all childten and their children will be deleted in response to if .. else chnage
    let removedChildElmtIds = new Array<number>();
    If.branchId(branchId, removedChildElmtIds);

    // purging these elmtIds from state mgmt will make sure no more update function on any deleted child wi;ll be executed
    stateMgmtConsole.debug(`ViewPU ifElseBranchUpdateFunction: elmtIds need unregister after if/else branch switch: ${JSON.stringify(removedChildElmtIds)}`);
    this.purgeDeletedElmtIds();

    branchfunc();
  }

   /**
    Partial updates for ForEach.
    * @param elmtId ID of element.
    * @param itemArray Array of items for use of itemGenFunc.
    * @param itemGenFunc Item generation function to generate new elements. If index parameter is
    *                    given set itemGenFuncUsesIndex to true.
    * @param idGenFunc   ID generation function to generate unique ID for each element. If index parameter is
    *                    given set idGenFuncUsesIndex to true.
    * @param itemGenFuncUsesIndex itemGenFunc optional index parameter is given or not.
    * @param idGenFuncUsesIndex idGenFunc optional index parameter is given or not.
    */
  public forEachUpdateFunction(elmtId : number,
    itemArray: Array<any>,
    itemGenFunc: (item: any, index?: number) => void,
    idGenFunc?: (item: any, index?: number) => string,
    itemGenFuncUsesIndex: boolean = false,
    idGenFuncUsesIndex: boolean = false) : void {

    stateMgmtConsole.debug(`${this.debugInfo()}: forEachUpdateFunction (ForEach re-render) start ...`);

    if (itemArray === null || itemArray === undefined) {
      stateMgmtConsole.applicationError(`${this.debugInfo()}: forEachUpdateFunction (ForEach re-render): input array is null or undefined error. Application error!`);
      return;
    }

    if (itemGenFunc === null || itemGenFunc === undefined) {
      stateMgmtConsole.applicationError(`${this.debugInfo()}: forEachUpdateFunction (ForEach re-render): Item generation function missing. Application error!`);
      return;
    }

    if (idGenFunc === undefined) {
      stateMgmtConsole.debug(`${this.debugInfo()}: forEachUpdateFunction: providing default id gen function `);
      idGenFuncUsesIndex = true;
      // catch possible error caused by Stringify and re-throw an Error with a meaningful (!) error message
      idGenFunc = (item: any, index : number) => {
        try {
          return `${index}__${JSON.stringify(item)}`;
        } catch(e) {
          throw new Error (`${this.debugInfo()}: ForEach id ${elmtId}: use of default id generator function not possible on provided data structure. Need to specify id generator function (ForEach 3rd parameter). Application Error!`)
        }
      }
    }

    let diffIndexArray = []; // New indexes compared to old one.
    let newIdArray = [];
    let idDuplicates = [];
    const arr = itemArray; // just to trigger a 'get' onto the array

    // ID gen is with index.
    if (idGenFuncUsesIndex) {
      // Create array of new ids.
      arr.forEach((item, indx) => {
        newIdArray.push(idGenFunc(item, indx));
      });
    }
    else {
      // Create array of new ids.
      arr.forEach((item, index) => {
        newIdArray.push(`${itemGenFuncUsesIndex ? index + '_':''}` + idGenFunc(item));
      });
    }

    // Set new array on C++ side.
    // C++ returns array of indexes of newly added array items.
    // these are indexes in new child list.
    ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates);

    // Its error if there are duplicate IDs.
    if (idDuplicates.length > 0) {
      idDuplicates.forEach((indx) => {
        stateMgmtConsole.error(`Error: ${newIdArray[indx]} generated for ${indx}${indx < 4 ? indx == 2 ? "nd" : "rd" : "th"} array item ${arr[indx]}.`);
      });
      stateMgmtConsole.applicationError(`${this.debugInfo()}: Ids generated by the ForEach id gen function must be unique. Application error!`);
    }

    stateMgmtConsole.debug(`${this.debugInfo()}: forEachUpdateFunction: diff indexes ${JSON.stringify(diffIndexArray)} . `);

    // Item gen is with index.
    stateMgmtConsole.debug(`   ... item Gen ${itemGenFuncUsesIndex ? 'with' : "without"} index`);
    // Create new elements if any.
    diffIndexArray.forEach((indx) => {
      ForEach.createNewChildStart(newIdArray[indx], this);
      if (itemGenFuncUsesIndex) {
        itemGenFunc(arr[indx], indx);
      } else {
        itemGenFunc(arr[indx]);
      }
      ForEach.createNewChildFinish(newIdArray[indx], this);
    });
    stateMgmtConsole.debug(`${this.debugInfo()}: forEachUpdateFunction (ForEach re-render) - DONE.`);
  }

  /**
     * CreateStorageLink and CreateStorageLinkPU are used by the implementation of @StorageLink and
     * @LocalStotrageLink in full update and partial update solution respectively.
     * These are not part of the public AppStorage API , apps should not use.
     * @param storagePropName - key in LocalStorage
     * @param defaultValue - value to use when creating a new prop in the LocalStotage
     * @param owningView - the View/ViewPU owning the @StorageLink/@LocalStorageLink variable
     * @param viewVariableName -  @StorageLink/@LocalStorageLink variable name
     * @returns SynchedPropertySimple/ObjectTwoWay/PU
     */
  public createStorageLink<T>(storagePropName: string, defaultValue: T, viewVariableName: string): ObservedPropertyAbstractPU<T> {
    const appStorageLink = AppStorage.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : (source instanceof ObservedPropertySimple)
          ? new SynchedPropertyObjectTwoWayPU<T>(source, this, viewVariableName)
          : new SynchedPropertyObjectTwoWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    this.ownStorageLinksProps_.add(appStorageLink);
    return appStorageLink;
  }

  public createStorageProp<T>(storagePropName: string, defaultValue: T, viewVariableName: string): ObservedPropertyAbstractPU<T> {
    const appStorageProp = AppStorage.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : (source instanceof ObservedPropertySimple)
          ? new SynchedPropertyObjectOneWayPU<T>(source, this, viewVariableName)
          : new SynchedPropertyObjectOneWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    this.ownStorageLinksProps_.add(appStorageProp);
    return appStorageProp;
  }

  public createLocalStorageLink<T>(storagePropName: string, defaultValue: T,
    viewVariableName: string): ObservedPropertyAbstractPU<T> {
      const localStorageLink =  this.localStorage_.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : (source instanceof ObservedPropertySimple)
          ? new SynchedPropertyObjectTwoWayPU<T>(source, this, viewVariableName)
          : new SynchedPropertyObjectTwoWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    this.ownStorageLinksProps_.add(localStorageLink);
    return localStorageLink;
}

  public createLocalStorageProp<T>(storagePropName: string, defaultValue: T,
    viewVariableName: string): ObservedPropertyAbstractPU<T> {
      const localStorageProp = this.localStorage_.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : (source instanceof ObservedPropertySimple)
          ? new SynchedPropertyObjectOneWayPU<T>(source, this, viewVariableName)
          : new SynchedPropertyObjectOneWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    this.ownStorageLinksProps_.add(localStorageProp);
    return localStorageProp;
  }
}
