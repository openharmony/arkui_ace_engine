/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner';

declare interface IView {
    id__(): number;
    debugInfo__?(): string;
    setParent?(parent: IView): void;
    setParentBuilderNode__?(node: ViewBuildNodeBase): void;
    setActiveInternal?(active: boolean, isReuse: boolean): void;
    onGlobalThemeChanged?(): void;
}

declare class ViewBuildNodeBase {
     static setArkThemeScopeManager(mgr: ArkThemeScopeManager): void;
     constructor(isView: boolean);
     __parentViewBuildNode__: ViewBuildNodeBase;
     id__(): number;
     debugInfo__(): string;
     getChildById(id: number): IView | undefined;
     addChild(child: IView): boolean;
     setParentBuilderNode__(node: ViewBuildNodeBase): void;
     get builderNodeWeakrefMap_(): Map<number, WeakRef<ViewBuildNodeBase>> | undefined;
     getOrCreateBuilderNodeWeakrefMap(): Map<number, WeakRef<ViewBuildNodeBase>>;
     addChildBuilderNode(child: ViewBuildNodeBase): boolean;
     removeChildBuilderNode(removedChildElmtId: number): void;
     clearChildBuilderNode(): void;
     propagateToChildrenToConnected(): void;
     propagateToChildrenToDisconnected(): void;
     getElementNameById(elmtId: number): string;
     debugInfoElmtId(elmtId: number, isProfiler?: boolean): string | ElementType;
     updateStateVarsOfChildByElmtId(elmtId: number, params: Object): void;
     createOrGetNode(elmtId: number, builder: () => ArkComponent): object;
     ifElseBranchUpdateFunction(branchId: number, branchfunc: () => void): void;
     onWillApplyThemeInternally(): void;
     onGlobalThemeChanged(): void;
     getShareLocalStorage(): LocalStorage;
     setShareLocalStorage(localStorage: LocalStorage): void;
     setActiveInternal(active: boolean, isReuse?: boolean): void;
}

declare class UpdateFuncsByElmtId {
     delete(elmtId: number): boolean;
     set(elmtId: number, params: any): void;
     get(elmtId: number): UpdateFuncRecord | undefined;
     has(elmtId: number): boolean;
     keys(): IterableIterator<number>;
     clear(): void;
     readonly size: number;
     forEach(callbackfn: (value: UpdateFuncRecord, key: number, map: Map<number, UpdateFuncRecord>) => void): void;
     debugInfoRegisteredElmtIds(): string;
     debugInfoElmtId(elmtId: number): string;
}

declare class UpdateFuncRecord {
     getComponentName(): string;
     getUpdateFunc(): Function | undefined;
     getNode(): ArkComponent | undefined;
     setNode(node: ArkComponent): void;
     isPending(): boolean;
     setPending(pending: boolean): void;
     setIsChanged(changed: boolean): void;
     isChanged(): boolean;
}

declare class If {
    static getBranchId(): number;
    static branchId(branchId: number, removedChildElmtIds: number[], reservedChildElmtIds: number[]): void;
    static getRetakenElmtIds(retakenElmtIds: number[]): boolean;
}

declare class ForEach {
    static setIdArray(elmtId: number, newIdArray: string[], diffIndexArray: number[], idDuplicates: number[], removedChildElmtIds: number[]): void;
}

declare class UINodeRegisterProxy {
     static obtainDeletedElmtIds(): void;
     static unregisterElmtIdsFromIViews(): void;
     static unregisterRemovedElmtsFromViewPUs(removedChildElmtIds: number[]): void;
}

declare class ArkComponent {
}

declare class ArkThemeScopeManager {
    onIfElseBranchUpdateEnter(): void;
    onIfElseBranchUpdateExit(removedChildElmtIds: number[]): void;
    getFinalTheme(view: ViewBuildNodeBase): Theme | undefined;
}

declare class Theme {
}

declare class LocalStorage {
}

declare class ElementType {
    elementId: number;
    elementTag: string;
    isCustomNode: boolean;
}

declare class ViewPU extends ViewBuildNodeBase {
}

declare class ViewV2 extends ViewBuildNodeBase {
}

declare class ObservedPropertyAbstractPU<T> {
}

class MockView implements IView {
     public id: number;
     public parentView: IView | undefined = undefined;
     public parentBuilderNode: ViewBuildNodeBase | undefined = undefined;
     public activeInternalCalls: Array<{ active: boolean, isReuse: boolean }> = [];
     public globalThemeChangedCount: number = 0;

    constructor(id: number) {
        this.id = id;
    }

    id__(): number {
        return this.id;
    }

     debugInfo__(): string {
         return `MockView[${this.id}]`;
     }

     setParent?(parent: IView): void {
         this.parentView = parent;
     }

     setParentBuilderNode__?(node: ViewBuildNodeBase): void {
         this.parentBuilderNode = node;
     }

     setActiveInternal?(active: boolean, isReuse: boolean): void {
         this.activeInternalCalls.push({ active, isReuse });
     }

     onGlobalThemeChanged?(): void {
         this.globalThemeChangedCount++;
     }
}

class MockViewBuildNodeBase extends ViewBuildNodeBase {
     private static nextId_: number = 1;
     protected id_: number;
     public forceCompleteRerenderCalls: Array<boolean> = [];
     public dirtyRetakenCalls: number = 0;
     public appliedThemes: Array<Theme> = [];

     constructor(isView: boolean = true, id?: number) {
         super(isView);
         this.id_ = (id !== undefined) ? id : MockViewBuildNodeBase.nextId_++;
     }

     public ifElseBranchUpdateFunctionDirtyRetaken(): void {
         this.dirtyRetakenCalls++;
     }

     public forceCompleteRerender(deep: boolean): void {
         this.forceCompleteRerenderCalls.push(deep);
     }

    public forceRerenderNode(elmtId: number): void {
    }

    public purgeDeleteElmtId(rmElmtId: number): boolean {
        return true;
    }

    public findProvidePU__(providePropName: string): ObservedPropertyAbstractPU<any> | undefined {
        return undefined;
    }

    public UpdateElement(elmtId: number): void {
    }

     public getInstanceId(): number {
         return this.id__();
     }

     public onWillApplyTheme(theme: Theme): void {
         this.appliedThemes.push(theme);
     }
}

class SpyBuilderNode extends MockViewBuildNodeBase {
     public connectedCalls: number = 0;
     public disconnectedCalls: number = 0;
     public activeInternalCalls: Array<{ active: boolean, isReuse: boolean }> = [];

     public propagateToChildrenToConnected(): void {
         this.connectedCalls++;
     }

     public propagateToChildrenToDisconnected(): void {
         this.disconnectedCalls++;
     }

     public setActiveInternal(active: boolean, isReuse: boolean = false): void {
         this.activeInternalCalls.push({ active, isReuse });
     }
}

/**
 * Comprehensive ViewBuildNodeBase Unit Tests
 *
 * This test suite validates the common base class for PUV2ViewBase and BaseNode.
 *
 * Test Sections:
 * 1. Constructor and Initialization
 * 2. ID and Debug Information
 * 3. Child Management
 * 4. BuilderNode Management
 * 5. Lifecycle Propagation
 * 6. State Update
 * 7. If/Else Branch Update
 * 8. Theme Management
 * 9. LocalStorage Management
 * 10. Active State Management
 * 11. Edge Cases and Stress Tests
 */
export class Puv2ViewBuildNodeBaseTestsV2 implements ITestFile {
    private idString: string = "";

    constructor(str: string) {
        console.log(`Creating Puv2ViewBuildNodeBaseTestsV2: ${str}`)
        this.idString = str;
    }

    public beforeAll(): void {
        console.log("Puv2ViewBuildNodeBaseTestsV2: Setting up test suite");
    }

    public beforeEach(): void {
    }

    public afterAll(): void {
        console.log("Puv2ViewBuildNodeBaseTestsV2: Tearing down test suite");
    }

    public afterEach(): void {
    }

    public getId(): string {
        return this.idString;
    }

    // =========================================================================
    // SECTION 1: Constructor and Initialization
    // =========================================================================

    /**
     * Test multiple instances
     * Expected: Multiple instances can be created independently
     */
    public testMultipleInstances(): void {
        const instance1 = new MockViewBuildNodeBase(true);
        const instance2 = new MockViewBuildNodeBase(false);
        const instance3 = new MockViewBuildNodeBase(true);

        eq(instance1 !== instance2, true, "instances should be different");
        eq(instance2 !== instance3, true, "instances should be different");
        eq(instance1 !== instance3, true, "instances should be different");
    }

    // =========================================================================
    // SECTION 2: ID and Debug Information
    // =========================================================================

    /**
     * Test debugInfo__() returns string
     * Expected: debugInfo__() returns debug information string
     */
    public testDebugInfoReturnsString(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const debugInfo = viewBuildNode.debugInfo__();

        eq(typeof debugInfo, "string", "debugInfo should be a string");
        eq(debugInfo.length > 0, true, "debugInfo should not be empty");
    }

    /**
     * Test debugInfo contains class name
     * Expected: debugInfo includes class name
     */
    public testDebugInfoContainsClassName(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const debugInfo = viewBuildNode.debugInfo__();

        eq(debugInfo.includes("MockViewBuildNodeBase"), true, "debugInfo should contain class name");
    }

    // =========================================================================
    // SECTION 3: Child Management
    // =========================================================================

    /**
     * Test addChild with valid child
     * Expected: Child is added successfully
     */
    public testAddChildValid(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockView(1);

        const result = parent.addChild(child);

        eq(result, true, "addChild should return true for valid child");
        eq(child.parentView === (parent as any), true, "child.setParent should be called for View");
        eq(parent.getChildById(1) === child, true, "child should be retrievable by id");
    }

    /**
     * Test addChild sets parent builder node
     * Expected: For BuilderNode parent, setParentBuilderNode__ is used
     */
    public testAddChildSetsParentBuilderNodeWhenNotView(): void {
        const parent = new MockViewBuildNodeBase(false);
        const child = new MockView(1);

        const result = parent.addChild(child);

        eq(result, true, "addChild should return true for valid child");
        eq(child.parentBuilderNode === (parent as any), true, "child.setParentBuilderNode__ should be called for BuilderNode");
        eq(child.parentView, undefined, "child.setParent should not be called for BuilderNode");
        eq(parent.getChildById(1) === child, true, "child should be retrievable by id");
    }

    /**
     * Test addChild with duplicate child
     * Expected: Duplicate child is not added
     */
    public testAddChildDuplicate(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockView(1);

        const result1 = parent.addChild(child);
        const result2 = parent.addChild(child);

        eq(result1, true, "first addChild should return true");
        eq(result2, false, "duplicate addChild should return false");
    }

    /**
     * Test getChildById with existing child
     * Expected: Child is retrieved correctly
     */
    public testGetChildByIdExisting(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockView(1);

        parent.addChild(child);
        const retrievedChild = parent.getChildById(1);

        eq(retrievedChild !== undefined, true, "child should be retrieved");
        eq(retrievedChild?.id__(), 1, "retrieved child should have correct ID");
    }

    /**
     * Test getChildById with non-existing child
     * Expected: undefined is returned
     */
    public testGetChildByIdNonExisting(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockView(1);

        parent.addChild(child);
        const retrievedChild = parent.getChildById(999);

        eq(retrievedChild, undefined, "non-existing child should return undefined");
    }

    /**
     * Test add multiple children
     * Expected: Multiple children can be added
     */
    public testAddMultipleChildren(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child1 = new MockView(1);
        const child2 = new MockView(2);
        const child3 = new MockView(3);

        const result1 = parent.addChild(child1);
        const result2 = parent.addChild(child2);
        const result3 = parent.addChild(child3);

        eq(result1, true, "child1 should be added");
        eq(result2, true, "child2 should be added");
        eq(result3, true, "child3 should be added");

        eq(parent.getChildById(1)?.id__(), 1, "child1 should be retrievable");
        eq(parent.getChildById(2)?.id__(), 2, "child2 should be retrievable");
        eq(parent.getChildById(3)?.id__(), 3, "child3 should be retrievable");
    }

    /**
     * Test setParentBuilderNode__
     * Expected: Parent builder node is set
     */
    public testSetParentBuilderNode(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockViewBuildNodeBase(false);

        child.setParentBuilderNode__(parent);

        eq(child.__parentViewBuildNode__ === parent, true, "parent builder node should be set");
    }

    // =========================================================================
    // SECTION 4: BuilderNode Management
    // =========================================================================

    /**
     * Test getOrCreateBuilderNodeWeakrefMap creates map
     * Expected: Map is created and returned
     */
    public testGetOrCreateBuilderNodeWeakrefMapCreates(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);

        eq(viewBuildNode.builderNodeWeakrefMap_, undefined, "builderNodeWeakrefMap_ should be undefined before create");
        const map = viewBuildNode.getOrCreateBuilderNodeWeakrefMap();

        eq(map !== undefined, true, "map should be created");
        eq(map instanceof Map, true, "map should be a Map instance");
        eq(viewBuildNode.builderNodeWeakrefMap_ === map, true, "builderNodeWeakrefMap_ should return created map");
    }

    /**
     * Test getOrCreateBuilderNodeWeakrefMap returns same map
     * Expected: Same map instance is returned on multiple calls
     */
    public testGetOrCreateBuilderNodeWeakrefMapReturnsSame(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const map1 = viewBuildNode.getOrCreateBuilderNodeWeakrefMap();
        const map2 = viewBuildNode.getOrCreateBuilderNodeWeakrefMap();

        eq(map1 === map2, true, "same map instance should be returned");
    }

    /**
     * Test addChildBuilderNode with valid child
     * Expected: BuilderNode child is added successfully
     */
    public testAddChildBuilderNodeValid(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockViewBuildNodeBase(false);

        const result = parent.addChildBuilderNode(child);

        eq(result, true, "addChildBuilderNode should return true");
        const weakRef = parent.getOrCreateBuilderNodeWeakrefMap().get(child.id__());
        eq(weakRef?.deref() === child, true, "child builder node should be stored as WeakRef");
    }

    /**
     * Test addChildBuilderNode triggers consume reconnect propagation
     * Expected: When __enableBuilderNodeConsume__ is true, propagateToChildrenToConnected is called
     */
    public testAddChildBuilderNodeConsumeTriggersPropagateConnected(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new SpyBuilderNode(false);
        (child as any).__enableBuilderNodeConsume__ = true;

        const result = parent.addChildBuilderNode(child);

        eq(result, true, "addChildBuilderNode should return true");
        eq(child.connectedCalls, 1, "propagateToChildrenToConnected should be called once on add");
    }

    /**
     * Test addChildBuilderNode with duplicate child
     * Expected: Duplicate child is not added
     */
    public testAddChildBuilderNodeDuplicate(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockViewBuildNodeBase(false);

        const result1 = parent.addChildBuilderNode(child);
        const result2 = parent.addChildBuilderNode(child);

        eq(result1, true, "first addChildBuilderNode should return true");
        eq(result2, false, "duplicate addChildBuilderNode should return false");
    }

    /**
     * Test removeChildBuilderNode with existing child
     * Expected: Child is removed successfully
     */
    public testRemoveChildBuilderNodeExisting(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new SpyBuilderNode(false);

        parent.addChildBuilderNode(child);
        (child as any).__enableBuilderNodeConsume__ = true;
        parent.removeChildBuilderNode(child.id__());

        eq(parent.getOrCreateBuilderNodeWeakrefMap().has(child.id__()), false, "child builder node should be removed");
        eq(child.disconnectedCalls, 1, "propagateToChildrenToDisconnected should be called on remove");
    }

    /**
     * Test removeChildBuilderNode with non-existing child
     * Expected: Remove operation completes without error
     */
    public testRemoveChildBuilderNodeNonExisting(): void {
        const parent = new MockViewBuildNodeBase(true);

        parent.removeChildBuilderNode(999);

        eq(parent !== undefined, true, "parent should still exist");
    }

    /**
     * Test clearChildBuilderNode
     * Expected: All builder nodes are cleared
     */
    public testClearChildBuilderNode(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child1 = new MockViewBuildNodeBase(false);
        const child2 = new MockViewBuildNodeBase(false);

        parent.addChildBuilderNode(child1);
        parent.addChildBuilderNode(child2);
        parent.clearChildBuilderNode();

        eq(parent.getOrCreateBuilderNodeWeakrefMap().size, 0, "builder node map should be empty after clear");
    }

    // =========================================================================
    // SECTION 5: Lifecycle Propagation
    // =========================================================================

    /**
     * Test propagateToChildrenToConnected can be called
     * Expected: Method completes without error
     */
    public testPropagateToChildrenToConnected(): void {
        const parent = new MockViewBuildNodeBase(true);
        const childConsumeEnabled = new SpyBuilderNode(false);
        const childConsumeDisabled = new SpyBuilderNode(false);

        parent.addChildBuilderNode(childConsumeEnabled);
        parent.addChildBuilderNode(childConsumeDisabled);

        (childConsumeEnabled as any).__enableBuilderNodeConsume__ = true;
        (childConsumeDisabled as any).__enableBuilderNodeConsume__ = false;

        parent.propagateToChildrenToConnected();

        eq(childConsumeEnabled.connectedCalls, 1, "consume-enabled child should be propagated");
        eq(childConsumeDisabled.connectedCalls, 0, "consume-disabled child should not be propagated");
    }

    /**
     * Test propagateToChildrenToDisconnected can be called
     * Expected: Method completes without error
     */
    public testPropagateToChildrenToDisconnected(): void {
        const parent = new MockViewBuildNodeBase(true);
        const childConsumeEnabled = new SpyBuilderNode(false);
        const childConsumeDisabled = new SpyBuilderNode(false);

        parent.addChildBuilderNode(childConsumeEnabled);
        parent.addChildBuilderNode(childConsumeDisabled);

        (childConsumeEnabled as any).__enableBuilderNodeConsume__ = true;
        (childConsumeDisabled as any).__enableBuilderNodeConsume__ = false;

        parent.propagateToChildrenToDisconnected();

        eq(childConsumeEnabled.disconnectedCalls, 1, "consume-enabled child should be propagated");
        eq(childConsumeDisabled.disconnectedCalls, 0, "consume-disabled child should not be propagated");
    }

    // =========================================================================
    // SECTION 6: State Update
    // =========================================================================

    /**
     * Test updateStateVarsOfChildByElmtId with valid elmtId
     * Expected: Update completes without error
     */
    public testUpdateStateVarsOfChildByElmtIdValid(): void {
        eq(typeof ViewPU !== 'undefined', true, "ViewPU should be defined");

        const parent = new MockViewBuildNodeBase(false);
        const elmtId = 1;
        const params = { param1: "value1" };
        let updateStateVarsCalled = 0;
        let updateDirtyElementsCalled = 0;

        const child: any = Object.create((ViewPU as any).prototype);
        child.id__ = () => elmtId;
        child.debugInfo__ = () => `FakeViewPU[${elmtId}]`;
        child.setParent = (_parent: IView) => { };
        child.setParentBuilderNode__ = (_node: ViewBuildNodeBase) => { };
        child.updateStateVars = (p: Object) => {
            updateStateVarsCalled++;
            child.lastParams = p;
        };
        child.updateDirtyElements = () => { updateDirtyElementsCalled++; };

        parent.addChild(child as IView);
        parent.updateStateVarsOfChildByElmtId(elmtId, params);

        eq(updateStateVarsCalled, 1, "updateStateVars should be called for ViewPU child");
        eq(child.lastParams === params, true, "updateStateVars should receive the original params object");
        eq(updateDirtyElementsCalled, 1, "updateDirtyElements should be called for BuilderNode parent");
    }

    /**
     * Test updateStateVarsOfChildByElmtId with invalid elmtId
     * Expected: Update completes without error
     */
    public testUpdateStateVarsOfChildByElmtIdInvalid(): void {
        eq(typeof ViewPU !== 'undefined', true, "ViewPU should be defined");

        const parent = new MockViewBuildNodeBase(false);
        const params = { param1: "value1" };
        let updateStateVarsCalled = 0;
        let updateDirtyElementsCalled = 0;

        const child: any = Object.create((ViewPU as any).prototype);
        child.id__ = () => 1;
        child.setParent = (_parent: IView) => { };
        child.setParentBuilderNode__ = (_node: ViewBuildNodeBase) => { };
        child.updateStateVars = (_p: Object) => { updateStateVarsCalled++; };
        child.updateDirtyElements = () => { updateDirtyElementsCalled++; };

        parent.addChild(child as IView);
        parent.updateStateVarsOfChildByElmtId(-1, params);

        eq(updateStateVarsCalled, 0, "invalid elmtId should not call updateStateVars");
        eq(updateDirtyElementsCalled, 0, "invalid elmtId should not call updateDirtyElements");
    }

    /**
     * Test updateStateVarsOfChildByElmtId with View parent
     * Expected: View parent does not call updateDirtyElements
     */
    public testUpdateStateVarsOfChildByElmtIdViewDoesNotCallUpdateDirtyElements(): void {
        eq(typeof ViewPU !== 'undefined', true, "ViewPU should be defined");

        const parent = new MockViewBuildNodeBase(true);
        const elmtId = 1;
        const params = { param1: "value1" };
        let updateStateVarsCalled = 0;
        let updateDirtyElementsCalled = 0;

        const child: any = Object.create((ViewPU as any).prototype);
        child.id__ = () => elmtId;
        child.setParent = (_parent: IView) => { };
        child.setParentBuilderNode__ = (_node: ViewBuildNodeBase) => { };
        child.updateStateVars = (_p: Object) => { updateStateVarsCalled++; };
        child.updateDirtyElements = () => { updateDirtyElementsCalled++; };

        parent.addChild(child as IView);
        parent.updateStateVarsOfChildByElmtId(elmtId, params);

        eq(updateStateVarsCalled, 1, "updateStateVars should be called for ViewPU child");
        eq(updateDirtyElementsCalled, 0, "View parent should not call updateDirtyElements");
    }

    /**
     * Test updateStateVarsOfChildByElmtId with non-ViewPU/V2 child
     * Expected: Child is ignored and no update functions are called
     */
    public testUpdateStateVarsOfChildByElmtIdNonViewPUChild(): void {
        const parent = new MockViewBuildNodeBase(false);
        const elmtId = 1;
        let updateStateVarsCalled = 0;
        let updateDirtyElementsCalled = 0;

        const child: any = new MockView(elmtId);
        child.updateStateVars = (_p: Object) => { updateStateVarsCalled++; };
        child.updateDirtyElements = () => { updateDirtyElementsCalled++; };

        parent.addChild(child as IView);
        parent.updateStateVarsOfChildByElmtId(elmtId, { a: 1 });

        eq(updateStateVarsCalled, 0, "non-ViewPU/V2 child should not be updated");
        eq(updateDirtyElementsCalled, 0, "non-ViewPU/V2 child should not trigger dirty update");
    }

    /**
     * Test updateStateVarsOfChildByElmtId with non-existing child
     * Expected: Update completes without error
     */
    public testUpdateStateVarsOfChildByElmtIdNonExisting(): void {
        const parent = new MockViewBuildNodeBase(true);

        parent.updateStateVarsOfChildByElmtId(999, { param1: "value1" });

        eq(parent !== undefined, true, "parent should exist after non-existing child update");
    }

    /**
     * Test createOrGetNode creates new node
     * Expected: New node is created
     */
    public testCreateOrGetNodeCreatesNew(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const elmtId = 1;
        (viewBuildNode as any).updateFuncByElmtId.set(elmtId, { updateFunc: () => { }, classObject: class TestComp { } });

        let builderCalls = 0;
        const builder = () => {
            builderCalls++;
            return { call: builderCalls };
        };

        const node1 = viewBuildNode.createOrGetNode(elmtId, builder);
        const node2 = viewBuildNode.createOrGetNode(elmtId, builder);

        eq(node1 !== undefined, true, "node1 should be created");
        eq(node1 === node2, true, "node should be cached when UpdateFuncRecord exists");
        eq(builderCalls, 1, "builder should be called only once when caching works");
    }

    /**
     * Test createOrGetNode returns existing node
     * Expected: Existing node is returned
     */
    public testCreateOrGetNodeReturnsExisting(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const illegalElmtId = 999;
        let builderCalls = 0;
        const builder = () => {
            builderCalls++;
            return { call: builderCalls };
        };

        const node1 = viewBuildNode.createOrGetNode(illegalElmtId, builder);
        const node2 = viewBuildNode.createOrGetNode(illegalElmtId, builder);

        eq(builderCalls, 2, "builder should be called for each illegal elmtId call");
        eq(node1 === node2, false, "illegal elmtId should not cache the node");
    }

    // =========================================================================
    // SECTION 7: If/Else Branch Update
    // =========================================================================

    /**
     * Test ifElseBranchUpdateFunction can be called
     * Expected: Branch update completes without error
     */
    public testIfElseBranchUpdateFunction(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const oldBranchId: number = If.getBranchId();
        let branchFuncCalled = 0;

        viewBuildNode.ifElseBranchUpdateFunction(oldBranchId, () => { branchFuncCalled++; });

        eq(branchFuncCalled, 0, "branchfunc should not be called when branchId is unchanged");
    }

    /**
     * Test ifElseBranchUpdateFunction with multiple calls
     * Expected: Multiple branch updates work correctly
     */
    public testIfElseBranchUpdateFunctionMultiple(): void {
        eq(typeof UINodeRegisterProxy !== 'undefined', true, "UINodeRegisterProxy should be defined");

        const viewBuildNode = new MockViewBuildNodeBase(true);
        const removedId = 11;
        const reservedId = 22;

        (viewBuildNode as any).updateFuncByElmtId.set(reservedId, { updateFunc: () => { }, classObject: class ReservedComp { } });
        (viewBuildNode as any).elmtId2Repeat_.set(removedId, {} as any);

        const prevThemeMgr = (ViewBuildNodeBase as any).arkThemeScopeManager;

        const prevIfGetBranchId = (If as any).getBranchId;
        const prevIfBranchId = (If as any).branchId;

        const prevUnregisterRemoved = (UINodeRegisterProxy as any).unregisterRemovedElmtsFromViewPUs;
        const prevObtainDeleted = (UINodeRegisterProxy as any).obtainDeletedElmtIds;
        const prevUnregisterIViews = (UINodeRegisterProxy as any).unregisterElmtIdsFromIViews;

        const themeMgr: any = {
            enterCount: 0,
            exitCount: 0,
            lastRemoved: undefined as number[] | undefined,
            onIfElseBranchUpdateEnter() { this.enterCount++; },
            onIfElseBranchUpdateExit(removedChildElmtIds: number[]) { this.exitCount++; this.lastRemoved = removedChildElmtIds.slice(); },
            getFinalTheme(_view: ViewBuildNodeBase) { return undefined; },
        };

        let unregisterRemovedArgs: number[] | undefined = undefined;
        let obtainDeletedCalls = 0;
        let unregisterIViewsCalls = 0;

        try {
            let useMockIf = true;
            try {
                (If as any).getBranchId = () => 0;
                (If as any).branchId = (_branchId: number, removedChildElmtIds: number[], reservedChildElmtIds: number[]) => {
                    removedChildElmtIds.push(removedId);
                    reservedChildElmtIds.push(reservedId);
                };
                useMockIf = (If as any).getBranchId !== prevIfGetBranchId && (If as any).branchId !== prevIfBranchId;
                if (!useMockIf) {
                    (If as any).getBranchId = prevIfGetBranchId;
                    (If as any).branchId = prevIfBranchId;
                }
            } catch (err: any) {
                // If is implemented on native side, patching may be blocked.
                // Fall back to validating the public behavior with the real If implementation.
                useMockIf = false;
                (If as any).getBranchId = prevIfGetBranchId;
                (If as any).branchId = prevIfBranchId;
            }

            (UINodeRegisterProxy as any).unregisterRemovedElmtsFromViewPUs = (removedChildElmtIds: number[]) => {
                unregisterRemovedArgs = removedChildElmtIds.slice();
            };
            (UINodeRegisterProxy as any).obtainDeletedElmtIds = () => { obtainDeletedCalls++; };
            (UINodeRegisterProxy as any).unregisterElmtIdsFromIViews = () => { unregisterIViewsCalls++; };

            ViewBuildNodeBase.setArkThemeScopeManager(themeMgr as any);

            let branchFuncCalled = 0;
            const newBranchId = useMockIf ? 1 : (If.getBranchId() + 1);
            viewBuildNode.ifElseBranchUpdateFunction(newBranchId, () => { branchFuncCalled++; });

            eq(branchFuncCalled, 1, "branchfunc should be called when branchId changes");
            eq(viewBuildNode.dirtyRetakenCalls, 1, "ifElseBranchUpdateFunctionDirtyRetaken should be called");

            eq(unregisterRemovedArgs !== undefined, true, "unregisterRemovedElmtsFromViewPUs should be called");
            eq(obtainDeletedCalls, 1, "obtainDeletedElmtIds should be called once");
            eq(unregisterIViewsCalls, 1, "unregisterElmtIdsFromIViews should be called once");

            eq(themeMgr.enterCount, 1, "theme manager enter should be called");
            eq(themeMgr.exitCount, 1, "theme manager exit should be called");

            if (useMockIf) {
                const record = (viewBuildNode as any).updateFuncByElmtId.get(reservedId);
                eq(record?.isPending(), true, "reserved child should be set to pending");
                eq((viewBuildNode as any).elmtId2Repeat_.has(removedId), false, "removed id should be deleted from repeat map");

                eq(unregisterRemovedArgs?.length, 1, "unregisterRemovedElmtsFromViewPUs should be called with removed ids");
                eq(unregisterRemovedArgs?.[0], removedId, "removed id should be passed to unregisterRemovedElmtsFromViewPUs");
                eq(themeMgr.lastRemoved?.[0], removedId, "theme manager exit should receive removed ids");
            } else {
                eq(Array.isArray(themeMgr.lastRemoved), true, "theme manager exit should provide removed ids array");
            }
        } finally {
            (If as any).getBranchId = prevIfGetBranchId;
            (If as any).branchId = prevIfBranchId;
            (UINodeRegisterProxy as any).unregisterRemovedElmtsFromViewPUs = prevUnregisterRemoved;
            (UINodeRegisterProxy as any).obtainDeletedElmtIds = prevObtainDeleted;
            (UINodeRegisterProxy as any).unregisterElmtIdsFromIViews = prevUnregisterIViews;
            (ViewBuildNodeBase as any).arkThemeScopeManager = prevThemeMgr;
        }
    }

    // =========================================================================
    // SECTION 8: Theme Management
    // =========================================================================

    /**
     * Test onWillApplyThemeInternally can be called
     * Expected: Theme application completes without error
     */
    public testOnWillApplyThemeInternally(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const theme = {} as Theme;
        const prevThemeMgr = (ViewBuildNodeBase as any).arkThemeScopeManager;
        const themeMgr: any = {
            onIfElseBranchUpdateEnter: () => { },
            onIfElseBranchUpdateExit: (_removed: number[]) => { },
            getFinalTheme: (_view: ViewBuildNodeBase) => theme,
        };

        try {
            ViewBuildNodeBase.setArkThemeScopeManager(themeMgr as any);
            viewBuildNode.onWillApplyThemeInternally();
            eq(viewBuildNode.appliedThemes.length, 1, "onWillApplyTheme should be called when theme exists");
            eq(viewBuildNode.appliedThemes[0] === theme, true, "applied theme should match theme manager output");
        } finally {
            (ViewBuildNodeBase as any).arkThemeScopeManager = prevThemeMgr;
        }
    }

    /**
     * Test onGlobalThemeChanged can be called
     * Expected: Global theme change completes without error
     */
    public testOnGlobalThemeChanged(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const child1 = new MockView(1);
        const child2 = new MockView(2);
        viewBuildNode.addChild(child1);
        viewBuildNode.addChild(child2);

        const theme = {} as Theme;
        const prevThemeMgr = (ViewBuildNodeBase as any).arkThemeScopeManager;
        const themeMgr: any = {
            onIfElseBranchUpdateEnter: () => { },
            onIfElseBranchUpdateExit: (_removed: number[]) => { },
            getFinalTheme: (_view: ViewBuildNodeBase) => theme,
        };

        try {
            ViewBuildNodeBase.setArkThemeScopeManager(themeMgr as any);
            viewBuildNode.onGlobalThemeChanged();

            eq(viewBuildNode.forceCompleteRerenderCalls.length, 1, "forceCompleteRerender should be called once");
            eq(viewBuildNode.forceCompleteRerenderCalls[0], false, "forceCompleteRerender should be called with deep=false");
            eq(viewBuildNode.appliedThemes.length, 1, "onWillApplyTheme should be called during global theme change");
            eq(child1.globalThemeChangedCount, 1, "child1 should receive global theme change");
            eq(child2.globalThemeChangedCount, 1, "child2 should receive global theme change");
        } finally {
            (ViewBuildNodeBase as any).arkThemeScopeManager = prevThemeMgr;
        }
    }

    // =========================================================================
    // SECTION 9: LocalStorage Management
    // =========================================================================

    /**
     * Test getShareLocalStorage initially undefined
     * Expected: LocalStorage is undefined initially
     */
    public testGetShareLocalStorageInitiallyUndefined(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const localStorage = viewBuildNode.getShareLocalStorage();

        eq(localStorage, undefined, "LocalStorage should be undefined initially");
    }

    /**
     * Test setShareLocalStorage and getShareLocalStorage
     * Expected: LocalStorage can be set and retrieved
     */
    public testSetAndGetShareLocalStorage(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const mockLocalStorage = {} as LocalStorage;

        viewBuildNode.setShareLocalStorage(mockLocalStorage);
        const retrievedLocalStorage = viewBuildNode.getShareLocalStorage();

        eq(retrievedLocalStorage, mockLocalStorage, "LocalStorage should be retrieved correctly");
    }

    /**
     * Test setShareLocalStorage multiple times
     * Expected: LocalStorage can be updated
     */
    public testSetShareLocalStorageMultipleTimes(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const localStorage1 = {} as LocalStorage;
        const localStorage2 = {} as LocalStorage;

        viewBuildNode.setShareLocalStorage(localStorage1);
        eq(viewBuildNode.getShareLocalStorage(), localStorage1, "first LocalStorage set correctly");

        viewBuildNode.setShareLocalStorage(localStorage2);
        eq(viewBuildNode.getShareLocalStorage(), localStorage2, "second LocalStorage set correctly");
    }

    // =========================================================================
    // SECTION 10: Active State Management
    // =========================================================================

    /**
     * Test setActiveInternal with active = true
     * Expected: Active state is set
     */
    public testSetActiveInternalActive(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);

        const viewChild = new MockView(1);
        const builderChild = new SpyBuilderNode(false);
        viewBuildNode.addChild(viewChild);
        viewBuildNode.addChildBuilderNode(builderChild);

        viewBuildNode.setActiveInternal(true);

        eq(viewChild.activeInternalCalls.length, 1, "view child should receive setActiveInternal");
        eq(viewChild.activeInternalCalls[0].active, true, "view child active should be true");
        eq(viewChild.activeInternalCalls[0].isReuse, false, "view child isReuse should be false");

        eq(builderChild.activeInternalCalls.length, 1, "builder child should receive setActiveInternal");
        eq(builderChild.activeInternalCalls[0].active, true, "builder child active should be true");
        eq(builderChild.activeInternalCalls[0].isReuse, false, "builder child isReuse should be false");
    }

    /**
     * Test setActiveInternal with active = false
     * Expected: Inactive state is set
     */
    public testSetActiveInternalInactive(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);

        const viewChild = new MockView(1);
        const builderChild = new SpyBuilderNode(false);
        viewBuildNode.addChild(viewChild);
        viewBuildNode.addChildBuilderNode(builderChild);

        viewBuildNode.setActiveInternal(false);

        eq(viewChild.activeInternalCalls.length, 1, "view child should receive setActiveInternal");
        eq(viewChild.activeInternalCalls[0].active, false, "view child active should be false");

        eq(builderChild.activeInternalCalls.length, 1, "builder child should receive setActiveInternal");
        eq(builderChild.activeInternalCalls[0].active, false, "builder child active should be false");
    }

    /**
     * Test setActiveInternal with isReuse parameter
     * Expected: Active state with reuse flag is set
     */
    public testSetActiveInternalWithReuse(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);

        const viewChild = new MockView(1);
        const builderChild = new SpyBuilderNode(false);
        viewBuildNode.addChild(viewChild);
        viewBuildNode.addChildBuilderNode(builderChild);

        viewBuildNode.setActiveInternal(true, true);
        viewBuildNode.setActiveInternal(false, false);

        eq(viewChild.activeInternalCalls.length, 2, "view child should receive two calls");
        eq(viewChild.activeInternalCalls[0].isReuse, true, "first view child call should have isReuse=true");
        eq(viewChild.activeInternalCalls[1].isReuse, false, "second view child call should have isReuse=false");

        eq(builderChild.activeInternalCalls.length, 2, "builder child should receive two calls");
        eq(builderChild.activeInternalCalls[0].isReuse, true, "first builder child call should have isReuse=true");
        eq(builderChild.activeInternalCalls[1].isReuse, false, "second builder child call should have isReuse=false");
    }

    /**
     * Test setActiveInternal multiple calls
     * Expected: Multiple active state changes work correctly
     */
    public testSetActiveInternalMultipleCalls(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);

        const viewChild = new MockView(1);
        const builderChild = new SpyBuilderNode(false);
        viewBuildNode.addChild(viewChild);
        viewBuildNode.addChildBuilderNode(builderChild);

        viewBuildNode.setActiveInternal(true);
        viewBuildNode.setActiveInternal(false);
        viewBuildNode.setActiveInternal(true);
        viewBuildNode.setActiveInternal(false);

        eq(viewChild.activeInternalCalls.length, 4, "view child should receive 4 calls");
        eq(builderChild.activeInternalCalls.length, 4, "builder child should receive 4 calls");
    }

    // =========================================================================
    // SECTION 11: Element Information
    // =========================================================================

    /**
     * Test getElementNameById
     * Expected: Element name is returned
     */
    public testGetElementNameById(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);

        eq(viewBuildNode.getElementNameById(1), 'unknown component name', "unknown elmtId should return default name");

        class MyComp { }
        (viewBuildNode as any).updateFuncByElmtId.set(1, { updateFunc: () => { }, classObject: MyComp });
        eq(viewBuildNode.getElementNameById(1), 'MyComp', "known elmtId should return component name");
    }

    /**
     * Test debugInfoElmtId for profiler and non-profiler output
     * Expected: Non-profiler returns string; profiler returns structured info
     */
    public testDebugInfoElmtIdProfilerAndNonProfiler(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const elmtId = 123;

        class MyComp { }
        (viewBuildNode as any).updateFuncByElmtId.set(elmtId, { updateFunc: () => { }, classObject: MyComp });

        const child = new MockView(elmtId);
        viewBuildNode.addChild(child);

        eq(viewBuildNode.debugInfoElmtId(elmtId, false), 'MyComp[123]', "non-profiler debugInfo should match");

        const profilerInfo: any = viewBuildNode.debugInfoElmtId(elmtId, true);
        eq(profilerInfo.elementId, elmtId, "profiler elementId should match");
        eq(profilerInfo.elementTag, 'MyComp', "profiler elementTag should match component name");
        eq(profilerInfo.isCustomNode, true, "isCustomNode should be true when child exists");
    }

    // =========================================================================
    // SECTION 12: Edge Cases and Stress Tests
    // =========================================================================

    /**
     * Test many children
     * Expected: Many children can be added
     */
    public testManyChildren(): void {
        const parent = new MockViewBuildNodeBase(true);
        const childCount = 100;

        for (let i = 0; i < childCount; i++) {
            const child = new MockView(i);
            parent.addChild(child);
        }

        for (let i = 0; i < childCount; i++) {
            eq(parent.getChildById(i)?.id__(), i, `child ${i} should be retrievable`);
        }
    }

    /**
     * Test many builder nodes
     * Expected: Many builder nodes can be added
     */
    public testManyBuilderNodes(): void {
        const parent = new MockViewBuildNodeBase(true);
        const builderNodeCount = 50;
        let added = 0;

        for (let i = 0; i < builderNodeCount; i++) {
            const child = new MockViewBuildNodeBase(false);
            if (parent.addChildBuilderNode(child)) {
                added++;
            }
        }

        eq(added, builderNodeCount, "all builder nodes should be added successfully");
        eq(parent.getOrCreateBuilderNodeWeakrefMap().size, builderNodeCount, "builder node map size should match");
    }

    /**
     * Test builder node add remove add cycle
     * Expected: BuilderNode can be added, removed, and added again
     */
    public testBuilderNodeAddRemoveAddCycle(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child = new MockViewBuildNodeBase(false);

        eq(parent.addChildBuilderNode(child), true, "first add succeeds");

        parent.removeChildBuilderNode(child.id__());

        eq(parent.addChildBuilderNode(child), true, "add after remove succeeds");
    }

    /**
     * Test state consistency after multiple operations
     * Expected: State remains consistent
     */
    public testStateConsistencyAfterMultipleOperations(): void {
        const viewBuildNode = new MockViewBuildNodeBase(true);
        const id = viewBuildNode.id__();

        const child1 = new MockView(1);
        const child2 = new MockView(2);
        const builderNode1 = new MockViewBuildNodeBase(false);

        viewBuildNode.addChild(child1);
        viewBuildNode.addChild(child2);
        viewBuildNode.addChildBuilderNode(builderNode1);

        eq(viewBuildNode.id__(), id, "ID remains consistent");
        eq(viewBuildNode.getChildById(1)?.id__(), 1, "child1 still retrievable");
        eq(viewBuildNode.getChildById(2)?.id__(), 2, "child2 still retrievable");

        viewBuildNode.removeChildBuilderNode(builderNode1.id__());
        viewBuildNode.clearChildBuilderNode();

        eq(viewBuildNode.id__(), id, "ID still consistent after removals");
    }

    /**
     * Test zero and negative IDs
     * Expected: Zero and negative IDs are handled
     */
    public testZeroAndNegativeIds(): void {
        const parent = new MockViewBuildNodeBase(true);
        const child0 = new MockView(0);
        const childNeg1 = new MockView(-1);
        const childNeg100 = new MockView(-100);

        eq(parent.addChild(child0), true, "child with ID 0 added");
        eq(parent.addChild(childNeg1), true, "child with ID -1 added");
        eq(parent.addChild(childNeg100), true, "child with ID -100 added");

        eq(parent.getChildById(0)?.id__(), 0, "child with ID 0 retrievable");
        eq(parent.getChildById(-1)?.id__(), -1, "child with ID -1 retrievable");
        eq(parent.getChildById(-100)?.id__(), -100, "child with ID -100 retrievable");
    }

    /**
     * Test large IDs
     * Expected: Large IDs are handled
     */
    public testLargeIds(): void {
        const parent = new MockViewBuildNodeBase(true);
        const largeId1 = 999999;
        const largeId2 = 2147483647;

        const child1 = new MockView(largeId1);
        const child2 = new MockView(largeId2);

        eq(parent.addChild(child1), true, "child with large ID 1 added");
        eq(parent.addChild(child2), true, "child with large ID 2 added");

        eq(parent.getChildById(largeId1)?.id__(), largeId1, "child with large ID 1 retrievable");
        eq(parent.getChildById(largeId2)?.id__(), largeId2, "child with large ID 2 retrievable");
    }

    /**
     * Test multiple parents with same child ID
     * Expected: Different parents can have children with same ID
     */
    public testMultipleParentsSameChildId(): void {
        const parent1 = new MockViewBuildNodeBase(true);
        const parent2 = new MockViewBuildNodeBase(true);
        const child1 = new MockView(1);
        const child2 = new MockView(1);

        eq(parent1.addChild(child1), true, "parent1 adds child with ID 1");
        eq(parent2.addChild(child2), true, "parent2 adds child with ID 1");

        eq(parent1.getChildById(1)?.id__(), 1, "parent1 child retrievable");
        eq(parent2.getChildById(1)?.id__(), 1, "parent2 child retrievable");
    }
}
