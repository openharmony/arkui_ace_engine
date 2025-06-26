/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * ViewBuildNodeBase is the common base class of PUV2ViewBase and BaseNode
 * The common methods for state management and BuilderNode are implemented in this base class.
 */
abstract class ViewBuildNodeBase {
    protected isView_: boolean;
    protected childrenWeakrefMap_ = new Map<number, WeakRef<IView>>();
    // Tracks all child BuilderNodes of this ViewBuildNodeBase instance using WeakRefs.
    protected builderNodeWeakrefMap_ = new Map<number, WeakRef<ViewBuildNodeBase>>();
    protected updateFuncByElmtId = new UpdateFuncsByElmtId();
    protected id_: number;
    protected shareLocalStorage_: LocalStorage = undefined;

    // Refer to the buildNode parent if it exists.
    // It is undefined, if current node is created in view.
    // It is not undefined, if current node is created in buildNode.
    protected __parentViewBuildNode__: ViewBuildNodeBase = undefined;

    // will find provide for consume only when __enableBuilderNodeConsume__ is true
    // to avoid the affect the performance for builderNode
    protected __enableBuilderNodeConsume__: boolean = false;

    // Map elmtId -> Repeat instance in ViewPU or ViewV2
    protected elmtId2Repeat_: Map<number, RepeatAPI<Object | null | undefined>> =
        new Map<number, RepeatAPI<Object | null | undefined>>();
    protected static arkThemeScopeManager: ArkThemeScopeManager | undefined = undefined;
  
    public abstract ifElseBranchUpdateFunctionDirtyRetaken(): void;
    public abstract forceCompleteRerender(deep: boolean): void;
    public abstract forceRerenderNode(elmtId: number): void;
    public abstract purgeDeleteElmtId(rmElmtId: number): boolean;

    public abstract findProvidePU__(providePropName: string): ObservedPropertyAbstractPU<any> | undefined;

    constructor(isView: boolean) {
        this.isView_ = isView;
        this.childrenWeakrefMap_ = new Map();
        this.builderNodeWeakrefMap_ = new Map();
    }
    // globally unique id, this is different from compilerAssignedUniqueChildId!
    id__(): number {
        return this.id_;
    }
    // overwritten by sub classes
    public debugInfo__(): string {
        return `ViewBuildNodeBase '${this.constructor.name}'[${this.id__()}]`;
    }

    public debugInfoElmtId(elmtId: number, isProfiler: boolean = false): string | ElementType {
        return isProfiler ? {
            elementId: elmtId,
            elementTag: this.updateFuncByElmtId.get(elmtId).getComponentName(),
            isCustomNode: this.childrenWeakrefMap_.has(elmtId)
        } : this.updateFuncByElmtId.debugInfoElmtId(elmtId);
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
    public addChild(child: IView): boolean {
        if (this.childrenWeakrefMap_.has(child.id__())) {
            stateMgmtConsole.warn(`${this.debugInfo__()}: addChild '${child?.debugInfo__()}' elmtId already exists ${child.id__()}. Internal error!`);
            return false;
        }
        this.childrenWeakrefMap_.set(child.id__(), new WeakRef(child));
        
        // if current this is view
        if (this.isView_) {
            child.setParent(this as unknown as IView); // FIXME
        } else {
            child.setParentBuilderNode__(this);
        }
        return true;
    }

    public setParentBuilderNode__(node: ViewBuildNodeBase): void {
        this.__parentViewBuildNode__ = node;
    }
    /**
     * Adds a child BuilderNode to this view
     * Invoke by buildNode when it attach to the view.
     * @param child - The child node to add
     * @returns True if added successfully, false if ID already exists
     */
    public addChildBuilderNode(child: ViewBuildNodeBase): boolean {
        stateMgmtConsole.debug(`BuildNode ${child?.debugInfo__()} is added to the ${this.debugInfo__()}`);
        if (this.builderNodeWeakrefMap_.has(child.id__())) {
            stateMgmtConsole.warn(`${this.debugInfo__()}: addChildBuilderNode '${child?.debugInfo__()}' elmtId already exists ${child.id__()}. Internal error!`);
            return false;
        }
        this.builderNodeWeakrefMap_.set(child.id__(), new WeakRef(child));
        // recursively check children for buildNode and view
        // if it has the default consume needs to reconnect the provide
        if (child.__enableBuilderNodeConsume__) {
            child.propagateToChildrenToConnected();
        }
        return true;
    }

    /**
     * Recursively check all the buildNode and View children
     * if it has the default consume, need to check if it has the new provide can be connected
     * Invoke by buildNode when it attach to the view.
     */
    propagateToChildrenToConnected(): void {
        if (this instanceof ViewPU && this.defaultConsume_.size > 0) {
            this.reconnectToConsume()
        }

        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild?.deref();
            if (child instanceof ViewPU && child.defaultConsume_.size > 0) {
                child.propagateToChildrenToConnected();
            }
        })
        this.builderNodeWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild?.deref();
            if (child instanceof ViewBuildNodeBase && child.__enableBuilderNodeConsume__) {
                child.propagateToChildrenToConnected();
            }
        })
    }
    /**
     * Removes a child BuilderNode from this view by elmtId.
     * Invoke by buildNode when it detaches to the view.
     * @param elmtId - The ID of the child node to remove
     */
    public removeChildBuilderNode(elmtId: number): void {
        stateMgmtConsole.debug(`BuildNode ${elmtId} is removed from the ${this.debugInfo__()}`);
        if (!this.builderNodeWeakrefMap_.has(elmtId)) {
            stateMgmtConsole.warn(`${this.debugInfo__()}: removeChildBuilderNode(${elmtId}) no child with this elmtId. Internal error!`);
            return;
        }

        const buildNode: ViewBuildNodeBase = this.builderNodeWeakrefMap_.get(elmtId)?.deref();
        // recursively check children for buildNode and view
        // if it has the default consume needs to reconnect the provide
        if (buildNode && buildNode.__enableBuilderNodeConsume__) {
            buildNode.propagateToChildrenToDisconnected();
        }
        this.builderNodeWeakrefMap_.delete(elmtId);
    }
    /**
     * Clears a child BuilderNode from this view
     */
    public clearChildBuilderNode(): void {
        this.builderNodeWeakrefMap_.clear();
    }

    /**
     * Recursively check all the buildNode and View children
     * if it has the reconnected consume, 
     * Invoke by buildNode when it attach to the view.
     */
    public propagateToChildrenToDisconnected(): void {
        if (this instanceof ViewPU && this.reconnectConsume_.size > 0) {
            this.disconnectedConsume();
        }
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild?.deref();
            if (child instanceof ViewPU && child.reconnectConsume_.size > 0) {
                child.propagateToChildrenToDisconnected();
            }
        })
        this.builderNodeWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild?.deref();
            if (child instanceof ViewBuildNodeBase && child.__enableBuilderNodeConsume__) {
                child.propagateToChildrenToDisconnected();
            }
        })
    }

    protected purgeDeletedElmtIds(): void {
        stateMgmtConsole.debug(`purgeDeletedElmtIds ViewBuildNodeBase '${this.constructor.name}' (id: ${this.id__()}) start ...`);
        UINodeRegisterProxy.obtainDeletedElmtIds();
        UINodeRegisterProxy.unregisterElmtIdsFromIViews();
        stateMgmtConsole.debug(`purgeDeletedElmtIds ViewBuildNodeBase '${this.constructor.name}' (id: ${this.id__()}) end... `);
    }
    public updateStateVarsOfChildByElmtId(elmtId, params: Object): void {
        stateMgmtProfiler.begin('ViewBuildNodeBase.updateStateVarsOfChildByElmtId');
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
        if (!this.isView_) {
            if ('updateDirtyElements' in child) {
                child.updateDirtyElements();
            }
        }
        stateMgmtConsole.debug(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - end`);
        stateMgmtProfiler.end();
    }
    public createOrGetNode(elmtId: number, builder: () => ArkComponent): object {
        const entry = this.updateFuncByElmtId.get(elmtId);
        if (entry === undefined) {
            stateMgmtConsole.warn(`${this.debugInfo__()} fail to create node, elmtId is illegal`);
            return builder();
        }
        let nodeInfo = entry.getNode();
        if (nodeInfo === undefined) {
            nodeInfo = builder();
            entry.setNode(nodeInfo);
        }
        return nodeInfo;
    }
    // performs the update on a branch within if() { branch } else if (..) { branch } else { branch }
    public ifElseBranchUpdateFunction(branchId: number, branchfunc: () => void): void {
        const oldBranchid: number = If.getBranchId();

        if (branchId === oldBranchid) {
            stateMgmtConsole.debug(`${this.debugInfo__()}: ifElseBranchUpdateFunction: IfElse branch unchanged, no work to do.`);
            return;
        }
        if (this.isView_ || (!this.isView_ && Utils.isApiVersionEQAbove(16))) {
            ViewBuildNodeBase.arkThemeScopeManager?.onIfElseBranchUpdateEnter()
        }
        // branchid identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
        // ifElseNode stores the most recent branch, so we can compare
        // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to if .. else change
        let removedChildElmtIds = new Array<number>();
        let reservedChildElmtIds = new Array<number>();
        If.branchId(branchId, removedChildElmtIds, reservedChildElmtIds);

        for (const reservedChildElmtId of reservedChildElmtIds) {
            this.updateFuncByElmtId.get(reservedChildElmtId)?.setPending(true);
        }

        removedChildElmtIds.forEach((id) => {
            this.elmtId2Repeat_.delete(id);
        });

        //un-registers the removed child elementIDs using proxy
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);

        // purging these elmtIds from state mgmt will make sure no more update function on any deleted child wi;ll be executed
        stateMgmtConsole.debug(`${this.debugInfo__()}: ifElseBranchUpdateFunction: elmtIds need unregister after if/else branch switch: ${JSON.stringify(removedChildElmtIds)}`);
        this.purgeDeletedElmtIds();

        branchfunc();
        this.ifElseBranchUpdateFunctionDirtyRetaken();
        if (this.isView_ || (!this.isView_ && Utils.isApiVersionEQAbove(16))) {
            ViewBuildNodeBase.arkThemeScopeManager?.onIfElseBranchUpdateExit(removedChildElmtIds)
        }
    }
    public static setArkThemeScopeManager(mgr: ArkThemeScopeManager): void {
        ViewBuildNodeBase.arkThemeScopeManager = mgr
    }
    public onWillApplyThemeInternally(): void {
        const theme = ViewBuildNodeBase.arkThemeScopeManager?.getFinalTheme(this);
        if (theme) {
            this.onWillApplyTheme(theme);
        }
    }
    onWillApplyTheme(theme: Theme): void { }
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
    public getShareLocalStorage(): LocalStorage {
        return this.shareLocalStorage_;
    }
    public setShareLocalStorage(localStorage: LocalStorage): void {
        this.shareLocalStorage_ = localStorage;
    }
    /**
     * Propagates the active state to all child nodes in the given weak reference map
     * This generic method can handle child View or child BuilderNode
     *
     * @param weakRefMap - The map containing WeakRefs to children
     * @param active - Whether the child nodes should be activated (true) or frozen (false)
     * @param isReuse - Related to component reuse
     */
    protected propagateToChildren(weakRefMap: Map<number, WeakRef<IView | ViewBuildNodeBase>> | undefined,
        active: boolean, isReuse: boolean): void {
        if (weakRefMap) {
            for (const child of weakRefMap.values()) {
                child.deref()?.setActiveInternal(active, isReuse);
            }
        }
    }
    // overwritten by sub classes
    public setActiveInternal(active: boolean, isReuse = false): void {
        // Propagate state to all child View
        this.propagateToChildren(this.childrenWeakrefMap_, active, isReuse);
        // Propagate state to all child BuilderNode
        this.propagateToChildren(this.builderNodeWeakrefMap_, active, isReuse);
    }
}