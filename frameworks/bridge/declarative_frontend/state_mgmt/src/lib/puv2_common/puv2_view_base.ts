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
*/

/**
 * 
 * This file includes only framework internal classes and functions 
 * non are part of SDK. Do not access from app.
 * 
 * PUV2ViewBase is the common base class of ViewPU and ViewV2
 * 
 */

/// <reference path="../../../../ark_theme/export/ark_theme_scope_manager.d.ts" />

type ExtraInfo = { page: string, line: number, col: number };
type ProfileRecursionCounter = { total: number };

// NativeView
// implemented in C++  for release
abstract class PUV2ViewBase extends NativeViewPartialUpdate {

  // List of inactive components used for Dfx
  protected static readonly inactiveComponents_: Set<string> = new Set<string>();
  protected get isReusable_(): boolean {
    // property getter function are in the prototype
    // @Reusable and @ReusableV2 decorators modify the function
    // in decorated class' prototype to return true
    return false;
  }

  // Array.sort() converts array items to string to compare them!
  static readonly compareNumber = (a: number, b: number): number => {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
  };

  // indicates the currently rendered or rendered UINode's elmtIds
  // or UINodeRegisterProxy.notRecordingDependencies if none is currently rendering
  // isRenderInProgress == true always when currentlyRenderedElmtIdStack_ length >= 0
  protected currentlyRenderedElmtIdStack_: Array<number> = new Array<number>();
  
  // Set of elmtIds that need re-render
  protected dirtDescendantElementIds_: Set<number> = new Set<number>();

  // Set of elmtIds retaken by IF that need re-render
  protected dirtRetakenElementIds_: Set<number> = new Set<number>();

  // Map elmtId -> Repeat instance in this ViewPU
  protected elmtId2Repeat_: Map<number, RepeatAPI<any>> = new Map<number, RepeatAPI<any>>();

  private id_: number;

  protected parent_: IView | undefined = undefined;
  protected childrenWeakrefMap_ = new Map<number, WeakRef<IView>>();

  // static flag for paused rendering
  // when paused, getCurrentlyRenderedElmtId() will return UINodeRegisterProxy.notRecordingDependencies
  public static renderingPaused: boolean = false;

  // greater than 0 means the node is active, otherwise node is inactive.
  // inActive means updates are delayed
  protected activeCount_: number = 1;

  // flag if {aboutToBeDeletedInternal} is called and the instance of ViewPU/V2 has not been GC.
  protected isDeleting_: boolean = false;

  protected isCompFreezeAllowed_: boolean = false;

  // registry of update functions
  // the key is the elementId of the Component/Element that's the result of this function
  protected updateFuncByElmtId = new UpdateFuncsByElmtId();

  protected extraInfo_: ExtraInfo = undefined;

  // used by view createdBy BuilderNode. Indicated weather need to block the recylce or reuse events called by parentView;
  public __isBlockRecycleOrReuse__: boolean = false;

  // Set of elements for delayed update
  private elmtIdsDelayedUpdate_: Set<number> = new Set();

  protected static arkThemeScopeManager: ArkThemeScopeManager | undefined = undefined

  static readonly doRecycle: boolean = true;
  static readonly doReuse: boolean = false;

  constructor(parent: IView, elmtId: number = UINodeRegisterProxy.notRecordingDependencies, extraInfo: ExtraInfo = undefined) {
    super();
    // if set use the elmtId also as the ViewPU/V2 object's subscribable id.
    // these matching is requirement for updateChildViewById(elmtId) being able to
    // find the child ViewPU/V2 object by given elmtId
    this.id_ = elmtId === UINodeRegisterProxy.notRecordingDependencies ? SubscriberManager.MakeId() : elmtId;

    stateMgmtConsole.debug(`PUV2ViewBase constructor: Creating @Component '${this.constructor.name}' from parent '${parent?.constructor.name}'`);

    if (extraInfo) {
      this.extraInfo_ = extraInfo;
    }

    if (parent) {
      // this View is not a top-level View
      this.setCardId(parent.getCardId());
      // Call below will set this parent_ to parent as well
      parent.addChild(this as unknown as IView); // FIXME
    }

    this.isCompFreezeAllowed_ = this.isCompFreezeAllowed_ || (this.parent_ && this.parent_.isCompFreezeAllowed());
    this.__isBlockRecycleOrReuse__ = typeof globalThis.__CheckIsInBuilderNode__ === 'function' ? globalThis.__CheckIsInBuilderNode__(parent) : false;
    stateMgmtConsole.debug(`${this.debugInfo__()}: constructor: done`);
  }

  
  // globally unique id, this is different from compilerAssignedUniqueChildId!
  id__(): number {
    return this.id_;
  }

  updateId(elmtId: number): void {
    this.id_ = elmtId;
  }

  /* Adds the elmtId to elmtIdsDelayedUpdate for delayed update
      once the view gets active
  */
  public scheduleDelayedUpdate(elmtId: number) : void {
    this.elmtIdsDelayedUpdate.add(elmtId);
  }

  public get elmtIdsDelayedUpdate(): Set<number> {
    return this.elmtIdsDelayedUpdate_;
  }

  public setParent(parent: IView): void {
    if (this.parent_ && parent) {
      stateMgmtConsole.warn(`${this.debugInfo__()}: setChild: changing parent to '${parent?.debugInfo__()} (unsafe operation)`);
    }
    this.parent_ = parent;
  }

  public getParent(): IView | undefined {
    return this.parent_;
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
  public addChild(child: IView): boolean {
    if (this.childrenWeakrefMap_.has(child.id__())) {
      stateMgmtConsole.warn(`${this.debugInfo__()}: addChild '${child?.debugInfo__()}' elmtId already exists ${child.id__()}. Internal error!`);
      return false;
    }
    this.childrenWeakrefMap_.set(child.id__(), new WeakRef(child));
    child.setParent(this as unknown as IView); // FIXME
    return true;
  }

  /**
   * remove given child and remove 'this' as its parent
   * @param child child to add
   * @returns returns false if child with given child's id does not exist
   */
  public removeChild(child: IView): boolean {
    const hasBeenDeleted = this.childrenWeakrefMap_.delete(child.id__());
    if (!hasBeenDeleted) {
      stateMgmtConsole.warn(`${this.debugInfo__()}: removeChild '${child?.debugInfo__()}', child id ${child.id__()} not known. Internal error!`);
    } else {
      child.setParent(undefined);
    }
    return hasBeenDeleted;
  }

  /**
   * Retrieve child by given id
   * @param id
   * @returns child if in map and weak ref resolves to IView object
   */
  public getChildById(id: number): IView | undefined {
    const childWeakRef = this.childrenWeakrefMap_.get(id);
    return childWeakRef ? childWeakRef.deref() : undefined;
  }

  // inform the subscribed property
  // that the View and thereby all properties
  // are about to be deleted
  abstract aboutToBeDeleted(): void;

  aboutToReuse(_: Object): void { }
  aboutToRecycle(): void { }

  public isDeleting(): boolean {
    return this.isDeleting_;
  }

  public setDeleting(): void {
    stateMgmtConsole.debug(`${this.debugInfo__()}: set as deleting (self)`);
    this.isDeleting_ = true;
  }

  public setDeleteStatusRecursively(): void {
    if (!this.childrenWeakrefMap_.size) {
      return;
    }
    stateMgmtConsole.debug(`${this.debugInfo__()}: set as deleting (${this.childrenWeakrefMap_.size} children)`);
    this.childrenWeakrefMap_.forEach((value: WeakRef<IView>) => {
      let child: IView = value.deref();
      if (child) {
        child.setDeleting();
        child.setDeleteStatusRecursively();
      }
    });
  }

  public isCompFreezeAllowed(): boolean {
    return this.isCompFreezeAllowed_;
  }

  public setActiveCount(active: boolean): void {
    // When the child node supports the Component freezing, the root node will definitely recurse to the child node. 
    // From API16, to prevent child node mistakenly activated by the parent node, reference counting is used to control node status.
    // active + 1 means count +1， inactive -1 means count -1, Expect no more than 1 
    if (Utils.isApiVersionEQAbove(16)) {
      this.activeCount_ += active ? 1 : -1;
    }
    else {
      this.activeCount_ = active ? 1 : 0;
    }
    if (this.activeCount_ > 1) {
      stateMgmtConsole.warn(`${this.debugInfo__()} activeCount_ error:${this.activeCount_}`);
    }
  }

  public getChildViewV2ForElmtId(elmtId: number): ViewV2 | undefined {
    const optComp = this.childrenWeakrefMap_.get(elmtId);
    return optComp?.deref() && (optComp.deref() instanceof ViewV2) ?
      optComp?.deref() as ViewV2 : undefined;
  }

  protected purgeVariableDependenciesOnElmtIdOwnFunc(elmtId: number): void {
    // ViewPU overrides to unregister ViewPU from variables, 
    // not in use in ViewV2
  }

  // overwritten by sub classes
  public debugInfo__(): string {
    return `@Component '${this.constructor.name}'[${this.id__()}]`;
  }

  public debugInfoRegisteredElmtIds(): string {
    return this.updateFuncByElmtId.debugInfoRegisteredElmtIds();
  }

  // for given elmtIds look up their component name/type and format a string out of this info
  // use function only for debug output and DFX.
  public debugInfoElmtIds(elmtIds: Array<number>): string {
    let result: string = '';
    let sepa: string = '';
    elmtIds.forEach((elmtId: number) => {
      result += `${sepa}${this.debugInfoElmtId(elmtId)}`;
      sepa = ', ';
    });
    return result;
  }

  public debugInfoElmtId(elmtId: number, isProfiler: boolean = false): string | ElementType {

    return isProfiler ? {
      elementId: elmtId,
      elementTag: this.updateFuncByElmtId.get(elmtId).getComponentName(),
      isCustomNode: this.childrenWeakrefMap_.has(elmtId)
    } : this.updateFuncByElmtId.debugInfoElmtId(elmtId);
  }

  public dumpStateVars(): void {
    stateMgmtConsole.debug(`${this.debugInfo__()}:  State variables:\n ${this.debugInfoStateVars()}`);
  }

  protected abstract debugInfoStateVars(): string;

  public isViewActive(): boolean {
    return this.activeCount_ > 0;
  }

  // abstract functions to be implemented by application defined class / transpiled code
  protected abstract purgeVariableDependenciesOnElmtId(removedElmtId: number);
  protected abstract initialRender(): void;
  protected abstract rerender(): void;
  protected abstract get isViewV2(): boolean;

  public abstract updateRecycleElmtId(oldElmtId: number, newElmtId: number): void;
  public abstract updateStateVars(params: Object);
  public abstract UpdateElement(elmtId: number): void;

  public dumpReport(): void {
    stateMgmtConsole.warn(`Printing profiler information`);
    stateMgmtProfiler.report();
  }

  public updateStateVarsOfChildByElmtId(elmtId, params: Object): void {
    stateMgmtProfiler.begin('ViewPU/V2.updateStateVarsOfChildByElmtId');
    stateMgmtConsole.debug(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - start`);

    if (elmtId < 0) {
      stateMgmtConsole.warn(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - invalid elmtId - internal error!`);
      stateMgmtProfiler.end();
      return;
    }
    let iChild: IView = this.getChildById(elmtId);
    if (!iChild || !((iChild instanceof ViewPU) || (iChild instanceof ViewV2))) {
      stateMgmtConsole.warn(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - no child with this elmtId - internal error!`);
      stateMgmtProfiler.end();
      return;
    }
    const child = iChild as ViewPU | ViewV2;
    if ('updateStateVars' in child) {
      child.updateStateVars(params);
    }
    stateMgmtConsole.debug(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - end`);
    stateMgmtProfiler.end();
  }

  // request list of all (global) elmtIds of deleted UINodes and unregister from the all ViewPUs/ViewV2
  // this function equals purgeDeletedElmtIdsRecursively because it does un-registration for all ViewPU/V2's
  protected purgeDeletedElmtIds(): void {
    stateMgmtConsole.debug(`purgeDeletedElmtIds @Component '${this.constructor.name}' (id: ${this.id__()}) start ...`);
    // request list of all (global) elmtIds of deleted UINodes that need to be unregistered
    UINodeRegisterProxy.obtainDeletedElmtIds();
    // unregister the removed elmtIds requested from the cpp side for all ViewPUs/ViewV2, it will make the first ViewPUs/ViewV2 slower
    // than before, but the rest ViewPUs/ViewV2 will be faster
    UINodeRegisterProxy.unregisterElmtIdsFromIViews();
    stateMgmtConsole.debug(`purgeDeletedElmtIds @Component '${this.constructor.name}' (id: ${this.id__()}) end... `);
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
    stateMgmtProfiler.begin('ViewPU/V2.forceCompleteRerender');
    stateMgmtConsole.debug(`${this.debugInfo__()}: forceCompleteRerender - start.`);

    // see which elmtIds are managed by this View
    // and clean up all book keeping for them
    this.purgeDeletedElmtIds();

    Array.from(this.updateFuncByElmtId.keys()).sort(ViewPU.compareNumber).forEach(elmtId => this.UpdateElement(elmtId));

    if (!deep) {
      stateMgmtConsole.debug(`${this.debugInfo__()}: forceCompleteRerender - end`);
      stateMgmtProfiler.end();
      return;
    }
    for (const child of this.childrenWeakrefMap_.values()) {
      const childView: IView | undefined = child.deref();

      if (!childView) {
        continue;
      }

      if (child instanceof ViewPU) {
          if (!child.isRecycled()) {
            child.forceCompleteRerender(true);
          } else {
            child.delayCompleteRerender(deep);
          }
      } else {
        childView.forceCompleteRerender(true);
      }
    }
    stateMgmtConsole.debug(`${this.debugInfo__()}: forceCompleteRerender - end`);
    stateMgmtProfiler.end();
  }

  /**
  * force a complete rerender / update on specific node by executing update function.
  *
  * @param elmtId which node needs to update.
  *
  * framework internal functions, apps must not call
  */
  public forceRerenderNode(elmtId: number): void {
    stateMgmtProfiler.begin('ViewPU/V2.forceRerenderNode');
    // see which elmtIds are managed by this View
    // and clean up all book keeping for them
    this.purgeDeletedElmtIds();
    this.UpdateElement(elmtId);

    // remove elemtId from dirtDescendantElementIds.
    this.dirtDescendantElementIds_.delete(elmtId);
    stateMgmtProfiler.end();
  }

  /**
   * for C++ to judge whether a CustomNode has updateFunc with specified nodeId.
   * use same judgement with UpdateElement, to make sure it can rerender if return true.
   *
   * @param elmtId query ID
   *
   * framework internal function
   */
  public hasNodeUpdateFunc(elmtId: number): boolean {
    const entry: UpdateFuncRecord | undefined = this.updateFuncByElmtId.get(elmtId);
    const updateFunc = entry ? entry.getUpdateFunc() : undefined;
    // if this component does not have updateFunc for elmtId, return false.
    return typeof updateFunc === 'function';
  }

  public static pauseRendering(): void {
    PUV2ViewBase.renderingPaused = true;
  }

  public static restoreRendering(): void {
    PUV2ViewBase.renderingPaused = false;
  }

  // performs the update on a branch within if() { branch } else if (..) { branch } else { branch }
  public ifElseBranchUpdateFunction(branchId: number, branchfunc: () => void): void {
    const oldBranchid: number = If.getBranchId();

    if (branchId === oldBranchid) {
      stateMgmtConsole.debug(`${this.debugInfo__()}: ifElseBranchUpdateFunction: IfElse branch unchanged, no work to do.`);
      return;
    }
    PUV2ViewBase.arkThemeScopeManager?.onIfElseBranchUpdateEnter()
    // branchid identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
    // ifElseNode stores the most recent branch, so we can compare
    // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to if .. else change
    let removedChildElmtIds = new Array<number>();
    let reservedChildElmtIds = new Array<number>();
    If.branchId(branchId, removedChildElmtIds, reservedChildElmtIds);

    for (const reservedChildElmtId of reservedChildElmtIds) {
      this.updateFuncByElmtId.get(reservedChildElmtId)?.setPending(true);
    }

    //un-registers the removed child elementIDs using proxy
    UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);

    // purging these elmtIds from state mgmt will make sure no more update function on any deleted child wi;ll be executed
    stateMgmtConsole.debug(`${this.debugInfo__()}: ifElseBranchUpdateFunction: elmtIds need unregister after if/else branch switch: ${JSON.stringify(removedChildElmtIds)}`);
    this.purgeDeletedElmtIds();

    branchfunc();

    let retakenElmtIds = new Array<number>();
    const res: boolean = If.getRetakenElmtIds(retakenElmtIds);
    if (res) {
      for (const retakenElmtId of retakenElmtIds) {
        this.updateFuncByElmtId.get(retakenElmtId)?.setPending(false);
        if (this.updateFuncByElmtId.get(retakenElmtId)?.isChanged() && !this.dirtDescendantElementIds_.has(retakenElmtId)) {
          this.dirtRetakenElementIds_.add(retakenElmtId);
        }
        this.updateFuncByElmtId.get(retakenElmtId)?.setIsChanged(false);
      }
    }

    PUV2ViewBase.arkThemeScopeManager?.onIfElseBranchUpdateExit(removedChildElmtIds)
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
  public forEachUpdateFunction(
    elmtId: number,
    itemArray: Array<any>,
    itemGenFunc: (item: any, index?: number) => void,
    idGenFunc?: (item: any, index?: number) => string,
    itemGenFuncUsesIndex: boolean = false,
    idGenFuncUsesIndex: boolean = false
  ): void {

    stateMgmtProfiler.begin('ViewPU/V2.forEachUpdateFunction');
    stateMgmtConsole.debug(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render) start ...`);

    if (itemArray === null || itemArray === undefined) {
      stateMgmtConsole.applicationError(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render): input array is null or undefined error. Application error!`);
      stateMgmtProfiler.end();
      return;
    }

    if (typeof itemGenFunc !== 'function') {
      stateMgmtConsole.applicationError(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render): Item generation function missing. Application error!`);
      stateMgmtProfiler.end();
      return;
    }

    if (idGenFunc !== undefined && typeof idGenFunc !== 'function') {
      stateMgmtConsole.applicationError(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render): id generator is not a function. Application error!`);
      stateMgmtProfiler.end();
      return;
    }

    if (idGenFunc === undefined) {
      stateMgmtConsole.debug(`${this.debugInfo__()}: forEachUpdateFunction: providing default id gen function `);
      idGenFuncUsesIndex = true;
      // catch possible error caused by Stringify and re-throw an Error with a meaningful (!) error message
      idGenFunc = (item: any, index: number): string => {
        try {
          return `${index}__${JSON.stringify(item)}`;
        } catch (e) {
          throw new Error(`${this.debugInfo__()}: ForEach id ${elmtId}: use of default id generator function not possible on provided data structure. Need to specify id generator function (ForEach 3rd parameter). Application Error!`);
        }
      };
    }

    let diffIndexArray = []; // New indexes compared to old one.
    let newIdArray = [];
    let idDuplicates = [];
    const arr = itemArray; // just to trigger a 'get' onto the array

    // ID gen is with index.
    if (idGenFuncUsesIndex || idGenFunc.length > 1) {
      // Create array of new ids.
      arr.forEach((item, indx) => {
        newIdArray.push(idGenFunc(item, indx));
      });
    }
    else {
      // Create array of new ids.
      arr.forEach((item, index) => {
        newIdArray.push(`${itemGenFuncUsesIndex ? index + '_' : ''}` + idGenFunc(item));
      });
    }

    // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to foreach change
    let removedChildElmtIds = [];
    // Set new array on C++ side.
    // C++ returns array of indexes of newly added array items.
    // these are indexes in new child list.
    ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates, removedChildElmtIds);

    // Its error if there are duplicate IDs.
    if (idDuplicates.length > 0) {
      idDuplicates.forEach((indx) => {
        stateMgmtConsole.error(`Error: ForEach id generated for ${indx}${indx < 4 ? indx === 2 ? 'nd' : 'rd' : 'th'} array item is duplicated.`);
      });
      stateMgmtConsole.applicationError(`${this.debugInfo__()}: Ids generated by the ForEach id gen function must be unique. Application error!`);
    }

    stateMgmtConsole.debug(`${this.debugInfo__()}: forEachUpdateFunction: diff indexes ${JSON.stringify(diffIndexArray)} . `);

    // Item gen is with index.
    stateMgmtConsole.debug(`   ... item Gen ${itemGenFuncUsesIndex ? 'with' : 'without'} index`);
    // Create new elements if any.
    stateMgmtProfiler.begin('ViewPU/V2.forEachUpdateFunction (native)');
    diffIndexArray.forEach((indx) => {
      ForEach.createNewChildStart(newIdArray[indx], this);
      if (itemGenFuncUsesIndex) {
        itemGenFunc(arr[indx], indx);
      } else {
        itemGenFunc(arr[indx]);
      }
      ForEach.createNewChildFinish(newIdArray[indx], this);
    });

    // un-registers the removed child elementIDs using proxy
    UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);

    // purging these elmtIds from state mgmt will make sure no more update function on any deleted child will be executed
    stateMgmtConsole.debug(`${this.debugInfo__()}: forEachUpdateFunction: elmtIds need unregister after foreach key change: ${JSON.stringify(removedChildElmtIds)}`);
    this.purgeDeletedElmtIds();

    stateMgmtConsole.debug(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render) - DONE.`);
    stateMgmtProfiler.end();
    stateMgmtProfiler.end();
  }

  public createOrGetNode(elmtId: number, builder: () => ArkComponent): object {
    const entry = this.updateFuncByElmtId.get(elmtId);
    if (entry === undefined) {
      throw new Error(`${this.debugInfo__()} fail to create node, elmtId is illegal`);
    }
    let nodeInfo = entry.getNode();
    if (nodeInfo === undefined) {
      nodeInfo = builder();
      entry.setNode(nodeInfo);
    }
    return nodeInfo;
  }

  /**
   * getNodeById is used to get ArkComponent stored updateFuncByElmtId
   * @param elmtId -  the id of the component
   * @returns ArkComponent | undefined
   */
  public getNodeById(elmtId: number): ArkComponent | undefined {
    const entry = this.updateFuncByElmtId.get(elmtId);
    return entry ? entry.getNode() : undefined;
  }

  /**
   * return its elmtId if currently rendering or re-rendering an UINode
   * otherwise return UINodeRegisterProxy.notRecordingDependencies
   * set in observeComponentCreation(2)
   */
  public getCurrentlyRenderedElmtId() {
    return PUV2ViewBase.renderingPaused || this.currentlyRenderedElmtIdStack_.length === 0
      ? UINodeRegisterProxy.notRecordingDependencies
      : this.currentlyRenderedElmtIdStack_[this.currentlyRenderedElmtIdStack_.length - 1];
  }

  public debugInfoViewHierarchy(recursive: boolean = false): string {
    return this.debugInfoViewHierarchyInternal(0, recursive);
  }

  public debugInfoViewHierarchyInternal(depth: number = 0, recursive: boolean = false): string {
    let retVaL: string = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]`;
    retVaL += (this instanceof ViewPU) ? 'ViewPU' : 'ViewV2';
    if (this.isCompFreezeAllowed()) {
      retVaL += ` {freezeWhenInactive : ${this.isCompFreezeAllowed()}}`;
    }
    retVaL += ` {isViewActive: ${this.isViewActive()}, isDeleting_: ${this.isDeleting_}}`;
    if (depth < 1 || recursive) {
      this.childrenWeakrefMap_.forEach((weakChild: WeakRef<IView>) => {
        retVaL += weakChild.deref()?.debugInfoViewHierarchyInternal(depth + 1, recursive);
      });
    }
    return retVaL;
  }

  public debugInfoUpdateFuncByElmtId(recursive: boolean = false): string {
    return this.debugInfoUpdateFuncByElmtIdInternal({ total: 0 }, 0, recursive);
  }

  public debugInfoUpdateFuncByElmtIdInternal(counter: ProfileRecursionCounter, depth: number = 0, recursive: boolean = false): string {
    let retVaL: string = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
    this.updateFuncByElmtId.forEach((value, key, map) => {
      retVaL += `\n${'  '.repeat(depth + 2)}${value.getComponentName()}[${key}]`;
    });
    counter.total += this.updateFuncByElmtId.size;
    retVaL += `\n${'  '.repeat(depth + 1)}}[${this.updateFuncByElmtId.size}]`;
    if (recursive) {
      this.childrenWeakrefMap_.forEach((value, key, map) => {
        retVaL += value.deref()?.debugInfoUpdateFuncByElmtIdInternal(counter, depth + 1, recursive);
      });
    }
    if (recursive && depth === 0) {
      retVaL += `\nTotal: ${counter.total}`;
    }
    return retVaL;
  }

  public debugInfoInactiveComponents(): string {
    // As active status has been added to -viewHierarchy,
    // it is more convenient to use -viewHierarchy instead of -inactiveComponents...
    return Array.from(PUV2ViewBase.inactiveComponents_)
      .map((component) => `- ${component}`).join('\n');
  }

  /**
   * on first render create a new Instance of Repeat
   * on re-render connect to existing instance
   * @param arr
   * @returns
   */
  abstract __mkRepeatAPI<I>(arr: Array<I>): RepeatAPI<I>;

  onGlobalThemeChanged(): void {
  }

  public static setArkThemeScopeManager(mgr: ArkThemeScopeManager): void {
    PUV2ViewBase.arkThemeScopeManager = mgr
  }

  public findViewInHierarchy(id: number): ViewPU | ViewV2 {
    let weakChild = this.childrenWeakrefMap_.get(id);
    if (weakChild) {
      const child = weakChild.deref();
      // found child with id, is it a ViewPU?
      return (child instanceof ViewPU || child instanceof ViewV2) ? child : undefined;
    }

    // did not find, continue searching
    let retVal: ViewPU | ViewV2 = undefined;
    for (const [key, value] of this.childrenWeakrefMap_.entries()) {
      retVal = value.deref().findViewInHierarchy(id);
      if (retVal) {
        break;
      }
    }
    return retVal;
  }
  /**
   * onDumpInfo is used to process commands delivered by the hidumper process
   * @param commands -  list of commands provided in the shell
   * @returns void
   */
  protected onDumpInfo(commands: string[]): void {

    let dfxCommands: DFXCommand[] = this.processOnDumpCommands(commands);

    dfxCommands.forEach((command) => {
      let view: ViewPU | ViewV2 = undefined;
      if (command.viewId) {
        view = this.findViewInHierarchy(command.viewId);
        if (!view) {
          DumpLog.print(0, `\nTarget view: ${command.viewId} not found for command: ${command.what}\n`);
          return;
        }
      } else {
        view = this as unknown as ViewPU | ViewV2;
        command.viewId = view.id__();
      }
      let headerStr: string = view instanceof ViewPU ? 'ViewPU' : 'ViewV2';
      switch (command.what) {
        case '-dumpAll':
          view.printDFXHeader(headerStr + 'Info', command);
          DumpLog.print(0, view.debugInfoView(command.isRecursive));
          break;
        case '-viewHierarchy':
          view.printDFXHeader(headerStr + 'Hierarchy', command);
          DumpLog.print(0, view.debugInfoViewHierarchy(command.isRecursive));
          break;
        case '-stateVariables':
          view.printDFXHeader(headerStr + 'State Variables', command);
          DumpLog.print(0, view.debugInfoStateVars());
          break;
        case '-registeredElementIds':
          view.printDFXHeader(headerStr + 'Registered Element IDs', command);
          DumpLog.print(0, view.debugInfoUpdateFuncByElmtId(command.isRecursive));
          break;
        case '-dirtyElementIds':
          view.printDFXHeader(headerStr + 'Dirty Registered Element IDs', command);
          DumpLog.print(0, view.debugInfoDirtDescendantElementIds(command.isRecursive));
          break;
        case '-inactiveComponents':
          view.printDFXHeader('List of Inactive Components', command);
          DumpLog.print(0, view.debugInfoInactiveComponents());
          break;
        case '-profiler':
          view.printDFXHeader('Profiler Info', command);
          view.dumpReport();
          this.sendStateInfo('{}');
          break;
        default:
          DumpLog.print(0, `\nUnsupported JS DFX dump command: [${command.what}, viewId=${command.viewId}, isRecursive=${command.isRecursive}]\n`);
      }
    });
  }

  private printDFXHeader(header: string, command: DFXCommand): void {
    let length: number = 50;
    let remainder: number = length - header.length < 0 ? 0 : length - header.length;
    DumpLog.print(0, `\n${'-'.repeat(remainder / 2)}${header}${'-'.repeat(remainder / 2)}`);
    DumpLog.print(0, `[${command.what}, viewId=${command.viewId}, isRecursive=${command.isRecursive}]\n`);
  }

  private processOnDumpCommands(commands: string[]): DFXCommand[] {
    let isFlag: Function = (param: string): boolean => {
      return '-r'.match(param) != null || param.startsWith('-viewId=');
    };

    let dfxCommands: DFXCommand[] = [];

    for (let i: number = 0; i < commands.length; i++) {
      let command = commands[i];
      if (isFlag(command)) {
        if (command.startsWith('-viewId=')) {
          let dfxCommand: DFXCommand = dfxCommands[dfxCommands.length - 1];
          if (dfxCommand) {
            let input: string[] = command.split('=');
            if (input[1]) {
              let viewId: number = Number.parseInt(input[1]);
              dfxCommand.viewId = Number.isNaN(viewId) ? UINodeRegisterProxy.notRecordingDependencies : viewId;
            }
          }
        } else if (command.match('-r')) {
          let dfxCommand: DFXCommand = dfxCommands[dfxCommands.length - 1];
          if (dfxCommand) {
            dfxCommand.isRecursive = true;
          }
        }
      } else {
        dfxCommands.push({
          what: command,
          viewId: undefined,
          isRecursive: false,
        });
      }
    }
    return dfxCommands;
  }

  // dump state var for v1 and v2 and send the dump value to ide to show in inspector
  public onDumpInspector(): string {
    const dumpInfo: DumpInfo = new DumpInfo();
    dumpInfo.viewInfo = {
      componentName: this.constructor.name, id: this.id__(), isV2: this.isViewV2,
      isCompFreezeAllowed_:this.isCompFreezeAllowed_, isViewActive_: this.isViewActive()
    };
    let resInfo: string = '';
    try {
      stateMgmtDFX.getDecoratedVariableInfo(this, dumpInfo);
      resInfo = JSON.stringify(dumpInfo);
    } catch (error) {
      stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in getInspector: ${(error as Error).message}`);
    }
    return resInfo;
  }

  public traverseChildDoRecycleOrReuse(recyleOrReuse: boolean): void {
    this.childrenWeakrefMap_.forEach((weakRefChild) => {
      const child = weakRefChild.deref();
      if (
        child &&
        (child instanceof ViewPU || child instanceof ViewV2) &&
        !child.hasBeenRecycled_ &&
        !child.__isBlockRecycleOrReuse__
      ) {
        recyleOrReuse ? child.aboutToRecycleInternal() : child.aboutToReuseInternal();
      } // if child
    });
  }
} // class PUV2ViewBase
