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

    constructor(parent: IView, elmtId: number = UINodeRegisterProxy.notRecordingDependencies, extraInfo: ExtraInfo = undefined) {
        super(parent, elmtId, extraInfo);
        stateMgmtConsole.debug(`ViewPU constructor: Creating @Component '${this.constructor.name}' from parent '${parent?.constructor.name}'`);
    }

    protected finalizeConstruction(): void {

        ProvideConsumeUtilV3.setupConsumeVarsV3(this);
        ObserveV2.getObserve().constructMonitor(this, this.constructor.name);
        ObserveV2.getObserve().constructComputed(this, this.constructor.name);

        // Always use ID_REFS in ViewPU
        this[ObserveV2.ID_REFS] = {};
    }

    public debugInfo__(): string {
        return `@ComponentV2 '${this.constructor.name}'[${this.id__()}]`;
    }


    private get isViewV3(): boolean {
        return true;
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
        // this ViewPU should be treated as already unregistered

        stateMgmtConsole.debug(`${this.constructor.name}: aboutToBeDeletedInternal `);

        // purge the elmtIds owned by this viewPU from the updateFuncByElmtId and also the state variable dependent elmtIds
        Array.from(this.updateFuncByElmtId.keys()).forEach((elmtId: number) => {
            // FIXME split View: enable delete  this purgeDeleteElmtId(elmtId);
        });

        /*if this hasRecycleManager() {
           this getRecycleManager() purgeAllCachedRecycleNode();
        }*/

        // unregistration of ElementIDs
        stateMgmtConsole.debug(`${this.debugInfo__()}: onUnRegElementID`);

        // it will unregister removed elementids from all the viewpu, equals purgeDeletedElmtIdsRecursively
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
            ObserveV2.getObserve().startBind(this, elmtId);

            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            if (!isFirstRender) {
                _popFunc();
            }

            let node = this.getNodeById(elmtId);
            if (node !== undefined) {
                (node as ArkComponent).cleanStageValue();
            }

            ObserveV2.getObserve().startBind(null, UINodeRegisterProxy.notRecordingDependencies);
            ViewStackProcessor.StopGetAccessRecording();

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

    /**
   *
   * @param paramVariableName
   * @param @once paramVariableName
   * @param is read only, therefore, init from parent needs to be done without
   *        causing property setter() to be called
   * @param newValue
   */
    protected initParam<Z>(paramVariableName: string, newValue: Z): void {
        VariableUtilV3.initParam<Z>(this, paramVariableName, newValue);
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
        VariableUtilV3.updateParam<Z>(this, paramVariableName, newValue);
    }

    /**
   *  inform that UINode with given elmtId needs rerender
   *  does NOT exec @Watch function.
   *  only used on V3 code path from ObserveV2.fireChange.
   *
   * FIXME will still use in the future?
   */
    public uiNodeNeedUpdateV3(elmtId: number): void {
        if (this.isFirstRender()) {
            return;
        }

        stateMgmtProfiler.begin(`ViewV2.uiNodeNeedUpdate ${this.debugInfoElmtId(elmtId)}`);

        if (!this.dirtDescendantElementIds_.size) { //  && !this runReuse_) {
            // mark ComposedElement dirty when first elmtIds are added
            // do not need to do this every time
            this.syncInstanceId();
            this.markNeedUpdate();
            this.restoreInstanceId();
        }
        /*  if (this hasRecycleManager()) {
              this dirtDescendantElementIds_ add(this.recycleManager_.proxyNodeId(elmtId));
            } else {
        */
        this.dirtDescendantElementIds_.add(elmtId);
        /*
            }
        */
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
                /*if (this hasRecycleManager()) {
                   this UpdateElement (this recycleManager_ proxyNodeId(elmtId));
                 } else {
                    */
                this.UpdateElement(elmtId);
                /*
                 }
                */
                this.dirtDescendantElementIds_.delete(elmtId);
            });

            if (this.dirtDescendantElementIds_.size) {
                stateMgmtConsole.applicationError(`${this.debugInfo__()}: New UINode objects added to update queue while re-render! - Likely caused by @Component state change during build phase, not allowed. Application error!`);
            }
        } while (this.dirtDescendantElementIds_.size);
        stateMgmtConsole.debug(`${this.debugInfo__()}: updateDirtyElements (re-render) - DONE, dump of ViewPU in next lines`);
        stateMgmtProfiler.end();
    }


    public UpdateElement(elmtId: number): void {
        stateMgmtProfiler.begin('ViewPU.UpdateElement');
        if (elmtId === this.id__()) {
            // do not attempt to update itself.
            // a @Prop can add a dependency of the ViewPU onto itself. Ignore it.
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
            updateFunc(elmtId, /* isFirstRender */ false);
            stateMgmtProfiler.end();
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

    public setActiveInternal(newState: boolean): void {
        stateMgmtConsole.error('ViewV2: setActiveInternal is unimplemented');
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
        const elmtId = this.getCurrentlyRenderedElmtId();
        let repeat = this.elmtId2Repeat_.get(elmtId) as __RepeatV2<I>
        if (!repeat) {
            repeat = new __RepeatV2<I>(arr);
            this.elmtId2Repeat_.set(elmtId, repeat);
        } else {
            repeat.updateArr(arr)
        }
        return repeat;
    }
}
