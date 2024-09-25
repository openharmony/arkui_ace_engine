/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 *
 * This file includes only framework internal classes and functions
 * non are part of SDK. Do not access from app.
 *
 * Implementation of @ComponentV2 is ViewV2
 * When transpiling @ComponentV2, the transpiler generates a class that extends from ViewV2.
 *
 */

abstract class ViewV2 extends PUV2ViewBase implements IView {

    // Set of elmtIds that need re-render
    protected dirtDescendantElementIds_: Set<number> = new Set<number>();
    public isJSBuilderNode : boolean = false;

    // Set of elements for delayed update
    private elmtIdsDelayedUpdate: Set<number> = new Set();
    private monitorIdsDelayedUpdate: Set<number> = new Set();
    private computedIdsDelayedUpdate: Set<number> = new Set();

    constructor(parent: IView, elmtId: number = UINodeRegisterProxy.notRecordingDependencies, extraInfo: ExtraInfo = undefined) {
        super(parent, elmtId, extraInfo);
        this.setIsV2(true);

        // Set the isJSBuilderNode flag to true if the parent of ViewV2 is a BuilderNode
        // This applies to components invoked by Builder functions
        if (!this.parent_ && this.checkIfBuilderNode(parent)) {
            stateMgmtConsole.debug(`ViewV2 constructor: @Component's '${this.constructor.name}' parent '${parent?.constructor.name}' is not of type 'IView'`);
            this.isJSBuilderNode = true;
        }
        stateMgmtConsole.debug(`ViewV2 constructor: Creating @Component '${this.constructor.name}' from parent '${parent?.constructor.name}'`);
    }

    /**
     * Helper function to check if a view is of type JSBuilderNode
     * This helps in reporting errors when Components with @Provider/@Consumer
     * are called from BuilderNodes.
     * Periodical track of BuilderNode elements from jsXNode.js might be needed to 
     * cross-check for changes in variables/classNames if any.
     */
    private checkIfBuilderNode(view: IView | undefined): boolean {
        return (
            view &&
            view.constructor.name === 'JSBuilderNode' &&
            typeof view['childrenWeakrefMap_'] === 'object' &&
            typeof view['uiContext_'] === 'object' &&
            view.hasOwnProperty('_supportNestingBuilder')
        );
    }

    /**
     * The `freezeState` parameter determines whether this @ComponentV2 is allowed to freeze, when inactive
     * Its called with value of the `freezeWhenInactive` parameter from the @ComponentV2 decorator,
     * or it may be called with `undefined` depending on how the UI compiler works.
     *
     * @param freezeState Only the value `true` will be used to set the freeze state,
     * otherwise it inherits from its parent instance if its freezeState is true
     */
    protected finalizeConstruction(freezeState?: boolean | undefined): void {

        ObserveV2.getObserve().constructComputed(this, this.constructor.name);
        ObserveV2.getObserve().constructMonitor(this, this.constructor.name);

        // Always use ID_REFS in ViewV2
        this[ObserveV2.ID_REFS] = {};

        // set to true if freeze parameter set for this @ComponentV2 to true
        // otherwise inherit from its parentComponent (if it exists).
        this.isCompFreezeAllowed_ = freezeState || this.isCompFreezeAllowed_;
        stateMgmtConsole.debug(`${this.debugInfo__()}: @ComponentV2 freezeWhenInactive state is set to ${this.isCompFreezeAllowed()}`);

    }

    public debugInfo__(): string {
        return `@ComponentV2 '${this.constructor.name}'[${this.id__()}]`;
    }


    private get isViewV2(): boolean {
        return true;
    }

    /**
     * Virtual function implemented in ViewPU and ViewV2
     * Unregisters and purges all child elements associated with the specified Element ID in ViewV2.
     *
     * @param rmElmtId - The Element ID to be purged and deleted
     * @returns {boolean} - Returns `true` if the Element ID was successfully deleted, `false` otherwise.
    */
    public purgeDeleteElmtId(rmElmtId: number): boolean {
        stateMgmtConsole.debug(`${this.debugInfo__()} purgeDeleteElmtId (V2) is purging the rmElmtId:${rmElmtId}`);
        const result = this.updateFuncByElmtId.delete(rmElmtId);
        if (result) {
            const childOpt = this.getChildViewV2ForElmtId(rmElmtId);
            if (childOpt) {
                childOpt.setDeleting();
                childOpt.setDeleteStatusRecursively();
            }

            // it means rmElmtId has finished all the unregistration from the js side, ElementIdToOwningViewPU_  does not need to keep it
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
        }

        // Needed only for V2
        ObserveV2.getObserve().clearBinding(rmElmtId);
        return result;
    }


    // super class will call this function from
    // its aboutToBeDeleted implementation
    protected aboutToBeDeletedInternal(): void {
        stateMgmtConsole.debug(`${this.debugInfo__()}: aboutToBeDeletedInternal`);
        // if this isDeleting_ is true already, it may be set delete status recursively by its parent, so it is not necessary
        // to set and resursively set its children any more
        if (!this.isDeleting_) {
            this.isDeleting_ = true;
            this.setDeleteStatusRecursively();
        }
        // tell UINodeRegisterProxy that all elmtIds under
        // this ViewV2 should be treated as already unregistered

        stateMgmtConsole.debug(`${this.constructor.name}: aboutToBeDeletedInternal `);

        // purge the elmtIds owned by this ViewV2 from the updateFuncByElmtId and also the state variable dependent elmtIds
        Array.from(this.updateFuncByElmtId.keys()).forEach((elmtId: number) => {
            // FIXME split View: enable delete  this purgeDeleteElmtId(elmtId);
        });

        // unregistration of ElementIDs
        stateMgmtConsole.debug(`${this.debugInfo__()}: onUnRegElementID`);

        // it will unregister removed elementids from all the ViewV2, equals purgeDeletedElmtIdsRecursively
        this.purgeDeletedElmtIds();

        // unregisters its own id once its children are unregistered above
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs([this.id__()]);

        stateMgmtConsole.debug(`${this.debugInfo__()}: onUnRegElementID  - DONE`);

        /* in case ViewPU is currently frozen
           ViewPU inactiveComponents_ delete(`${this.constructor.name}[${this.id__()}]`);
        */
        MonitorV2.clearWatchesFromTarget(this);

        this.updateFuncByElmtId.clear();
        if (this.parent_) {
            this.parent_.removeChild(this);
        }
    }

    public initialRenderView(): void {
        stateMgmtProfiler.begin(`ViewV2: initialRenderView`);
        this.initialRender();
        stateMgmtProfiler.end();
    }

    public observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: { prototype: Object, pop?: () => void }): void {
        if (this.isDeleting_) {
            stateMgmtConsole.error(`@ComponentV2 ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation2 `);
            return;
        }
        const _componentName: string = (classObject && ('name' in classObject)) ? Reflect.get(classObject, 'name') as string : 'unspecified UINode';
        const _popFunc: () => void = (classObject && 'pop' in classObject) ? classObject.pop! : (): void => { };
        const updateFunc = (elmtId: number, isFirstRender: boolean): void => {
            this.syncInstanceId();
            stateMgmtConsole.debug(`@ComponentV2 ${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`} ${_componentName}[${elmtId}] - start ....`);

            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            ObserveV2.getObserve().startRecordDependencies(this, elmtId);

            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            if (!isFirstRender) {
                _popFunc();
            }

            let node = this.getNodeById(elmtId);
            if (node !== undefined) {
                (node as ArkComponent).cleanStageValue();
            }

            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();

            stateMgmtConsole.debug(`${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`}  ${_componentName}[${elmtId}] - DONE ....`);
            this.restoreInstanceId();
        };

        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        // needs to move set before updateFunc.
        // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
        this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, classObject: classObject });
        // add element id -> owning ViewV2
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

    /**
   *
   * @param paramVariableName
   * @param @once paramVariableName
   * @param is read only, therefore, init from parent needs to be done without
   *        causing property setter() to be called
   * @param newValue
   */
    protected initParam<Z>(paramVariableName: string, newValue: Z): void {
        this.checkIsV1Proxy(paramVariableName, newValue);
        VariableUtilV2.initParam<Z>(this, paramVariableName, newValue);
    }
    /**
   *
   * @param paramVariableName
   * @param @once paramVariableName
   * @param is read only, therefore, update from parent needs to be done without
   *        causing property setter() to be called
   * @param @once reject any update
    * @param newValue
   */
    protected updateParam<Z>(paramVariableName: string, newValue: Z): void {
        this.checkIsV1Proxy(paramVariableName, newValue);
        VariableUtilV2.updateParam<Z>(this, paramVariableName, newValue);
      }

    private checkIsV1Proxy<Z>(paramVariableName: string, value: Z): void {
        if (ObservedObject.IsObservedObject(value)) {
            throw new Error(`Cannot assign the ComponentV1 value to the ComponentV2 for the property '${paramVariableName}'`);
        }
    }

    /**
   *  inform that UINode with given elmtId needs rerender
   *  does NOT exec @Watch function.
   *  only used on V2 code path from ObserveV2.fireChange.
   *
   * FIXME will still use in the future?
   */
    public uiNodeNeedUpdateV2(elmtId: number): void {
        if (this.isFirstRender()) {
            return;
        }

        stateMgmtProfiler.begin(`ViewV2.uiNodeNeedUpdate ${this.debugInfoElmtId(elmtId)}`);

        if(!this.isActive_) {
            this.scheduleDelayedUpdate(elmtId);
            return;
        }

        if (!this.dirtDescendantElementIds_.size) { //  && !this runReuse_) {
            // mark ComposedElement dirty when first elmtIds are added
            // do not need to do this every time
            this.syncInstanceId();
            this.markNeedUpdate();
            this.restoreInstanceId();
        }
        this.dirtDescendantElementIds_.add(elmtId);
        stateMgmtConsole.debug(`${this.debugInfo__()}: uiNodeNeedUpdate: updated full list of elmtIds that need re-render [${this.debugInfoElmtIds(Array.from(this.dirtDescendantElementIds_))}].`);

        stateMgmtProfiler.end();
    }


    /**
 * For each recorded dirty Element in this custom component
 * run its update function
 *
 */
    public updateDirtyElements(): void {
        stateMgmtProfiler.begin('ViewV2.updateDirtyElements');
        do {
            stateMgmtConsole.debug(`${this.debugInfo__()}: updateDirtyElements (re-render): sorted dirty elmtIds: ${Array.from(this.dirtDescendantElementIds_).sort(ViewV2.compareNumber)}, starting ....`);

            // see which elmtIds are managed by this View
            // and clean up all book keeping for them
            this.purgeDeletedElmtIds();

            // process all elmtIds marked as needing update in ascending order.
            // ascending order ensures parent nodes will be updated before their children
            // prior cleanup ensure no already deleted Elements have their update func executed
            const dirtElmtIdsFromRootNode = Array.from(this.dirtDescendantElementIds_).sort(ViewV2.compareNumber);
            // if state changed during exec update lambda inside UpdateElement, then the dirty elmtIds will be added
            // to newly created this.dirtDescendantElementIds_ Set
            dirtElmtIdsFromRootNode.forEach(elmtId => {
                this.UpdateElement(elmtId);
                this.dirtDescendantElementIds_.delete(elmtId);
            });

            if (this.dirtDescendantElementIds_.size) {
                stateMgmtConsole.applicationError(`${this.debugInfo__()}: New UINode objects added to update queue while re-render! - Likely caused by @Component state change during build phase, not allowed. Application error!`);
            }
        } while (this.dirtDescendantElementIds_.size);
        stateMgmtConsole.debug(`${this.debugInfo__()}: updateDirtyElements (re-render) - DONE`);
        stateMgmtProfiler.end();
    }


    public UpdateElement(elmtId: number): void {

        if(this.isDeleting_) {
            stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement(${elmtId}) (V2) returns with NO UPDATE, this @ComponentV2 is under deletion!`);
            return;
        }

        stateMgmtProfiler.begin('ViewV2.UpdateElement');
        if (elmtId === this.id__()) {
            // do not attempt to update itself
            stateMgmtProfiler.end();
            return;
        }
        // do not process an Element that has been marked to be deleted
        const entry: UpdateFuncRecord | undefined = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = entry ? entry.getUpdateFunc() : undefined;

        if (typeof updateFunc !== 'function') {
            stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement: update function of elmtId ${elmtId} not found, internal error!`);
        } else {
            const componentName = entry.getComponentName();
            stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement: re-render of ${componentName} elmtId ${elmtId} start ...`);
            stateMgmtProfiler.begin('ViewV2.updateFunc');
            try {
                updateFunc(elmtId, /* isFirstRender */ false);
            } catch (e) {
                stateMgmtConsole.applicationError(`Exception caught in update function of ${componentName} for elmtId ${elmtId}`, e.toString());
                throw e;
            } finally {
                stateMgmtProfiler.end();
            }
            stateMgmtProfiler.begin('ViewV2.finishUpdateFunc (native)');
            this.finishUpdateFunc(elmtId);
            stateMgmtProfiler.end();
            stateMgmtConsole.debug(`${this.debugInfo__()}: UpdateElement: re-render of ${componentName} elmtId ${elmtId} - DONE`);
        }
        stateMgmtProfiler.end();
    }

    /**
 * Retrieve child by given id
 * @param id
 * @returns child if child with this id exists and it is instance of ViewV2
 */
    public getViewV2ChildById(id: number): ViewV2 | undefined {
        const childWeakRef = this.childrenWeakrefMap_.get(id);
        const child = childWeakRef ? childWeakRef.deref() : undefined;
        return (child && child instanceof ViewV2) ? child : undefined;
    }

    /**
     * findViewPUInHierarchy function needed for @Component and @ComponentV2 mixed
     * parent - child hierarchies. Not used by ViewV2
     */
    public findViewPUInHierarchy(id: number): ViewPU | undefined {
        // this ViewV2 is not a ViewPU, continue searching amongst children
        let retVal: ViewPU = undefined;
        for (const [key, value] of this.childrenWeakrefMap_.entries()) {
            retVal = value.deref().findViewPUInHierarchy(id);
            if (retVal) {
                break;
            }
        }
        return retVal;
    }

    /* Adds the elmtId to elmtIdsDelayedUpdate for delayed update
        once the view gets active
    */
    public scheduleDelayedUpdate(elmtId: number) : void {
        this.elmtIdsDelayedUpdate.add(elmtId);
    }

    // WatchIds that needs to be fired later gets added to monitorIdsDelayedUpdate
    // monitor fireChange will be triggered for all these watchIds once this view gets active
    public addDelayedMonitorIds(watchId: number) {
        stateMgmtConsole.debug(`${this.debugInfo__()} addDelayedMonitorIds called for watchId: ${watchId}`);
        this.monitorIdsDelayedUpdate.add(watchId);
    }

    public addDelayedComputedIds(watchId: number) {
        stateMgmtConsole.debug(`${this.debugInfo__()} addDelayedComputedIds called for watchId: ${watchId}`);
        this.computedIdsDelayedUpdate.add(watchId);
    }

    public setActiveInternal(newState: boolean): void {
        stateMgmtProfiler.begin("ViewV2.setActive");

        if (!this.isCompFreezeAllowed()) {
            stateMgmtConsole.debug(`${this.debugInfo__()}: ViewV2.setActive. Component freeze state is ${this.isCompFreezeAllowed()} - ignoring`);
            stateMgmtProfiler.end();
            return;
        }

        stateMgmtConsole.debug(`${this.debugInfo__()}: ViewV2.setActive ${newState ? ' inActive -> active' : 'active -> inActive'}`);
        this.isActive_ = newState;
        if (this.isActive_) {
          this.onActiveInternal()
        } else {
          this.onInactiveInternal();
        }
        stateMgmtProfiler.end();
    }

    private onActiveInternal(): void {
        if (!this.isActive_) {
          return;
        }

        stateMgmtConsole.debug(`${this.debugInfo__()}: onActiveInternal`);
        this.performDelayedUpdate();

        // Set 'isActive_' state for all descendant child Views
        for (const child of this.childrenWeakrefMap_.values()) {
          const childView: IView | undefined = child.deref();
          if (childView) {
            childView.setActiveInternal(this.isActive_);
          }
        }
    }

    private onInactiveInternal(): void {
        if (this.isActive_) {
          return;
        }
        stateMgmtConsole.debug(`${this.debugInfo__()}: onInactiveInternal`);

        // Set 'isActive_' state for all descendant child Views
        for (const child of this.childrenWeakrefMap_.values()) {
          const childView: IView | undefined = child.deref();
          if (childView) {
            childView.setActiveInternal(this.isActive_);
          }
        }
    }

    private performDelayedUpdate(): void {
        stateMgmtProfiler.begin("ViewV2: performDelayedUpdate");
        if(this.computedIdsDelayedUpdate.size) {
            // exec computed functions
            ObserveV2.getObserve().updateDirtyComputedProps([...this.computedIdsDelayedUpdate]);
        }
        if(this.monitorIdsDelayedUpdate.size) {
          // exec monitor functions
          ObserveV2.getObserve().runDirtyMonitors(this.monitorIdsDelayedUpdate);
        }
        if(this.elmtIdsDelayedUpdate.size) {
          // update re-render of updated element ids once the view gets active
          if(this.dirtDescendantElementIds_.size === 0) {
            this.dirtDescendantElementIds_ = new Set(this.elmtIdsDelayedUpdate);
          }
          else {
            this.elmtIdsDelayedUpdate.forEach((element) => {
              this.dirtDescendantElementIds_.add(element);
            });
          }
        }
        this.markNeedUpdate();
        this.elmtIdsDelayedUpdate.clear();
        this.monitorIdsDelayedUpdate.clear();
        this.computedIdsDelayedUpdate.clear();
        stateMgmtProfiler.end();
    }

    /*
      findProvidePU finds @Provided property recursively by traversing ViewPU's towards that of the UI tree root @Component:
      if 'this' ViewPU has a @Provide('providedPropName') return it, otherwise ask from its parent ViewPU.
      function needed for mixed @Component and @ComponentV2 parent child hierarchies.
    */
    public findProvidePU(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined {
        return this.getParent()?.findProvidePU(providedPropName);
    }

    get localStorage_(): LocalStorage {
        // FIXME check this also works for root @ComponentV2
        return (this.getParent()) ? this.getParent().localStorage_ : new LocalStorage({ /* empty */ });
    }

    /**
     * @function observeRecycleComponentCreation
     * @description custom node recycle creation not supported for V2. So a dummy function is implemented to report
     * an error message
     * @param name custom node name
     * @param recycleUpdateFunc custom node recycle update which can be converted to a normal update function
     * @return void
     */
    public observeRecycleComponentCreation(name: string, recycleUpdateFunc: RecycleUpdateFunc): void {
        stateMgmtConsole.error(`${this.debugInfo__()}: Recycle not supported for ComponentV2 instances`);
    }

    public debugInfoDirtDescendantElementIdsInternal(depth: number = 0, recursive: boolean = false, counter: ProfileRecursionCounter): string {
        let retVaL: string = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
        retVaL += `ViewV2 keeps no info about dirty elmtIds`;
        if (recursive) {
            this.childrenWeakrefMap_.forEach((value, key, map) => {
                retVaL += value.deref()?.debugInfoDirtDescendantElementIdsInternal(depth + 1, recursive, counter);
            });
        }

        if (recursive && depth === 0) {
            retVaL += `\nTotal: ${counter.total}`;
        }
        return retVaL;
    }


    protected debugInfoStateVars(): string {
        return ''; // TODO DFX, read out META
    }

    /**
   * on first render create a new Instance of Repeat
   * on re-render connect to existing instance
   * @param arr
   * @returns
   */
    public __mkRepeatAPI: <I>(arr: Array<I>) => RepeatAPI<I> = <I>(arr: Array<I>): RepeatAPI<I> => {
        // factory is for future extensions, currently always return the same
        const elmtId = ObserveV2.getCurrentRecordedId();
        let repeat = this.elmtId2Repeat_.get(elmtId) as __Repeat<I>;
        if (!repeat) {
            repeat = new __Repeat<I>(this, arr);
            this.elmtId2Repeat_.set(elmtId, repeat);
        } else {
            repeat.updateArr(arr);
        }
        return repeat;
    };
}
