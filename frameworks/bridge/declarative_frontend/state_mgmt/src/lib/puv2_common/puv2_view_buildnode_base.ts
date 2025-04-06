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
    protected updateFuncByElmtId = new UpdateFuncsByElmtId();
    protected id_: number;
    protected static arkThemeScopeManager: ArkThemeScopeManager | undefined = undefined;
  
    public abstract ifElseBranchUpdateFunctionDirtyRetaken(): void;
    public abstract forceCompleteRerender(deep: boolean): void;
    public abstract forceRerenderNode(elmtId: number): void;
    public abstract purgeDeleteElmtId(rmElmtId: number): boolean;

    constructor(isView: boolean) {
        this.isView_ = isView;
        this.childrenWeakrefMap_ = new Map();
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
        if (this.isView_) {
            child.setParent(this as unknown as IView); // FIXME
        }
        return true;
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
}