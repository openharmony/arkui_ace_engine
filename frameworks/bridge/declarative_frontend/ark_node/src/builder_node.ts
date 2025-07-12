/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
/// <reference path="../../state_mgmt/src/lib/common/ifelse_native.d.ts" />
/// <reference path="../../state_mgmt/src/lib/puv2_common/puv2_viewstack_processor.d.ts" />
/// <reference path="./disposable.ts" />

class BuilderNode extends Disposable {
  private _JSBuilderNode: JSBuilderNode;
  // the name of "nodePtr_" is used in ace_engine/interfaces/native/node/native_node_napi.cpp.
  private nodePtr_: NodePtr;
  constructor(uiContext: UIContext, options: RenderOptions) {
    super();
    let jsBuilderNode = new JSBuilderNode(uiContext, options);
    this._JSBuilderNode = jsBuilderNode;
    let id = Symbol('BuilderRootFrameNode');
    BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.set(id, jsBuilderNode);
    BuilderNodeFinalizationRegisterProxy.register(this, { name: 'BuilderRootFrameNode', idOfNode: id });
  }
  public update(params: Object) {
    this._JSBuilderNode.update(params);
  }
  public build(builder: WrappedBuilder<Object[]>, params?: Object, options?: BuildOptions,): void {
    this._JSBuilderNode.build(builder, params, options);
    this.nodePtr_ = this._JSBuilderNode.getNodePtr();
  }
  public getNodePtr(): NodePtr {
    return this._JSBuilderNode.getValidNodePtr();
  }
  public getFrameNode(): FrameNode {
    return this._JSBuilderNode.getFrameNode();
  }
  public getFrameNodeWithoutCheck(): FrameNode | null {
    return this._JSBuilderNode.getFrameNodeWithoutCheck();
  }
  public postTouchEvent(touchEvent: TouchEvent): boolean {
    __JSScopeUtil__.syncInstanceId(this._JSBuilderNode.getInstanceId());
    let ret = this._JSBuilderNode.postTouchEvent(touchEvent);
    __JSScopeUtil__.restoreInstanceId();
    return ret;
  }
  public postInputEvent(event: InputEventType): boolean {
    __JSScopeUtil__.syncInstanceId(this._JSBuilderNode.getInstanceId());
    let ret = this._JSBuilderNode.postInputEvent(event);
    __JSScopeUtil__.restoreInstanceId();
    return ret;
  }
  public dispose(): void {
    super.dispose();
    this._JSBuilderNode.dispose();
  }
  public isDisposed(): boolean {
    return super.isDisposed() && (this._JSBuilderNode ? this._JSBuilderNode.isDisposed() : true);
  }
  public reuse(param?: Object): void {
    this._JSBuilderNode.reuse(param);
  }
  public recycle(): void {
    this._JSBuilderNode.recycle();
  }
  public updateConfiguration(): void {
    this._JSBuilderNode.updateConfiguration();
  }
  public onReuseWithBindObject(param?: Object): void {
    this._JSBuilderNode.onReuseWithBindObject(param);
  }
  public onRecycleWithBindObject(): void {
    this._JSBuilderNode.onRecycleWithBindObject();
  }
  public inheritFreezeOptions(enable: boolean): void {
    this._JSBuilderNode.inheritFreezeOptions(enable);
  }
}

class JSBuilderNode extends BaseNode implements IDisposable {
  private params_: Object;
  private uiContext_: UIContext;
  private frameNode_: FrameNode;
  private _nativeRef: NativeStrongRef;
  private _supportNestingBuilder: boolean;
  private _proxyObjectParam: Object;
  private bindedViewOfBuilderNode:ViewPU;
  private disposable_: Disposable;
  private inheritFreeze: boolean;
  private allowFreezeWhenInactive: boolean;
  private parentallowFreeze: boolean;
  private isFreeze: boolean;
  public __parentViewOfBuildNode?: ViewBuildNodeBase;
  constructor(uiContext: UIContext, options?: RenderOptions) {
    super(uiContext, options);
    this.uiContext_ = uiContext;
    this.updateFuncByElmtId = new UpdateFuncsByElmtId();
    this._supportNestingBuilder = false;
    this.disposable_ = new Disposable();
    this.inheritFreeze = false;
    this.allowFreezeWhenInactive = false;
    this.parentallowFreeze = false;
    this.isFreeze = false;
    this.__parentViewOfBuildNode = undefined;
  }
  public findProvidePU__(providePropName: string): ObservedPropertyAbstractPU<any> | undefined {
    if (this.__enableBuilderNodeConsume__ && this.__parentViewOfBuildNode) {
      return this.__parentViewOfBuildNode.findProvidePU__(providePropName);
    }
    return undefined;
  }
  public reuse(param: Object): void {
    this.updateStart();
    try {
      this.childrenWeakrefMap_.forEach((weakRefChild) => {
        const child = weakRefChild.deref();
        if (child) {
          if (child instanceof ViewPU) {
            child.aboutToReuseInternal(param);
          }
          else {
            // FIXME fix for mixed V2 - V3 Hierarchies
            throw new Error('aboutToReuseInternal: Recycle not implemented for ViewV2, yet');
          }
        } // if child
      });
    } catch (err) {
      this.updateEnd();
      throw err;
    }
    this.updateEnd();
  }
  public recycle(): void {
    this.childrenWeakrefMap_.forEach((weakRefChild) => {
      const child = weakRefChild.deref();
      if (child) {
        if (child instanceof ViewPU) {
          child.aboutToRecycleInternal();
        }
        else {
          // FIXME fix for mixed V2 - V3 Hierarchies
          throw new Error('aboutToRecycleInternal: Recycle not yet implemented for ViewV2');
        }
      } // if child
    });
  }
  public onReuseWithBindObject(param?: Object): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    super.onReuseWithBindObject(param);
    __JSScopeUtil__.restoreInstanceId();
  }
  public onRecycleWithBindObject(): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    super.onRecycleWithBindObject();
    __JSScopeUtil__.restoreInstanceId();
  }
  public inheritFreezeOptions(enable: boolean): void {
    this.inheritFreeze = enable;
    if (enable) {
      this.setAllowFreezeWhenInactive(this.getParentAllowFreeze());
    } else {
      this.setAllowFreezeWhenInactive(false);
    }
  }
  public getInheritFreeze(): boolean {
    return this.inheritFreeze;
  }
  public setAllowFreezeWhenInactive(enable: boolean): void {
    this.allowFreezeWhenInactive = enable;
  }
  public getAllowFreezeWhenInactive(): boolean {
    return this.allowFreezeWhenInactive;
  }
  public setParentAllowFreeze(enable: boolean): void {
    this.parentallowFreeze = enable;
  }
  public getParentAllowFreeze(): boolean {
    return this.parentallowFreeze;
  }
  public getIsFreeze(): boolean {
    return this.isFreeze;
  }
  public getCardId(): number {
    return -1;
  }
  private isObject(param: Object): boolean {
    const typeName = Object.prototype.toString.call(param);
    const objectName = `[object Object]`;
    if (typeName === objectName) {
      return true;
    } else {
      return false;
    }
  }
  private buildWithNestingBuilder(builder: WrappedBuilder<Object[]>, supportLazyBuild: boolean): void {
    if (this._supportNestingBuilder && this.isObject(this.params_)) {
      this._proxyObjectParam = new Proxy(this.params_, {
        set(target, property, val): boolean {
          throw Error(`@Builder : Invalid attempt to set(write to) parameter '${property.toString()}' error!`);
        },
        get: (target, property, receiver): Object => { return this.params_?.[property] }
      });
      this.nodePtr_ = super.create(builder.builder?.bind(this.bindedViewOfBuilderNode ? this.bindedViewOfBuilderNode : this),
        this._proxyObjectParam, this.updateNodeFromNative, this.updateConfiguration, supportLazyBuild);
    } else {
      this.nodePtr_ = super.create(builder.builder?.bind(this.bindedViewOfBuilderNode ? this.bindedViewOfBuilderNode : this),
        this.params_, this.updateNodeFromNative, this.updateConfiguration, supportLazyBuild);
    }
  }
  public build(builder: WrappedBuilder<Object[]>, params?: Object, options?: BuildOptions): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    this._supportNestingBuilder = options?.nestingBuilderSupported ? options.nestingBuilderSupported : false;
    const supportLazyBuild = options?.lazyBuildSupported ? options.lazyBuildSupported : false;
    this.bindedViewOfBuilderNode = options?.bindedViewOfBuilderNode;
    this.__enableBuilderNodeConsume__ = (options?.enableProvideConsumeCrossing)? (options?.enableProvideConsumeCrossing) : false; 
    this.params_ = params;
    if (options?.localStorage instanceof LocalStorage) {
      this.setShareLocalStorage(options.localStorage);
    }
    this.updateFuncByElmtId.clear();
    if(this.bindedViewOfBuilderNode){
      globalThis.__viewPuStack__?.push(this.bindedViewOfBuilderNode); 
    }
    this.buildWithNestingBuilder(builder, supportLazyBuild);
    if(this.bindedViewOfBuilderNode){
      globalThis.__viewPuStack__?.pop(); 
    }
    this._nativeRef = getUINativeModule().nativeUtils.createNativeStrongRef(this.nodePtr_);
    if (this.frameNode_ === undefined || this.frameNode_ === null) {
      this.frameNode_ = new BuilderRootFrameNode(this.uiContext_);
    }
    this.frameNode_.setNodePtr(this._nativeRef, this.nodePtr_);
    this.frameNode_.setRenderNode(this._nativeRef);
    this.frameNode_.setBaseNode(this);
    this.frameNode_.setBuilderNode(this);
    let id = this.frameNode_.getUniqueId();
    if (this.id_ && this.id_ !== id) {
      this.__parentViewOfBuildNode?.removeChildBuilderNode(this.id_);
    }
    this.id_ = id;
    this.__parentViewOfBuildNode?.addChildBuilderNode(this);
    FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.set(this.frameNode_.getUniqueId(), new WeakRef(this.frameNode_));
    __JSScopeUtil__.restoreInstanceId();
  }
  public update(param: Object) {
    if (this.isFreeze) {
      this.params_ = param;
      return;
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    this.updateStart();
    try {
      this.purgeDeletedElmtIds();
      this.params_ = param;
      Array.from(this.updateFuncByElmtId.keys()).sort((a: number, b: number): number => {
        return (a < b) ? -1 : (a > b) ? 1 : 0;
      }).forEach(elmtId => this.UpdateElement(elmtId));
    } catch (err) {
      this.updateEnd();
      throw err;
    }
    this.updateEnd();
    __JSScopeUtil__.restoreInstanceId();
  }
  public updateConfiguration(): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    this.updateStart();
    try {
      this.purgeDeletedElmtIds();
      Array.from(this.updateFuncByElmtId.keys()).sort((a: number, b: number): number => {
        return (a < b) ? -1 : (a > b) ? 1 : 0;
      }).forEach(elmtId => this.UpdateElement(elmtId));
      for (const child of this.childrenWeakrefMap_.values()) {
        const childView = child.deref();
        if (childView) {
          childView.forceCompleteRerender(true);
        }
      }
      getUINativeModule().frameNode.updateConfiguration(this.getFrameNode()?.getNodePtr());
    } catch (err) {
      this.updateEnd();
      throw err;
    }
    this.updateEnd();
    __JSScopeUtil__.restoreInstanceId();
  }
  private UpdateElement(elmtId: number): void {
    // do not process an Element that has been marked to be deleted
    const obj: UpdateFunc | UpdateFuncRecord | undefined = this.updateFuncByElmtId.get(elmtId);
    const updateFunc = (typeof obj === 'object') ? obj.getUpdateFunc() : null;
    if (typeof updateFunc === 'function') {
      updateFunc(elmtId, /* isFirstRender */ false);
      this.finishUpdateFunc();
    }
  }

  public setActiveInternal(active: boolean, isReuse: boolean = false): void {
    stateMgmtProfiler.begin('BuilderNode.setActive');
    if (!isReuse) {
      if (active && this.isFreeze) {
        this.isFreeze = false;
        this.update(this.params_);
      } else if (!active) {
        this.isFreeze = this.allowFreezeWhenInactive;
      }
    }
    if (this.inheritFreeze) {
      this.propagateToChildren(this.childrenWeakrefMap_, active, isReuse);
      this.propagateToChildren(this.builderNodeWeakrefMap_, active, isReuse);
    }
    stateMgmtProfiler.end();
  }

  public purgeDeleteElmtId(rmElmtId: number): boolean {
    const result = this.updateFuncByElmtId.delete(rmElmtId);
    if (result) {
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
    }
    return result;
  }

  public getFrameNode(): FrameNode | null {
    if (
      this.frameNode_ !== undefined &&
      this.frameNode_ !== null &&
      this.frameNode_.getNodePtr() !== null
    ) {
      return this.frameNode_;
    }
    return null;
  }

  public getFrameNodeWithoutCheck(): FrameNode | null | undefined {
    return this.frameNode_;
  }

  public observeComponentCreation(func: (arg0: number, arg1: boolean) => void) {
    let elmId: number = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmId, new WeakRef(this));
    try {
      func(elmId, true);
    } catch (error) {
      // avoid the incompatible change that move set function before updateFunc.
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmId);
      throw error;
    }
  }

  public observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: { prototype: Object; pop?: () => void }): void {
    const _componentName: string = classObject && 'name' in classObject ? (Reflect.get(classObject, 'name') as string) : 'unspecified UINode';
    const _popFunc: () => void =
      classObject && 'pop' in classObject ? classObject.pop! : () => { };
    const updateFunc = (elmtId: number, isFirstRender: boolean): void => {
      __JSScopeUtil__.syncInstanceId(this.instanceId_);
      ViewBuildNodeBase.arkThemeScopeManager?.onComponentCreateEnter(_componentName, elmtId, isFirstRender, this);
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      // if V2 @Observed/@Track used anywhere in the app (there is no more fine grained criteria),
      // enable V2 object deep observation
      // FIXME: A @Component should only use PU or V2 state, but ReactNative dynamic viewer uses both.
      if (ConfigureStateMgmt.instance.needsV2Observe()) {
        // FIXME: like in V2 setting bindId_ in ObserveV2 does not work with 'stacked'
        // update + initial render calls, like in if and ForEach case, convert to stack as well
        ObserveV2.getObserve().startRecordDependencies(this, elmtId, true);
      }
      if (this._supportNestingBuilder) {
        compilerAssignedUpdateFunc(elmtId, isFirstRender);
      } else {
        compilerAssignedUpdateFunc(elmtId, isFirstRender, this.params_);
      }
      if (!isFirstRender) {
        _popFunc();
      }
      if (ConfigureStateMgmt.instance.needsV2Observe()) {
        ObserveV2.getObserve().stopRecordDependencies();
      }
      ViewStackProcessor.StopGetAccessRecording();
      ViewBuildNodeBase.arkThemeScopeManager?.onComponentCreateExit(elmtId);
      __JSScopeUtil__.restoreInstanceId();
    };

    const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    // needs to move set before updateFunc.
    // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
    this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, classObject: classObject });
    UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
    try {
      updateFunc(elmtId, /* is first render */ true);
    } catch (error) {
      // avoid the incompatible change that move set function before updateFunc.
      this.updateFuncByElmtId.delete(elmtId);
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
      throw error;
    }
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
    if (itemArray === null || itemArray === undefined) {
      return;
    }

    if (itemGenFunc === null || itemGenFunc === undefined) {
      return;
    }

    if (idGenFunc === undefined) {
      idGenFuncUsesIndex = true;
      // catch possible error caused by Stringify and re-throw an Error with a meaningful (!) error message
      idGenFunc = (item: any, index: number): string => {
        try {
          return `${index}__${JSON.stringify(item)}`;
        } catch (e) {
          throw new Error(
            ` ForEach id ${elmtId}: use of default id generator function not possible on provided data structure. Need to specify id generator function (ForEach 3rd parameter). Application Error!`
          );
        }
      };
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
    } else {
      // Create array of new ids.
      arr.forEach((item, index) => {
        newIdArray.push(
          `${itemGenFuncUsesIndex ? index + '_' : ''}` + idGenFunc(item)
        );
      });
    }
    // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to foreach change
    let removedChildElmtIds = [];
    // Set new array on C++ side.
    // C++ returns array of indexes of newly added array items.
    // these are indexes in new child list.
    ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates, removedChildElmtIds);
    // Item gen is with index.
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
    this.purgeDeletedElmtIds();
  }
  public getNodePtr(): NodePtr {
    return this.nodePtr_;
  }
  public getValidNodePtr(): NodePtr {
    return this._nativeRef?.getNativeHandle();
  }
  public dispose(): void {
    if (this.nodePtr_) {
      getUINativeModule().frameNode.fireArkUIObjectLifecycleCallback(new WeakRef(this), 'BuilderNode', this.getFrameNode()?.getNodeType() || 'BuilderNode', this.nodePtr_);
    }
    this.disposable_.dispose();
    this.frameNode_?.dispose();
  }
  public isDisposed(): boolean {
    return this.disposable_.isDisposed() && (this._nativeRef === undefined || this._nativeRef === null);
  }
  public disposeNode(): void {
    super.disposeNode();
    this.nodePtr_ = null;
    this._nativeRef = null;
    this.frameNode_?.resetNodePtr();
  }
  updateInstance(uiContext: UIContext): void {
      this.uiContext_ = uiContext;
      this.instanceId_ = uiContext.instanceId_;
      if (this.frameNode_ !== undefined && this.frameNode_ !== null) {
          this.frameNode_.updateInstance(uiContext);
      }
  }

  private updateNodePtr(nodePtr: NodePtr)
  {
    if (nodePtr != this.nodePtr_) {
      this.dispose();
      this.nodePtr_ = nodePtr;
      this._nativeRef = getUINativeModule().nativeUtils.createNativeStrongRef(this.nodePtr_);
      this.frameNode_.setNodePtr(this._nativeRef, this.nodePtr_);
    }
  }

  private updateInstanceId(instanceId: number)
  {
    this.instanceId_ = instanceId;
  }

  protected updateNodeFromNative(instanceId: number, nodePtr: NodePtr)
  {
    this.updateNodePtr(nodePtr);
    this.updateInstanceId(instanceId);
  }

  public observeRecycleComponentCreation(name: string, recycleUpdateFunc: RecycleUpdateFunc): void {
    throw new Error('custom component in @Builder used by BuilderNode does not support @Reusable');
  }
  public ifElseBranchUpdateFunctionDirtyRetaken(): void {}
  public forceCompleteRerender(deep: boolean): void {}
  public forceRerenderNode(elmtId: number): void {}
}
