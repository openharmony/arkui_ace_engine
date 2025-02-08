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
 * A decorator function that sets the static `isReusable_` property to `true`
 * on the provided class. This decorator is automatically invoked when the generated component
 * class in the transpiler has the `@ReusableV2` decorator prefix, as below:
 *
 * @ReusableV2
 * class MyComponent { }
 */
function ReusableV2<T extends Constructor>(BaseClass: T): T {
    stateMgmtConsole.debug(`@ReusableV2 ${BaseClass.name}: Redefining isReusable_ as true.`);
    Reflect.defineProperty(BaseClass.prototype, 'isReusable_', {
        get: () => {
          return true;
        }
      });
    return BaseClass;
}

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

    private monitorIdsDelayedUpdate: Set<number> = new Set();
    private computedIdsDelayedUpdate: Set<number> = new Set();

    private recyclePoolV2_: RecyclePoolV2 | undefined = undefined;

    public hasBeenRecycled_: boolean = false;

    public paramsGenerator_?: () => Object;

    constructor(parent: IView, elmtId: number = UINodeRegisterProxy.notRecordingDependencies, extraInfo: ExtraInfo = undefined) {
        super(parent, elmtId, extraInfo);
        this.setIsV2(true);
        PUV2ViewBase.arkThemeScopeManager?.onViewPUCreate(this);
        stateMgmtConsole.debug(`ViewV2 constructor: Creating @Component '${this.constructor.name}' from parent '${parent?.constructor.name}'`);
    }

    onGlobalThemeChanged(): void {
        this.onWillApplyThemeInternally();
        this.forceCompleteRerender(false);
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                child.onGlobalThemeChanged();
            }
        });
    }

    private onWillApplyThemeInternally(): void {
        const theme = PUV2ViewBase.arkThemeScopeManager?.getFinalTheme(this);
        if (theme) {
            this.onWillApplyTheme(theme);
        }
    }

    onWillApplyTheme(theme: Theme): void {}

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

    /**
     * @function recycleSelf
     * @description
     * This callback function is triggered from the native side when the native-side recycle dummy UI node,
     * acting as the parent for the recycled component, is deleted in the ~RecycleDummyNode() destructor.
     * It attempts to add the current JS object to the RecyclePool to ensure proper recycling.
     *
     * If the parent is invalid or being deleted, the component is reset by invoking the native
     * `resetRecycleCustomNode` function, which restores the custom node associated with the JSView object:
     * - If the JSView object has been garbage collected by the engine, the CustomNode is deleted.
     * - If the JSView object is managed by the RecycleManager, the CustomNode is reused.
     *
     * @param {string} reuseId - The ID used for recycling the component.
     */
    public recycleSelf(reuseId: string): void {
        stateMgmtConsole.debug(`${this.debugInfo__()}:  reuseId: ${reuseId}`);

        if (this.getParent() && this.getParent() instanceof ViewV2 && !(this.getParent() as ViewV2).isDeleting_) {
            const parentV2: ViewV2 = this.getParent() as ViewV2;
            parentV2.getOrCreateRecyclePool().pushRecycleV2Component(reuseId, this);
            this.hasBeenRecycled_ = true;
        } else {
            // Native function call to restore the custom node for the JSView object
            // Deletes or reuses the custom node based on GC or RecycleManager
            this.resetRecycleCustomNode();
        }
    }

    // The resetStateVarsOnReuse function defined in the transpiler will be called.
    // If it's not defined, it indicates that an older version of the toolchain is being used,
    // and an error is thrown to notify about the outdated toolchain.
    public resetStateVarsOnReuse(params: Object): void {
        throw new Error('Old toolchain detected. Please upgrade to the latest.');
    }

    // The aboutToReuse function defined in the application will be called if it exists.
    // If not, this empty function will be called, which does nothing.
    aboutToReuse(): void {
        // Empty function
    }

    /**
     * @function aboutToReuseInternal
     * @description This function is triggered from the function reuseOrCreateNewComponent when the component is
     * about to be reused from the recycle Pool.
     * It invokes the `resetStateVarsOnReuse` method (defined in the transpiler) to reinitialize the component's
     * decorated variables either from its parent or local initialization
     * It also invokes the `aboutToReuse` function if defined in the application.
     * Additionally, it recursively traverses  all its subcomponents, calling `resetStateVarsOnReuse`
     * and `aboutToReuse` on each subcomponent to prepare them for reuse.
     * @param {?Object} initialParams - optional, the first reused component use this params to reset value, or it will not record
     * dependency of params.
     */
    aboutToReuseInternal(initialParams?: Object): void {
        stateMgmtConsole.debug(`${this.debugInfo__()}: aboutToReuseInternal`);
        stateMgmtTrace.scopedTrace(() => {
            if (this.paramsGenerator_ && typeof this.paramsGenerator_ === 'function') {
                const params = initialParams ? initialParams : this.paramsGenerator_();
                stateMgmtConsole.debug(`${this.debugInfo__()}: resetStateVarsOnReuse params: ${JSON.stringify(params)}`);
                ObserveV2.getObserve().setCurrentReuseId(this.id__());
                // resets the variables to its initial state
                this.resetStateVarsOnReuse(params);
                // unfreeze the component on reuse
                this.unfreezeReusedComponent();
                this.aboutToReuse();
            }
        }, 'aboutToReuseInternal', this.constructor.name);
        ObserveV2.getObserve().updateDirty2(true, true);
        ObserveV2.getObserve().setCurrentReuseId(ObserveV2.NO_REUSE);
        this.traverseChildDoRecycleOrReuse(PUV2ViewBase.doReuse);
    }

    /**
     * @function aboutToRecycleInternal
     * @description Callback function invoked from the native side function 'CustomNodeBase::SetRecycleFunction'
     * when the component is about to be recycled.
     * It first calls the `aboutToRecycle` function in the application, and performs the necessary actions
     * defined in the application before recycling.
     * Then, it freezes the component to avoid performing UI updates when its in recycle pool
     * Finally recursively traverses all subcomponents, calling `aboutToRecycleInternal` on each subcomponent
     * that is about to be recycled, preparing them for recycling as well.
     */
    aboutToRecycleInternal(): void {

        stateMgmtConsole.debug(`ViewV2 ${this.debugInfo__()} aboutToRecycleInternal`);

        // Calls the application's aboutToRecycle() method if defined
        this.aboutToRecycle();

        // Freeze the component when its in recycle pool
        this.freezeRecycledComponent();

        this.traverseChildDoRecycleOrReuse(PUV2ViewBase.doRecycle);
    }

    // Freezes the component when it is moved to the recycle pool to prevent elementId updates
    private freezeRecycledComponent(): void {
        this.activeCount_--;
        ViewV2.inactiveComponents_.add(`${this.constructor.name}[${this.id__()}]`);
    }

    /**
     * @function unfreezeReusedComponent
     * @description Unfreezes the component when it is removed from the recycle pool for active rendering
     * Only delayed element update is performed here, as monitors and computed
     * are reset by resetStateVarsOnReuse() prior to calling this function
     *
     * @returns void
     */
    private unfreezeReusedComponent(): void {
        this.activeCount_++;
        if (this.elmtIdsDelayedUpdate.size) {
            this.elmtIdsDelayedUpdate.forEach((element) => {
                ObserveV2.getObserve().elmtIdsChanged_.add(element);
            });
        }
        this.elmtIdsDelayedUpdate.clear();
        ViewV2.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
    }

    /**
     * @function getOrCreateRecyclePool
     * @description Retrieves the existing `RecyclePoolV2` instance or creates a new one
     * if it does not exist.
     *
     * @returns {RecyclePoolV2} - The `RecyclePoolV2` instance for managing recycling.
     */
    getOrCreateRecyclePool(): RecyclePoolV2 {
        if (!this.recyclePoolV2_) {
          this.recyclePoolV2_ = new RecyclePoolV2();
        }
        return this.recyclePoolV2_;
      }

    /**
     * @function getRecyclePool
     * @description Retrieves the `RecyclePoolV2` instance if it exists.
     * @returns {RecyclePoolV2} - The existing `RecyclePoolV2` instance for managing recycling.
     */
    getRecyclePool(): RecyclePoolV2 {
        return this.recyclePoolV2_;
    }

    /**
     * @function hasRecyclePool
     * @description Checks if a `RecyclePoolV2` instance exists.
     * The RecyclePoolV2 instance is created when the native side triggers the recycleSelf callback
     * during the recycling of a component.
     * @returns {boolean} - `true` if the `RecyclePoolV2` exists, otherwise `false`.
     */
    hasRecyclePool(): boolean {
        return !(this.recyclePoolV2_ === undefined);
    }

    /**
     * @function cleanupRecycledElmtId
     * @description purges the recycled Element ID in ViewV2
     *
     * @returns void
     */
    private cleanupRecycledElmtId(elmtId: number): void {
        this.updateFuncByElmtId.delete(elmtId);
        UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
        ObserveV2.getObserve().clearBinding(elmtId);
    }

    protected get isViewV2(): boolean {
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

        // Clears all cached components from the Recycle pool and resets the customNode on the native side
        if (this.hasRecyclePool()) {
            this.getRecyclePool().purgeAllCachedRecycleElmtIds();
        }

        // it will unregister removed elementids from all the ViewV2, equals purgeDeletedElmtIdsRecursively
        this.purgeDeletedElmtIds();

        // unregisters its own id once its children are unregistered above
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs([this.id__()]);

        stateMgmtConsole.debug(`${this.debugInfo__()}: onUnRegElementID  - DONE`);

        PUV2ViewBase.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);

        MonitorV2.clearWatchesFromTarget(this);
        ComputedV2.clearComputedFromTarget(this);

        this.updateFuncByElmtId.clear();
        if (this.parent_) {
            this.parent_.removeChild(this);
        }
        PUV2ViewBase.arkThemeScopeManager?.onViewPUDelete(this);
    }

    public initialRenderView(): void {
        stateMgmtProfiler.begin(`ViewV2: initialRenderView`);
        if (this.isReusable_ === true) {
            const isReusableAllowed = this.allowReusableV2Descendant();
            if (!isReusableAllowed) {
                const error = `using @ReusableV2 component inside Repeat.template is not allowed!`;
                stateMgmtConsole.applicationError(error);
                throw new Error(error);
            }
        }
        this.onWillApplyThemeInternally();
        this.initialRender();
        stateMgmtProfiler.end();
    }

    /**
     * @function resetMonitorsOnReuse
     * @description
     * Called from the transpiler's `resetStateVarsOnReuse` method when the component is about to be reused.
     * Ensures that @Monitor functions are reset and reinitialized during the reuse cycle
     */
    public resetMonitorsOnReuse(): void {
        // Clear the monitorIds set for delayed updates, if any
        this.monitorIdsDelayedUpdate.clear();
        ObserveV2.getObserve().resetMonitorValues();
    }

    // Resets the computed value when the reused component variables are reinitialized
    // through the resetStateVarsOnReuse process
    public resetComputed(name: string): void {
        // Clear the computedIds set for delayed updates, if any
        this.computedIdsDelayedUpdate.clear();

        const refs = this[ObserveV2.COMPUTED_REFS];
        refs[name].resetComputed(name);
     }

    // Resets the consumer value when the component is reinitialized on reuse
     public resetConsumer<T>(varName: string, consumerVal: T): void {
        let providerInfo = ProviderConsumerUtilV2.findProvider(this, varName);
        if (!providerInfo) {
          ProviderConsumerUtilV2.defineConsumerWithoutProvider(this, varName, consumerVal);
          ObserveV2.getObserve().fireChange(this, varName);
        }
        stateMgmtConsole.debug(`resetConsumer value: ${consumerVal} for ${varName}`);
     }

    public observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: { prototype: Object, pop?: () => void }): void {
        if (this.isNeedBuildPrebuildCmd() && PUV2ViewBase.prebuildFuncQueues.has(PUV2ViewBase.prebuildingElmtId_)) {
            const prebuildFunc: PrebuildFunc = () => {
              this.observeComponentCreation2(compilerAssignedUpdateFunc, classObject);
            };
            PUV2ViewBase.prebuildFuncQueues.get(PUV2ViewBase.prebuildingElmtId_)?.push(prebuildFunc);
            ViewStackProcessor.PushPrebuildCompCmd();
            return;
        }
        if (this.isDeleting_) {
            stateMgmtConsole.error(`@ComponentV2 ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation2 `);
            return;
        }
        const _componentName: string = (classObject && ('name' in classObject)) ? Reflect.get(classObject, 'name') as string : 'unspecified UINode';
        const _popFunc: () => void = (classObject && 'pop' in classObject) ? classObject.pop! : (): void => { };
        const updateFunc = (elmtId: number, isFirstRender: boolean): void => {
            this.syncInstanceId();
            stateMgmtConsole.debug(`@ComponentV2 ${this.debugInfo__()}: ${isFirstRender ? `First render` : `Re-render/update`} ${_componentName}[${elmtId}] - start ....`);
            PUV2ViewBase.arkThemeScopeManager?.onComponentCreateEnter(_componentName, elmtId, isFirstRender, this);
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
            PUV2ViewBase.arkThemeScopeManager?.onComponentCreateExit(elmtId);
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
     * @Param @Once paramVariableName
     * @Param is read only, therefore, init from parent needs to be done without
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
     * @Param @Once paramVariableName
     * @Param is read only, therefore, update from parent needs to be done without
     *        causing property setter() to be called
     * @Param @Once reject any update
     * @param newValue
     */
    protected updateParam<Z>(paramVariableName: string, newValue: Z): void {
        this.checkIsV1Proxy(paramVariableName, newValue);
        VariableUtilV2.updateParam<Z>(this, paramVariableName, newValue);
    }

    protected resetParam<Z>(paramVariableName: string, newValue: Z): void {
        this.checkIsV1Proxy(paramVariableName, newValue);
        VariableUtilV2.resetParam<Z>(this, paramVariableName, newValue);
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
        if (this.isPrebuilding_) {
            const propertyChangedFunc: PrebuildFunc = () => {
                this.uiNodeNeedUpdateV2(elmtId);
            };
            if (!PUV2ViewBase.propertyChangedFuncQueues.has(this.id__())) {
                PUV2ViewBase.propertyChangedFuncQueues.set(this.id__(), new Array<PrebuildFunc>);
            }
            PUV2ViewBase.propertyChangedFuncQueues.get(this.id__())?.push(propertyChangedFunc);
            return;
        }
        if (this.isFirstRender()) {
            return;
        }

        stateMgmtProfiler.begin(`ViewV2.uiNodeNeedUpdate ${this.debugInfoElmtId(elmtId)}`);

        if (!this.isViewActive()) {
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

            for (const dirtRetakenElementId of this.dirtRetakenElementIds_) {
                this.dirtDescendantElementIds_.add(dirtRetakenElementId);
            }
            this.dirtRetakenElementIds_.clear();
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

    // WatchIds that needs to be fired later gets added to monitorIdsDelayedUpdate
    // monitor fireChange will be triggered for all these watchIds once this view gets active
    public addDelayedMonitorIds(watchId: number): void  {
        stateMgmtConsole.debug(`${this.debugInfo__()} addDelayedMonitorIds called for watchId: ${watchId}`);
        this.monitorIdsDelayedUpdate.add(watchId);
    }

    public addDelayedComputedIds(watchId: number) {
        stateMgmtConsole.debug(`${this.debugInfo__()} addDelayedComputedIds called for watchId: ${watchId}`);
        this.computedIdsDelayedUpdate.add(watchId);
    }
    // If the component has `hasComponentFreezeEnabled` set to true and is marked as @ReusableV2,
    // skip the delayed update, as freeze and delayed updates are handled in `aboutToRecycleInternal`
    // and `aboutToReuseInternal` for @ReusableV2 components.
    public setActiveInternal(active: boolean, isReuse: boolean = false): void {
        stateMgmtProfiler.begin('ViewV2.setActive');
        stateMgmtConsole.debug(`${this.debugInfo__()}: isCompFreezeAllowed : ${this.isCompFreezeAllowed()}`);
        if (this.isCompFreezeAllowed() && !isReuse) {
            stateMgmtConsole.debug(`${this.debugInfo__()}: ViewV2.setActive ${active ? ' inActive -> active' : 'active -> inActive'}`);
            this.setActiveCount(active);
            if (this.isViewActive()) {
                this.performDelayedUpdate();
                ViewV2.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
            } else {
                ViewV2.inactiveComponents_.add(`${this.constructor.name}[${this.id__()}]`);
            }
        }
        for (const child of this.childrenWeakrefMap_.values()) {
            const childView: IView | undefined = child.deref();
            if (childView) {
                childView.setActiveInternal(active, isReuse);
            }
        }
        stateMgmtProfiler.end();
    }

    private performDelayedUpdate(): void {
        stateMgmtProfiler.begin('ViewV2: performDelayedUpdate');
        if(this.computedIdsDelayedUpdate.size) {
            // exec computed functions
            ObserveV2.getObserve().updateDirtyComputedProps([...this.computedIdsDelayedUpdate]);
        }
        if(this.monitorIdsDelayedUpdate.size) {
          // exec monitor functions
          ObserveV2.getObserve().updateDirtyMonitors(this.monitorIdsDelayedUpdate);
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
     * Handles the creation or reuse of a ReusableV2 component
     *
     * This function is invoked from the transpiler for components declared as ReusableV2.
     * It manages the lifecycle of components by either creating a new component or reusing
     * an existing recycle node.
     *
     * During the initial render:
     * - If a recycle node is available, it is reused; otherwise, a new component is created.
     * - A `ViewV2.createRecycle` call is made to the native side to manage recycling.
     * - The callback `aboutToReuseInternal` is triggered when a recycled node is used, indicating
     *   the node was fetched and reused instead of being newly created.
     *
     * On subsequent renders, state variables are updated for the reused component.
     *
     * @param componentClass - The class of the component to be created or reused.
     * @param getParams - A function returning the parameters for the component.
     * @param getReuseId - A function providing a unique reuse ID (default: component class name).
     * @param extraInfo - Additional information required for component creation.
     */
    public reuseOrCreateNewComponent(params: {
        componentClass: any, getParams: () => Object,
        getReuseId?: () => string, extraInfo?: ExtraInfo
    }): void {
        const { componentClass, getParams, getReuseId = (): string => '', extraInfo } = params;
        let reuseId = getReuseId();
        // If reuseId is null or empty (not set by the application), default to the component's name
        if (!reuseId) {
            reuseId = componentClass.name;
        }
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            if (isInitialRender) {
                const params = getParams(); // should call here to record dependency
                const recycledNode = this.hasRecyclePool() ? this.getRecyclePool().popRecycleV2Component(reuseId) : null;
                const componentRef = recycledNode ? recycledNode :
                    new componentClass(/* Parent */this, params, /*localStorage */undefined, elmtId, /*paramsLambda */() => { }, extraInfo);
                if (recycledNode) {
                    // If a recycled node is found, update the recycled element ID mapping in the recycle pool
                    const lastId = this.recyclePoolV2_.getRecycleIdMapping(recycledNode.id__());
                    this.recyclePoolV2_.updateRecycleIdMapping(recycledNode.id__(), elmtId);
                    recycledNode.hasBeenRecycled_ = false;

                    // Removes the recycled elementId after the recycleId mapping is updated.
                    this.cleanupRecycledElmtId(lastId); // clean useless dependency
                }

                // Native call to fetch the cached recycle node or create a new one if it doesn't exist
                ViewV2.createRecycle(componentRef, recycledNode != null, reuseId, () => {
                        // Callback from the native side when the component is reused.
                        recycledNode?.aboutToReuseInternal(params);
                    });

                // Set the component's parameters generator function for later retrieval during reuse
                componentRef.paramsGenerator_ = getParams;
                stateMgmtConsole.debug(`${this.debugInfo__()}: paramsGenerator_:${JSON.stringify(componentRef.paramsGenerator_())}`);
             }
            else {
                // Retrieve the mapped recycled element ID to update the state variables
                const recycledElmtId = this.getOrCreateRecyclePool().getRecycleIdMapping(elmtId);
                this.updateStateVarsOfChildByElmtId(recycledElmtId, getParams());
            }
        }, componentClass);
    }

    public debugInfoDirtDescendantElementIdsInternal(depth: number = 0, recursive: boolean = false, counter: ProfileRecursionCounter): string {
        let retVaL: string = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
        retVaL += `ViewV2 keeps no info about dirty elmtIds}`;
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


    public debugInfoStateVars(): string {
        let retVal: string = `|--${this.constructor.name}[${this.id__()}]\n`;
        let meta = this[ObserveV2.V2_DECO_META];
        if (!meta) {
            retVal += ' No State Variables';
            return retVal;
        }
        Object.getOwnPropertyNames(meta)
            .filter((varName) => !varName.startsWith(ProviderConsumerUtilV2.ALIAS_PREFIX)) // remove provider & consumer prefix
            .forEach((varName) => {
                const prop: any = Reflect.get(meta, varName);
                if ('deco' in prop) {
                    retVal += ` ${prop.deco}`; // main decorator
                }
                if ('deco2' in prop) {
                    retVal += ` ${prop.deco2}`; // sub decorator like @Once
                }
                if ('aliasName' in prop) {
                    retVal += `(${prop.aliasName})`; // aliasName for provider & consumer
                }
                retVal += ` varName: ${varName}`;
                let dependentElmtIds = this[ObserveV2.SYMBOL_REFS][varName];
                if (dependentElmtIds) {
                    retVal += `\n  |--DependentElements:`;
                    dependentElmtIds.forEach((elmtId) => {
                        if (elmtId < ComputedV2.MIN_COMPUTED_ID) {
                            retVal += ` ` + ObserveV2.getObserve().getElementInfoById(elmtId);
                        } else if (elmtId < MonitorV2.MIN_WATCH_ID) {
                            retVal += ` @Computed[${elmtId}]`;
                        } else if (elmtId < PersistenceV2Impl.MIN_PERSISTENCE_ID) {
                            retVal += ` @Monitor[${elmtId}]`;
                        } else {
                            retVal += ` PersistenceV2[${elmtId}]`;
                        }
                    });
                }
                retVal += '\n';

            });
        return retVal;
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

    public debugInfoView(recursive: boolean = false): string {
        return this.debugInfoViewInternal(recursive);
    }

    private debugInfoViewInternal(recursive: boolean = false): string {
        let retVal: string = `@ComponentV2\n${this.constructor.name}[${this.id__()}]`;
        retVal += `\n\nView Hierarchy:\n${this.debugInfoViewHierarchy(recursive)}`;
        retVal += `\n\nState variables:\n${this.debugInfoStateVars()}`;
        retVal += `\n\nRegistered Element IDs:\n${this.debugInfoUpdateFuncByElmtId(recursive)}`;
        retVal += `\n\nDirty Registered Element IDs:\n${this.debugInfoDirtDescendantElementIds(recursive)}`;
        return retVal;
    }

    public debugInfoDirtDescendantElementIds(recursive: boolean = false): string {
        return this.debugInfoDirtDescendantElementIdsInternal(0, recursive, { total: 0 });
    }

    public observeRecycleComponentCreation(name: string, recycleUpdateFunc: RecycleUpdateFunc): void {
        // cannot use ReusableV1 in V2, but for compatibility, do not throw error..
        // transpiler will try to give a warning to hint that it will downgrade to normal V1
        stateMgmtConsole.error(`${this.debugInfo__()}: Recycle not supported for ComponentV2 instance`);
    }
}
