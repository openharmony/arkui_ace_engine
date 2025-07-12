/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

type DFXCommand = { what: string, viewId: number, isRecursive: boolean };
type RecycleUpdateFunc = (elmtId: number, isFirstRender: boolean, recycleNode: ViewPU) => void;
type PrebuildFunc = () => void;

/**
 * A decorator function that sets the static `isReusable_` property to `true`
 * on the provided class. This decorator is automatically invoked when the generated component
 * class in the transpiler has the `@Reusable` decorator prefix, as below:
 * @Reusable
 * class MyComponent { }
 */
function Reusable<T extends Constructor>(BaseClass: T): T {
  stateMgmtConsole.debug(`@Reusable ${BaseClass.name}: Redefining isReusable_ as true.`);
  Reflect.defineProperty(BaseClass.prototype, 'isReusable_', {
    get: () => {
      return true;
    }
  });
  return BaseClass;
}

class SyncedViewRegistry {
  public static dirtyNodesList: Set<WeakRef<ViewPU>> = new Set<WeakRef<ViewPU>>();
  
  // map viewPU -> weakref<ViewPU>
  private static wmap_ = new WeakMap();
  
  public static addSyncedUpdateDirtyNodes(view: ViewPU): void {
    let weakRef = this.wmap_.get(view)
    if (!weakRef) {
      SyncedViewRegistry.wmap_.set(view, weakRef = new WeakRef(view));
    }
    SyncedViewRegistry.dirtyNodesList.add(weakRef);
    stateMgmtConsole.debug(`SyncedViewRegistry addSyncedUpdateDirtyNodes ${view.debugInfo__()}, syncDirtySize: ${SyncedViewRegistry.dirtyNodesList.size}`);
  }
}

abstract class ViewPU extends PUV2ViewBase
  implements IViewPropertiesChangeSubscriber, IView {

  // flag for initial rendering or re-render on-going.
  private isRenderInProgress: boolean = false;

  // flag for initial rendering being done
  private isInitialRenderDone: boolean = false;

  private runReuse_: boolean = false;

  public paramsGenerator_: () => Object;

  private watchedProps: Map<string, (propName: string) => void> = new Map<string, (propName: string) => void>();

  private recycleManager_: RecycleManager = undefined;

  public hasBeenRecycled_: boolean = false;

  private preventRecursiveRecycle_: boolean = false;

  private delayRecycleNodeRerender: boolean = false;

  private delayRecycleNodeRerenderDeep: boolean = false;

  // store the current key -> consume, which has the default value
  public defaultConsume_: Map<string, SynchedPropertyTwoWayPU<any>> = new Map<string, SynchedPropertyTwoWayPU<any>>();

  // store the current key -> consume, which has reconnect to the provide
  public reconnectConsume_: Map<string, SynchedPropertyTwoWayPU<any>> = new Map<string, SynchedPropertyTwoWayPU<any>>();

  // @Provide'd variables by this class and its ancestors
  protected providedVars_: Map<string, ObservedPropertyAbstractPU<any>> = new Map<string, ObservedPropertyAbstractPU<any>>();

  // Set of elmtIds that need re-render
  public dirtyElementIdsNeedsUpdateSynchronously_: Set<number> = new Set<number>();

  // my LocalStorage instance, shared with ancestor Views.
  // create a default instance on demand if none is initialized
  protected localStoragebackStore_: LocalStorage = undefined;

  private ownObservedPropertiesStore__?: Set<ObservedPropertyAbstractPU<any>>;

  private get ownObservedPropertiesStore_() {
    if (!this.ownObservedPropertiesStore__) {
      // lazy init
      this.ownObservedPropertiesStore__ = new Set<ObservedPropertyAbstractPU<any>>();
      this.obtainOwnObservedProperties();
    }
    return this.ownObservedPropertiesStore__;
  }

  protected obtainOwnObservedProperties(): void {
    let usesStateMgmtVersion = 0;
    Object.getOwnPropertyNames(this)
      .filter((propName) => {
        // do not include backing store, and ObserveV2/MonitorV2/ComputedV2 meta data objects
        return (propName.startsWith('__') &&
          !propName.startsWith(ObserveV2.OB_PREFIX) &&
          !propName.startsWith(MonitorV2.WATCH_PREFIX) &&
          !propName.startsWith(ComputedV2.COMPUTED_PREFIX));
      })
      .forEach((propName) => {
        const stateVar = Reflect.get(this, propName) as Object;
        if (stateVar && typeof stateVar === 'object' && 'notifyPropertyHasChangedPU' in stateVar) {
          stateMgmtConsole.debug(`... add state variable ${propName} to ${stateVar}`);
          this.ownObservedPropertiesStore_.add(stateVar as unknown as ObservedPropertyAbstractPU<any>);
          usesStateMgmtVersion = 2;
        } else {
          stateMgmtConsole.debug(`${this.debugInfo__()} ${propName} application may use an unregular naming style, or stateVar may be Non-Object.`);
        }
      });

    if (this.isViewV2 === true) {
      if (usesStateMgmtVersion === 2) {
        const error = `${this.debugInfo__()}: mixed use of stateMgmt V1 and V2 variable decorators. Application error!`;
        stateMgmtConsole.applicationError(error);
        throw new Error(error);
      }
    }
    stateMgmtConsole.debug(`${this.debugInfo__()}: uses stateMgmt version ${this.isViewV2 === true ? 3 : 2}`);
  }

  public get localStorage_(): LocalStorage {
    if (!this.localStoragebackStore_ && this.getParent()) {
      stateMgmtConsole.debug(`${this.debugInfo__()}: constructor: get localStorage_ : Using LocalStorage instance of the parent View.`);
      this.localStoragebackStore_ = this.getParent().localStorage_;
    }

    if (!this.localStoragebackStore_) {
      stateMgmtConsole.info(`${this.debugInfo__()}: constructor: is accessing LocalStorage without being provided an instance. Creating a default instance.`);
      this.localStoragebackStore_ = new LocalStorage({ /* empty */ });
    }
    return this.localStoragebackStore_;
  }

  public set localStorage_(instance: LocalStorage) {
    if (!instance) {
      // setting to undefined not allowed
      return;
    }
    if (this.localStoragebackStore_) {
      stateMgmtConsole.applicationError(`${this.debugInfo__()}: constructor: is setting LocalStorage instance twice. Application error.`);
    }
    this.localStoragebackStore_ = instance;
  }

  // FIXME
  // indicate if this is  V1 or a V2 component
  // V1 by default, changed to V2 by the first V2 decorated variable
  // when splitting ViewPU and ViewV2
  // use instanceOf. Until then, this is a workaround.
  // @Local, @Param, @Trace, etc V2 decorator functions modify isViewV2 to return true
  // (decorator can modify functions in prototype)
  // FIXME
  protected get isViewV2(): boolean {
    return false;
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
  constructor(parent: IView, localStorage: LocalStorage, elmtId: number = UINodeRegisterProxy.notRecordingDependencies, extraInfo: ExtraInfo = undefined) {
    super(parent, elmtId, extraInfo);
    // if set use the elmtId also as the ViewPU object's subscribable id.
    // these matching is requirement for updateChildViewById(elmtId) being able to
    // find the child ViewPU object by given elmtId
    //this.id_ = elmtId == UINodeRegisterProxy.notRecordingDependencies ? SubscriberManager.MakeId() : elmtId;

    this.localStoragebackStore_ = undefined;

    stateMgmtConsole.debug(`ViewPU constructor: Creating @Component '${this.constructor.name}' from parent '${parent?.constructor.name}'`);

    ViewBuildNodeBase.arkThemeScopeManager?.onViewPUCreate(this)

    // Disable optimization when V1 is involved.
    ObserveV2.getObserve().isParentChildOptimizable_ = false;

    if (localStorage) {
      this.localStorage_ = localStorage;
      stateMgmtConsole.debug(`${this.debugInfo__()}: constructor: Using LocalStorage instance provided via @Entry or view instance creation.`);
    } else if (parent instanceof ViewBuildNodeBase) {
      this.localStorage_ = parent.getShareLocalStorage();
    }

    SubscriberManager.Add(this);
    stateMgmtConsole.debug(`${this.debugInfo__()}: constructor: done`);
  }

  // inform the subscribed property
  // that the View and thereby all properties
  // are about to be deleted
  abstract aboutToBeDeleted(): void;

  aboutToReuse(params: Object): void { }

  aboutToRecycle(): void { }

  // super class will call this function from
  // its aboutToBeDeleted implementation
  protected aboutToBeDeletedInternal(): void {
    stateMgmtConsole.debug(`${this.debugInfo__()}: aboutToBeDeletedInternal`);
    // if this isDeleting_ is true already, it may be set delete status recursively by its parent, so it is not necessary
    // to set and recursively set its children any more
    if (!this.isDeleting_) {
      this.isDeleting_ = true;
      this.setDeleteStatusRecursively();
    }
    // tell UINodeRegisterProxy that all elmtIds under
    // this ViewPU should be treated as already unregistered

    // un-register all repeat sub-components
    this.elmtId2Repeat_.forEach(<I>(repeat: __Repeat<I>) => {
      repeat.aboutToBeDeleted();
    });

    stateMgmtConsole.debug(`${this.constructor.name}: aboutToBeDeletedInternal `);

    // purge the elmtIds owned by this viewPU from the updateFuncByElmtId and also the state variable dependent elmtIds
    this.updateFuncByElmtId.forEach((_updateFun: UpdateFuncRecord, elmtId: number) => {
      this.purgeDeleteElmtId(elmtId);
      if (ConfigureStateMgmt.instance.needsV2Observe()) {
        delete ObserveV2.getObserve().id2cmp_[elmtId];
      }
    });

    if (ConfigureStateMgmt.instance.needsV2Observe()) {
      delete ObserveV2.getObserve().id2cmp_[this.id_];
    }

    if (this.hasRecycleManager()) {
      this.getRecycleManager().purgeAllCachedRecycleNode();
    }

    // un-registration of ElementIDs
    stateMgmtConsole.debug(`${this.debugInfo__()}: onUnRegElementID`);

    // it will unregister removed elmtIds from all ViewPu, equals purgeDeletedElmtIdsRecursively
    this.purgeDeletedElmtIds();

    // un-registers its own id once all its children are unregistered
    UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs([this.id__()]);

    stateMgmtConsole.debug(`${this.debugInfo__()}: onUnRegElementID  - DONE`);

    // in case this ViewPU is currently frozen
    PUV2ViewBase.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);

    this.updateFuncByElmtId.clear();
    this.watchedProps.clear();
    this.providedVars_.clear();
    if (this.ownObservedPropertiesStore__) {
      this.ownObservedPropertiesStore__.clear();
    }
    if (this.getParent()) {
      this.getParent().removeChild(this);
    }
    ViewBuildNodeBase.arkThemeScopeManager?.onViewPUDelete(this);
    this.localStoragebackStore_ = undefined;
    PUV2ViewBase.prebuildFuncQueues.delete(this.id__());
    PUV2ViewBase.propertyChangedFuncQueues.delete(this.id__());
    // if memory watch register the callback func, then report such information to memory watch
    // when custom node destroyed
    if (ArkUIObjectFinalizationRegisterProxy.callbackFunc_) {
      ArkUIObjectFinalizationRegisterProxy.call(new WeakRef(this),
        `${this.debugInfo__()} is in the process of destruction` );
    }
  }

  public purgeDeleteElmtId(rmElmtId: number): boolean {
    stateMgmtConsole.debug(`${this.debugInfo__()} purgeDeleteElmtId (PU) is purging the rmElmtId:${rmElmtId}`);
    const result = this.updateFuncByElmtId.delete(rmElmtId);
    if (result) {
      this.purgeVariableDependenciesOnElmtIdOwnFunc(rmElmtId);
      // it means rmElmtId has finished all the unregistration from the js side, ElementIdToOwningViewPU_  does not need to keep it
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
    }
    return result;
  }

  protected purgeVariableDependenciesOnElmtIdOwnFunc(elmtId: number): void {
    this.ownObservedPropertiesStore_.forEach((stateVar: ObservedPropertyAbstractPU<any>) => {
      stateVar.purgeDependencyOnElmtId(elmtId);
    });
  }
  public debugInfoStateVars(): string {
    let result: string = `|--${this.constructor.name}[${this.id__()}]`;
    Object.getOwnPropertyNames(this)
      .filter((varName: string) => varName.startsWith('__') && !varName.startsWith(ObserveV2.OB_PREFIX))
      .forEach((varName) => {
        const prop: any = Reflect.get(this, varName);
        if (prop && typeof prop === 'object' && 'debugInfoDecorator' in prop) {
          const observedProp = prop as ObservedPropertyAbstractPU<any>;
          result += `\n  ${observedProp.debugInfoDecorator()} '${observedProp.info()}'[${observedProp.id__()}]`;
          result += `\n  ${observedProp.debugInfoSubscribers()}`;
          result += `\n  ${observedProp.debugInfoSyncPeers()}`;
          result += `\n  ${observedProp.debugInfoDependentElmtIds()}`;
          result += `\n  ${observedProp.debugInfoDependentComponents()}`;
        }
      });
    return result;
  }

   /**
   * Indicate if this @Component is allowed to freeze by calling with freezeState=true
   * Called with value of the @Component decorator 'freezeWhenInactive' parameter
   * or depending how UI compiler works also with 'undefined'
   * @param freezeState only value 'true' will be used, otherwise inherits from parent
   * if not parent, set to false.
   */
   protected initAllowComponentFreeze(freezeState: boolean | undefined): void {
    // set to true if freeze parameter set for this @Component to true
    // otherwise inherit from parent @Component (if it exists).
    this.isCompFreezeAllowed_ = freezeState || this.isCompFreezeAllowed_;
    stateMgmtConsole.debug(`${this.debugInfo__()}: @Component freezeWhenInactive state is set to ${this.isCompFreezeAllowed()}`);
  }

  /**
 * ArkUI engine will call this function when the corresponding CustomNode's active status change.
 * ArkUI engine will not recurse children nodes to inform the stateMgmt for the performance reason.
 * So the stateMgmt needs to recurse the children although the isCompFreezeAllowed is false because the children nodes
 * may enable the freezeWhenInActive.
 * @param active true for active, false for inactive
 */
  public setActiveInternal(active: boolean, isReuse = false): void {
    stateMgmtProfiler.begin('ViewPU.setActive');
    if (this.isCompFreezeAllowed()) {
      this.setActiveCount(active);
      if (this.isViewActive()) {
        this.onActiveInternal();
      } else {
        this.onInactiveInternal();
      }
    }
    // Propagate state to all child View
    this.propagateToChildren(this.childrenWeakrefMap_, active, isReuse);
    // Propagate state to all child BuilderNode
    this.propagateToChildren(this.builderNodeWeakrefMap_, active, isReuse);
    stateMgmtProfiler.end();
  }

  private onActiveInternal(): void {
    if (!this.isViewActive()) {
      return;
    }

    stateMgmtConsole.debug(`${this.debugInfo__()}: onActiveInternal`);
    this.performDelayedUpdate();
    // Remove the active component from the Map for Dfx
    ViewPU.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
  }


  private onInactiveInternal(): void {
    if (this.isViewActive()) {
      return;
    }

    stateMgmtConsole.debug(`${this.debugInfo__()}: onInactiveInternal`);
    for (const stateLinkProp of this.ownObservedPropertiesStore_) {
      stateLinkProp.enableDelayedNotification();
    }
    // Add the inactive Components to Map for Dfx listing
    ViewPU.inactiveComponents_.add(`${this.constructor.name}[${this.id__()}]`);
  }


  // abstract functions to be implemented by application defined class / transpiled code
  protected abstract purgeVariableDependenciesOnElmtId(removedElmtId: number);
  protected abstract initialRender(): void;
  protected abstract rerender(): void;

  public abstract updateRecycleElmtId(oldElmtId: number, newElmtId: number): void;
  public abstract updateStateVars(params: Object);

  public initialRenderView(): void {
    stateMgmtProfiler.begin('ViewPU.initialRenderView');
    this.onWillApplyThemeInternally();
    this.obtainOwnObservedProperties();
    this.isRenderInProgress = true;
    this.initialRender();
    this.isRenderInProgress = false;
    this.isInitialRenderDone = true;
    stateMgmtProfiler.end();
  }

  public UpdateElement(elmtId: number, dirtElmtIdsFromRootNode: Array<number> = new Array<number>()): void {
    stateMgmtProfiler.begin('ViewPU.UpdateElement');
    if (elmtId === this.id__()) {
      // do not attempt to update itself.
      // a @Prop can add a dependency of the ViewPU onto itself. Ignore it.
      stateMgmtProfiler.end();
      return;
    }

    // do not process an Element that has been marked to be deleted
    const entry: UpdateFuncRecord | undefined = this.updateFuncByElmtId.get(elmtId);
    if (!entry) {
      stateMgmtProfiler.end();
      return;
    }
    let updateFunc: UpdateFunc;
    // if the element is pending, its updateFunc will not be executed during this function call, instead mark its UpdateFuncRecord as changed
    // when the pending element is retaken and its UpdateFuncRecord is marked changed, then it will be inserted into dirtRetakenElementIds_
    if (entry.isPending()) {
      entry.setIsChanged(true);
    } else {
      updateFunc = entry.getUpdateFunc();
    }

    if (typeof updateFunc !== 'function') {
      stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement: update function of elmtId ${elmtId} not found, internal error!`);
    } else {
      stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement: re-render of ${entry.getComponentName()} elmtId ${elmtId} start ...`);
      this.isRenderInProgress = true;
      stateMgmtProfiler.begin('ViewPU.updateFunc');
      try {
        updateFunc(elmtId, /* isFirstRender */ false);
      } catch (error) {
        for (const dirtEId of dirtElmtIdsFromRootNode) {
          stateMgmtConsole.applicationError(`${this.debugInfo__()}: dirty element ${this.updateFuncByElmtId.get(dirtEId)?.getComponentName()} with id ${dirtEId}, isPending: ${this.updateFuncByElmtId.get(dirtEId)?.isPending()}`);
        }
        stateMgmtConsole.applicationError(`${this.debugInfo__()}: UpdateElement: re-render of ${entry.getComponentName()} elmtId ${elmtId} has error in update func: ${error.message}`);
        throw error;
      }
      stateMgmtProfiler.end();
      stateMgmtProfiler.begin('ViewPU.finishUpdateFunc (native)');
      this.finishUpdateFunc(elmtId);
      stateMgmtProfiler.end();
      this.isRenderInProgress = false;
      stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement: re-render of ${entry.getComponentName()} elmtId ${elmtId} - DONE`);
    }
    stateMgmtProfiler.end();
  }

  public delayCompleteRerender(deep: boolean = false): void {
    this.delayRecycleNodeRerender = true;
    this.delayRecycleNodeRerenderDeep = deep;
  }

  public flushDelayCompleteRerender(): void {
    this.forceCompleteRerender(this.delayRecycleNodeRerenderDeep);
    this.delayRecycleNodeRerender = false;
  }

  /**
   * force a complete rerender / update on specific node by executing update function.
   *
   * @param elmtId which node needs to update.
   *
   * framework internal functions, apps must not call
   */
  public forceRerenderNode(elmtId: number): void {
    stateMgmtProfiler.begin('ViewPU.forceRerenderNode');
    // see which elmtIds are managed by this View
    // and clean up all book keeping for them
    this.purgeDeletedElmtIds();
    this.UpdateElement(elmtId);

    // remove elemtId from dirtDescendantElementIds.
    this.dirtDescendantElementIds_.delete(elmtId);
    stateMgmtProfiler.end();
  }

  // collect elements need to update synchronously and its owning view
  public collectElementsNeedToUpdateSynchronously(varName: PropertyInfo, dependentElmtIds: Set<number>): void {
    stateMgmtConsole.debug(`collectElementsNeedToUpdateSynchronously ${this.debugInfo__()} change ${varName} dependent elements ${dependentElmtIds}`);
    if (dependentElmtIds.size && !this.isFirstRender()) {
      for (const elmtId of dependentElmtIds) {
        if (this.hasRecycleManager()) {
          this.dirtyElementIdsNeedsUpdateSynchronously_.add(this.recycleManager_.proxyNodeId(elmtId));
        } else {
          this.dirtyElementIdsNeedsUpdateSynchronously_.add(elmtId);
        }
      }
      SyncedViewRegistry.addSyncedUpdateDirtyNodes(this);
    }
    const cb = this.watchedProps.get(varName);
    if (cb && typeof cb === 'function') {
      stateMgmtConsole.debug(`${this.debugInfo__()} state var ${varName} calling @Watch function`);
      cb.call(this, varName);
    }
  }

  // implements IMultiPropertiesChangeSubscriber
  viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void {
    stateMgmtProfiler.begin('ViewPU.viewPropertyHasChanged');
    aceDebugTrace.begin('ViewPU.viewPropertyHasChanged', this.constructor.name, varName, dependentElmtIds.size, this.id__(), this.dirtDescendantElementIds_.size, this.runReuse_);
    if (this.isRenderInProgress) {
      stateMgmtConsole.applicationError(`${this.debugInfo__()}: State variable '${varName}' has changed during render! It's illegal to change @Component state while build (initial render or re-render) is on-going. Application error!`);
    } else if (this.isPrebuilding_) {
      const propertyChangedFunc: PrebuildFunc = () => {
        this.viewPropertyHasChanged(varName, dependentElmtIds);
      };
      if (!PUV2ViewBase.propertyChangedFuncQueues.has(this.id__())) {
        PUV2ViewBase.propertyChangedFuncQueues.set(this.id__(), new Array<PrebuildFunc>());
      }
      PUV2ViewBase.propertyChangedFuncQueues.get(this.id__())?.push(propertyChangedFunc);
      return;
    }

    this.syncInstanceId();

    if (dependentElmtIds.size && !this.isFirstRender()) {
      if (!this.dirtDescendantElementIds_.size && !this.runReuse_) {
        // mark ComposedElement dirty when first elmtIds are added
        // do not need to do this every time
        this.markNeedUpdate();
      }
      stateMgmtConsole.debug(`${this.debugInfo__()}: viewPropertyHasChanged property: elmtIds that need re-render due to state variable change: ${this.debugInfoElmtIds(Array.from(dependentElmtIds))} .`);
      for (const elmtId of dependentElmtIds) {
        if (this.hasRecycleManager()) {
          this.dirtDescendantElementIds_.add(this.recycleManager_.proxyNodeId(elmtId));
        } else {
          this.dirtDescendantElementIds_.add(elmtId);
        }
      }
      stateMgmtConsole.debug(`   ... updated full list of elmtIds that need re-render [${this.debugInfoElmtIds(Array.from(this.dirtDescendantElementIds_))}].`);
    } else {
      stateMgmtConsole.debug(`${this.debugInfo__()}: viewPropertyHasChanged: state variable change adds no elmtIds for re-render`);
      stateMgmtConsole.debug(`   ... unchanged full list of elmtIds that need re-render [${this.debugInfoElmtIds(Array.from(this.dirtDescendantElementIds_))}].`);
    }

    let cb = this.watchedProps.get(varName);
    if (cb && typeof cb === 'function') {
      stateMgmtConsole.debug(`   ... calling @Watch function`);
      cb.call(this, varName);
    }

    this.restoreInstanceId();
    aceDebugTrace.end();
    stateMgmtProfiler.end();
  }


  /**
 *  inform that UINode with given elmtId needs rerender
 *  does NOT exec @Watch function.
 *  only used on V2 code path from ObserveV2.fireChange.
 *
 * FIXME will still use in the future?
 */
  public uiNodeNeedUpdateV2(elmtId: number): void {
    if (this.isPrebuilding_) {
      const propertyChangedFunc: PrebuildFunc = () => {
        this.uiNodeNeedUpdateV2(elmtId);
      };
      if (!PUV2ViewBase.propertyChangedFuncQueues.has(this.id__())) {
        PUV2ViewBase.propertyChangedFuncQueues.set(this.id__(), new Array<PrebuildFunc>());
      }
      PUV2ViewBase.propertyChangedFuncQueues.get(this.id__())?.push(propertyChangedFunc);
      return;
    }
    if (this.isFirstRender()) {
      return;
    }

    stateMgmtProfiler.begin(`ViewPU.uiNodeNeedUpdate ${this.debugInfoElmtId(elmtId)}`);

    if (!this.dirtDescendantElementIds_.size) { //  && !this runReuse_) {
      // mark ComposedElement dirty when first elmtIds are added
      // do not need to do this every time
      this.syncInstanceId();
      this.markNeedUpdate();
      this.restoreInstanceId();
    }
    if (this.hasRecycleManager()) {
      this.dirtDescendantElementIds_.add(this.recycleManager_.proxyNodeId(elmtId));
    } else {
      this.dirtDescendantElementIds_.add(elmtId);
    }
    stateMgmtConsole.debug(`${this.debugInfo__()}: uiNodeNeedUpdate: updated full list of elmtIds that need re-render [${this.debugInfoElmtIds(Array.from(this.dirtDescendantElementIds_))}].`);

    stateMgmtProfiler.end();
  }

  private performDelayedUpdate(): void {
    if (!this.ownObservedPropertiesStore_.size && !this.elmtIdsDelayedUpdate.size) {
      return;
    }
    stateMgmtProfiler.begin('ViewPU.performDelayedUpdate');
    aceDebugTrace.begin('ViewPU.performDelayedUpdate', this.constructor.name);
    stateMgmtConsole.debug(`${this.debugInfo__()}: performDelayedUpdate start ...`);
    this.syncInstanceId();

    for (const stateLinkPropVar of this.ownObservedPropertiesStore_) {
      const changedElmtIds = stateLinkPropVar.moveElmtIdsForDelayedUpdate();
      if (changedElmtIds) {
        const varName = stateLinkPropVar.info();
        if (changedElmtIds.size && !this.isFirstRender()) {
          for (const elmtId of changedElmtIds) {
            this.dirtDescendantElementIds_.add(elmtId);
          }
        }

        stateMgmtConsole.debug(`${this.debugInfo__()}: performDelayedUpdate: all elmtIds that need re-render [${Array.from(this.dirtDescendantElementIds_).toString()}].`);

        const cb = this.watchedProps.get(varName);
        if (cb) {
          stateMgmtConsole.debug(`   ... calling @Watch function`);
          cb.call(this, varName);
        }
      }
    } // for all ownStateLinkProps_

    for (let elementId of this.elmtIdsDelayedUpdate) {
      this.dirtDescendantElementIds_.add(elementId);
    }
    this.elmtIdsDelayedUpdate.clear();

    this.restoreInstanceId();

    if (this.dirtDescendantElementIds_.size) {
      this.markNeedUpdate();
    }
    aceDebugTrace.end();
    stateMgmtProfiler.end();
  }

  /**
   * Function to be called from the constructor of the sub component
   * to register a @Watch variable
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
  protected addProvidedVar<T>(providedPropName: string, store: ObservedPropertyAbstractPU<T>, allowOverride: boolean = false) {
    if (!allowOverride && this.findProvidePU__(providedPropName)) {
      throw new ReferenceError(`${this.constructor.name}: duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Views already. @Provide override not allowed.`);
    }
    store.setDecoratorInfo('@Provide');
    this.providedVars_.set(providedPropName, store);
  }

  /*
    findProvidePU__ finds @Provided property recursively by traversing ViewPU's towards that of the UI tree root @Component:
    if 'this' ViewPU has a @Provide('providedPropName') return it, otherwise ask from its parent ViewPU.
  */
  public findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined {
    return this.providedVars_.get(providedPropName) ||
    (this.parent_ && this.parent_.findProvidePU__(providedPropName)) ||
    (this.__parentViewBuildNode__ && this.__parentViewBuildNode__.findProvidePU__(providedPropName));
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
    consumeVarName: string, defaultValue?: any): ObservedPropertyAbstractPU<T> {
    let providedVarStore: ObservedPropertyAbstractPU<any> = this.findProvidePU__(providedPropName);
    // '3' means that developer has initialized the @Consume decorated variable
    if (!providedVarStore) {
      if (arguments.length === 3) {
        providedVarStore = new ObservedPropertyPU(defaultValue, this, consumeVarName);
        providedVarStore.__setIsFake_ObservedPropertyAbstract_Internal(true);
      } else {
        throw new ReferenceError(`${this.debugInfo__()} missing @Provide property with name ${providedPropName} or default value.
          Fail to resolve @Consume(${providedPropName}).`);
      }
    }

    const factory = <T>(source: ObservedPropertyAbstract<T>) => {
      const result: ObservedPropertyAbstractPU<T> = new SynchedPropertyTwoWayPU<T>(source, this, consumeVarName);
      result.setDecoratorInfo('@Consume');
      stateMgmtConsole.debug(`The @Consume is instance of ${result.constructor.name}`);
      return result;
    };
    let consumeVal = providedVarStore.createSync(factory) as SynchedPropertyTwoWayPU<T>;
    if (providedVarStore.__isFake_ObservedPropertyAbstract_Internal()) {
      this.defaultConsume_.set(providedPropName, consumeVal);
    }
    return consumeVal;
  }

  public reconnectToConsume(): void {
    this.defaultConsume_.forEach((value: SynchedPropertyObjectTwoWayPU<any>, providedPropName: string) => {
      let providedVarStore: ObservedPropertyAbstractPU<any> = this.findProvidePU__(providedPropName);
      if (providedVarStore) {
        stateMgmtConsole.debug(`${value.debugInfo()} connected to the provide ${providedVarStore.debugInfo()}`);
        value.resetSource(providedVarStore);
        // store the consume reconnect to provide
        this.reconnectConsume_.set(providedPropName, value);
        value.getDependencies().forEach((id: number) => {
          this.UpdateElement(id);
        })
      }
    })
  }

  public disconnectedConsume(): void {
    for (const [key, value] of this.reconnectConsume_) {
      // try to findProvide again
      // need to set Parent undefine first
      const provide = this.findProvidePU__(key);
      // if provide is undefined, the provide and consume connection is broken
      // reset consume to default value.
      if (!provide) {
        value.resetFakeSource();
        value.getDependencies().forEach((id: number) => {
          this.UpdateElement(id);
        })
        this.reconnectConsume_.delete(key);
      }
    }
  }

  /**
   * given the elmtId of a child or child of child within this custom component
   * remember this component needs a partial update
   * @param elmtId
   */
  public markElemenDirtyById(elmtId: number): void {
    // TODO ace-ets2bundle, framework, compiled apps need to update together
    // this function will be removed after a short transition period
    stateMgmtConsole.applicationError(`${this.debugInfo__()}: markElemenDirtyById no longer supported.
        Please update your ace-ets2bundle and recompile your application. Application error!`);
  }

  /**
   * For each recorded dirty Element in this custom component
   * run its update function
   *
   */
  public updateDirtyElements(): void {
    stateMgmtProfiler.begin('ViewPU.updateDirtyElements');
    do {
      stateMgmtConsole.debug(`${this.debugInfo__()}: updateDirtyElements (re-render): sorted dirty elmtIds: ${Array.from(this.dirtDescendantElementIds_).sort(ViewPU.compareNumber)}, starting ....`);

      // see which elmtIds are managed by this View
      // and clean up all book keeping for them
      this.purgeDeletedElmtIds();

      // process all elmtIds marked as needing update in ascending order.
      // ascending order ensures parent nodes will be updated before their children
      // prior cleanup ensure no already deleted Elements have their update func executed
      const dirtElmtIdsFromRootNode = Array.from(this.dirtDescendantElementIds_).sort(ViewPU.compareNumber);
      // if state changed during exec update lambda inside UpdateElement, then the dirty elmtIds will be added
      // to newly created this.dirtDescendantElementIds_ Set
      dirtElmtIdsFromRootNode.forEach(elmtId => {
        if (this.hasRecycleManager()) {
          this.UpdateElement(this.recycleManager_.proxyNodeId(elmtId), dirtElmtIdsFromRootNode);
        } else {
          this.UpdateElement(elmtId, dirtElmtIdsFromRootNode);
        }
        this.dirtDescendantElementIds_.delete(elmtId);
      });

      if (this.dirtDescendantElementIds_.size) {
        stateMgmtConsole.applicationError(`${this.debugInfo__()}: New UINode objects added to update queue while re-render! - Likely caused by @Component state change during build phase, not allowed. Application error!`);
      }

      for (const dirtRetakenElementId of this.dirtRetakenElementIds_) {
        this.dirtDescendantElementIds_.add(dirtRetakenElementId);
      }
      this.dirtRetakenElementIds_.clear();

    } while (this.dirtDescendantElementIds_.size);
    stateMgmtConsole.debug(`${this.debugInfo__()}: updateDirtyElements (re-render) - DONE, dump of ViewPU in next lines`);
    stateMgmtProfiler.end();
  }

  // executed on first render only
  // kept for backward compatibility with old ace-ets2bundle
  public observeComponentCreation(compilerAssignedUpdateFunc: UpdateFunc): void {
    if (PUV2ViewBase.isNeedBuildPrebuildCmd() && PUV2ViewBase.prebuildFuncQueues.has(PUV2ViewBase.prebuildingElmtId_)) {
      const prebuildFunc: PrebuildFunc = () => {
        this.observeComponentCreation(compilerAssignedUpdateFunc);
      };
      PUV2ViewBase.prebuildFuncQueues.get(PUV2ViewBase.prebuildingElmtId_)?.push(prebuildFunc);
      ViewStackProcessor.PushPrebuildCompCmd();
      return;
    }
    if (this.isDeleting_) {
      stateMgmtConsole.error(`View ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation `);
      return;
    }
    const updateFunc = (elmtId: number, isFirstRender: boolean): void => {
      stateMgmtConsole.debug(`${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`} start ....`);
      this.currentlyRenderedElmtIdStack_.push(elmtId);
      compilerAssignedUpdateFunc(elmtId, isFirstRender);
      this.currentlyRenderedElmtIdStack_.pop();
      stateMgmtConsole.debug(`${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`} - DONE ....`);
    }

    const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    // in observeComponentCreation function we do not get info about the component name, in
    // observeComponentCreation2 we do.
    this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc });
    // add element id -> owning ViewPU
    UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
    try {
      updateFunc(elmtId, /* is first render */ true);
    } catch (error) {
      // avoid the incompatible change that move set function before updateFunc.
      this.updateFuncByElmtId.delete(elmtId);
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
      stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in update func: ${(error as Error).message}`);
      throw error;
    }
  }

  public observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: UIClassObject): void {
    if (PUV2ViewBase.isNeedBuildPrebuildCmd() && PUV2ViewBase.prebuildFuncQueues.has(PUV2ViewBase.prebuildingElmtId_)) {
      const prebuildFunc: PrebuildFunc = () => {
        this.observeComponentCreation2(compilerAssignedUpdateFunc, classObject);
      };
      PUV2ViewBase.prebuildFuncQueues.get(PUV2ViewBase.prebuildingElmtId_)?.push(prebuildFunc);
      ViewStackProcessor.PushPrebuildCompCmd();
      return;
    }
    if (this.isDeleting_) {
      stateMgmtConsole.error(`View ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation2 `);
      return;
    }
    const _componentName: string = (classObject && ('name' in classObject)) ? Reflect.get(classObject, 'name') as string : 'unspecified UINode';
    if (_componentName === '__Recycle__') {
      return;
    }
    const _popFunc: () => void = (classObject && 'pop' in classObject) ? classObject.pop! : (): void => { };
    const updateFunc = (elmtId: number, isFirstRender: boolean): void => {
      this.syncInstanceId();
      stateMgmtConsole.debug(`${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`} ${_componentName}[${elmtId}] ${!this.isViewV2 ? '(enable PU state observe) ' : ''} ${ConfigureStateMgmt.instance.needsV2Observe() ? '(enabled V2 state observe) ' : ''} - start ....`);

      ViewBuildNodeBase.arkThemeScopeManager?.onComponentCreateEnter(_componentName, elmtId, isFirstRender, this)

      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);

      if (!this.isViewV2) {
        // Enable PU state tracking only in PU @Components
        this.currentlyRenderedElmtIdStack_.push(elmtId);
        stateMgmtDFX.inRenderingElementId.push(elmtId);
      }

      // if V2 @Observed/@Track used anywhere in the app (there is no more fine grained criteria),
      // enable V2 object deep observation
      // FIXME: A @Component should only use PU or V2 state, but ReactNative dynamic viewer uses both.
      if (this.isViewV2 || ConfigureStateMgmt.instance.needsV2Observe()) {
        stateMgmtConsole.debug(`${this.debugInfo__()}: V2 dependency recording is enabled (uses ObserveV2.getObserve().startRecordDependencies, enables addRef)`)
        // FIXME: like in V2 setting bindId_ in ObserveV2 does not work with 'stacked'
        // update + initial render calls, like in if and ForEach case, convert to stack as well
        ObserveV2.getObserve().startRecordDependencies(this, elmtId);
      }

      compilerAssignedUpdateFunc(elmtId, isFirstRender);
      if (!isFirstRender) {
        _popFunc();
      }

      let node = this.getNodeById(elmtId);
      if (node !== undefined) {
        (node as ArkComponent).cleanStageValue();
      }

      if (this.isViewV2 || ConfigureStateMgmt.instance.needsV2Observe()) {
        ObserveV2.getObserve().stopRecordDependencies();
      }
      if (!this.isViewV2) {
        this.currentlyRenderedElmtIdStack_.pop();
        stateMgmtDFX.inRenderingElementId.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();

      ViewBuildNodeBase.arkThemeScopeManager?.onComponentCreateExit(elmtId)

      stateMgmtConsole.debug(`${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`}  ${_componentName}[${elmtId}] - DONE ....`);
      this.restoreInstanceId();
    };

    const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    // needs to move set before updateFunc.
    // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
    this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, classObject: classObject });
    // add element id -> owning ViewPU
    UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
    try {
      updateFunc(elmtId, /* is first render */ true);
    } catch (error) {
      // avoid the incompatible change that move set function before updateFunc.
      this.updateFuncByElmtId.delete(elmtId);
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
      stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in update func: ${(error as Error).message}`);
      throw error;
    }
    stateMgmtConsole.debug(`${this.debugInfo__()} is initial rendering elmtId ${elmtId}, tag: ${_componentName}, and updateFuncByElmtId size :${this.updateFuncByElmtId.size}`);
  }


  getOrCreateRecycleManager(): RecycleManager {
    if (!this.recycleManager_) {
      this.recycleManager_ = new RecycleManager;
    }
    return this.recycleManager_;
  }

  getRecycleManager(): RecycleManager {
    return this.recycleManager_;
  }

  hasRecycleManager(): boolean {
    return !(this.recycleManager_ === undefined);
  }

  initRecycleManager(): void {
    if (this.recycleManager_) {
      stateMgmtConsole.error(`${this.debugInfo__()}: init recycleManager multiple times. Internal error.`);
      return;
    }
    this.recycleManager_ = new RecycleManager;
  }
  rebuildUpdateFunc(elmtId, compilerAssignedUpdateFunc): void {
    const updateFunc = (elmtId, isFirstRender): void => {
      this.currentlyRenderedElmtIdStack_.push(elmtId);
      compilerAssignedUpdateFunc(elmtId, isFirstRender);
      this.currentlyRenderedElmtIdStack_.pop();
    };
    if (this.updateFuncByElmtId.has(elmtId)) {
      this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc });
    }
  }

  /**
   * @function observeRecycleComponentCreation
   * @description custom node recycle creation
   * @param name custom node name
   * @param recycleUpdateFunc custom node recycle update which can be converted to a normal update function
   * @return void
   */
  public observeRecycleComponentCreation(name: string, recycleUpdateFunc: RecycleUpdateFunc): void {
    if (PUV2ViewBase.isNeedBuildPrebuildCmd() && PUV2ViewBase.prebuildFuncQueues.has(PUV2ViewBase.prebuildingElmtId_)) {
      const prebuildFunc: PrebuildFunc = () => {
        this.observeRecycleComponentCreation(name, recycleUpdateFunc);
      };
      PUV2ViewBase.prebuildFuncQueues.get(PUV2ViewBase.prebuildingElmtId_)?.push(prebuildFunc);
      ViewStackProcessor.PushPrebuildCompCmd();
      return;
    }
    // convert recycle update func to update func
    const compilerAssignedUpdateFunc: UpdateFunc = (element, isFirstRender) => {
      recycleUpdateFunc(element, isFirstRender, undefined);
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
    this.recycleManager_.updateNodeId(oldElmtId, newElmtId);
    node.hasBeenRecycled_ = false;
    this.rebuildUpdateFunc(oldElmtId, compilerAssignedUpdateFunc);
    recycleUpdateFunc(oldElmtId, /* is first render */ true, node);
  }

  // param is used by BuilderNode
  aboutToReuseInternal(param?: Object) {
    this.runReuse_ = true;
    stateMgmtConsole.debug(`ViewPU ${this.debugInfo__()} aboutToReuseInternal`);
    stateMgmtTrace.scopedTrace(() => {
      if (this.paramsGenerator_ && typeof this.paramsGenerator_ === 'function') {
        const params = param ? param : this.paramsGenerator_();
        this.updateStateVars(params);
        this.aboutToReuse(params);
      }
    }, 'aboutToReuse', this.constructor.name);

    for (const stateLinkPropVar of this.ownObservedPropertiesStore_) {
      const changedElmtIds = stateLinkPropVar.moveElmtIdsForDelayedUpdate(true);
      if (changedElmtIds) {
        if (changedElmtIds.size && !this.isFirstRender()) {
          for (const elmtId of changedElmtIds) {
            this.dirtDescendantElementIds_.add(elmtId);
          }
        }
      }
    }
    if (!this.delayRecycleNodeRerender) {
      this.updateDirtyElements();
    } else {
      this.flushDelayCompleteRerender();
    }
    this.traverseChildDoRecycleOrReuse(PUV2ViewBase.doReuse);
    this.runReuse_ = false;
  }

  stopRecursiveRecycle() {
    this.preventRecursiveRecycle_ = true;
  }

  aboutToRecycleInternal() {
    this.runReuse_ = true;
    stateMgmtConsole.debug(`ViewPU ${this.debugInfo__()} aboutToRecycleInternal`);
    stateMgmtTrace.scopedTrace(() => {
      this.aboutToRecycle();
    }, 'aboutToRecycle', this.constructor.name);
    if (this.preventRecursiveRecycle_) {
      this.preventRecursiveRecycle_ = false;
      return;
    }
    this.traverseChildDoRecycleOrReuse(PUV2ViewBase.doRecycle);
    this.runReuse_ = false;
  }

  // add current JS object to it's parent recycle manager
  public recycleSelf(name: string): void {

    if (this.getParent() && this.getParent() instanceof ViewPU && !(this.getParent() as ViewPU).isDeleting_) {
      const parentPU : ViewPU = this.getParent() as ViewPU;
      parentPU.getOrCreateRecycleManager().pushRecycleNode(name, this);
      this.hasBeenRecycled_ = true;
    } else {
      this.resetRecycleCustomNode();
    }
  }

  public isRecycled() : boolean {
    return this.hasBeenRecycled_;
  }

  public UpdateLazyForEachElements(elmtIds: Array<number>): void {
    if (!Array.isArray(elmtIds)) {
      return;
    }
    Array.from(elmtIds).sort(ViewPU.compareNumber).forEach((elmtId: number) => {
      const entry: UpdateFuncRecord | undefined = this.updateFuncByElmtId.get(elmtId);
      const updateFunc: UpdateFunc = entry ? entry.getUpdateFunc() : undefined;
      if (typeof updateFunc !== 'function') {
        stateMgmtConsole.debug(`${this.debugInfo__()}: update function of elmtId ${elmtId} not found, internal error!`);
      } else {
        this.isRenderInProgress = true;
        updateFunc(elmtId, false);
        this.finishUpdateFunc(elmtId);
        this.isRenderInProgress = false;
      }
    })
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
        : new SynchedPropertyTwoWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    appStorageLink?.setDecoratorInfo('@StorageLink');
    return appStorageLink;
  }

  public createStorageProp<T>(storagePropName: string, defaultValue: T, viewVariableName: string): ObservedPropertyAbstractPU<T> {
    const appStorageProp = AppStorage.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : new SynchedPropertyOneWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    appStorageProp?.setDecoratorInfo('@StorageProp');
    return appStorageProp;
  }

  public createLocalStorageLink<T>(storagePropName: string, defaultValue: T,
    viewVariableName: string): ObservedPropertyAbstractPU<T> {
    const localStorageLink = this.localStorage_.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : new SynchedPropertyTwoWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    localStorageLink?.setDecoratorInfo('@LocalStorageLink');
    return localStorageLink;
  }

  public createLocalStorageProp<T>(storagePropName: string, defaultValue: T,
    viewVariableName: string): ObservedPropertyAbstractPU<T> {
    const localStorageProp = this.localStorage_.__createSync<T>(storagePropName, defaultValue,
      <T>(source: ObservedPropertyAbstract<T>) => (source === undefined)
        ? undefined
        : new SynchedPropertyObjectOneWayPU<T>(source, this, viewVariableName)
    ) as ObservedPropertyAbstractPU<T>;
    localStorageProp?.setDecoratorInfo('@LocalStorageProp');
    return localStorageProp;
  }

  public debugInfoView(recursive: boolean = false): string {
    return this.debugInfoViewInternal(recursive);
  }

  private debugInfoViewInternal(recursive: boolean = false): string {
    let retVal: string = `@Component\n${this.constructor.name}[${this.id__()}]`;
    retVal += `\n\nView Hierarchy:\n${this.debugInfoViewHierarchy(recursive)}`;
    retVal += `\n\nState variables:\n${this.debugInfoStateVars()}`;
    retVal += `\n\nRegistered Element IDs:\n${this.debugInfoUpdateFuncByElmtId(recursive)}`;
    retVal += `\n\nDirty Registered Element IDs:\n${this.debugInfoDirtDescendantElementIds(recursive)}`;
    return retVal;
  }

  public debugInfoDirtDescendantElementIds(recursive: boolean = false): string {
    return this.debugInfoDirtDescendantElementIdsInternal(0, recursive, { total: 0 });
  }

  public debugInfoDirtDescendantElementIdsInternal(depth: number = 0, recursive: boolean = false, counter: ProfileRecursionCounter): string {
    let retVaL: string = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
    this.dirtDescendantElementIds_.forEach((value) => {
      retVaL += `${value}, `;
    });
    counter.total += this.dirtDescendantElementIds_.size;
    retVaL += `\n${'  '.repeat(depth + 1)}}[${this.dirtDescendantElementIds_.size}]`;
    if (recursive) {
      this.childrenWeakrefMap_.forEach((value, key, map) => {
        retVaL += value.deref()?.debugInfoDirtDescendantElementIdsInternal(depth + 1, recursive, counter);
      })
    }

    if (recursive && depth == 0) {
      retVaL += `\nTotal: ${counter.total}`;
    }
    return retVaL;
  }

  /**
   * on first render create a new Instance of Repeat
   * on re-render connect to existing instance
   * @param arr
   * @returns
   */
  public __mkRepeatAPI: <I>(arr: Array<I>) => RepeatAPI<I> = <I>(arr: Array<I>): RepeatAPI<I> => {
    // factory is for future extensions, currently always return the same
    const elmtId = this.getCurrentlyRenderedElmtId();
    let repeat = this.elmtId2Repeat_.get(elmtId) as __Repeat<I>;
    if (!repeat) {
        repeat = new __Repeat<I>(this, arr);
        this.elmtId2Repeat_.set(elmtId, repeat);
    } else {
        repeat.updateArr(arr);
    }

    return repeat;
  }

  public reuseOrCreateNewComponent(params: { componentClass: any, getParams: () => Object,
    getReuseId?: () => string, extraInfo?: ExtraInfo }): void {
      // ViewPU should not have a ReusableV2 Component, throw error!
      const error = `@Component cannot have a child @ReusableV2 component !`;
      stateMgmtConsole.applicationError(error);
      throw new Error(error);
  }
} // class ViewPU

