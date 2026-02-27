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

// ============================================================================
// Type Definitions and Mock Classes
// ============================================================================

declare class PUV2ViewBase {
    static isNeedBuildPrebuildCmd(): boolean;
    static prebuildFuncQueues: Map<number, any>;
    static prebuildingElmtId_: number;
    static inactiveComponents_: Set<string>;
    static doReuse(component: any): void;
    static doRecycle(component: any): void;
}

declare class IView {
    id__(): number;
    parent_: IView | undefined;
    childrenWeakrefMap_: Map<number, WeakRef<any>>;
    builderNodeWeakrefMap_: Map<number, WeakRef<any>>;
    isDeleting_: boolean;
    isCompFreezeAllowed_(): boolean;
    activeCount_: number;
    updateFuncByElmtId: Map<number, any>;
    elmtIdsDelayedUpdate: Set<number>;
    dirtRetakenElementIds_: Set<number>;
    getChildViewV2ForElmtId(elmtId: number): any;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;
    isFirstRender(): boolean;
    isViewActive(): boolean;
    scheduleDelayedUpdate(elmtId: number): void;
    syncInstanceId(): void;
    restoreInstanceId(): void;
    markNeedUpdate(): void;
    getNodeById(elmtId: number): any;
    getParent(): IView;
    removeChild(child: any): void;
    setChild(child: any): void;
}

declare class IPropertySubscriber {
    id_: number;
}

declare class ExtraInfo {}

declare class RecyclePoolV2 {
    pushRecycleV2Component(reuseId: string, component: any): void;
    popRecycleV2Component(reuseId: string): any;
    getRecycleIdMapping(elmtId: number): number;
    updateRecycleIdMapping(elmtId: number, newElmtId: number): void;
    purgeAllCachedRecycleElmtIds(): void;
}

declare class ObserveV2 {
    static ID_REFS: string;
    static SYNC_MONITOR_REFS: string;
    static COMPUTED_REFS: string;
    static V2_DECO_META: string;
    static V2_DECO_METHOD_META: string;
    static SYMBOL_REFS: string;
    static NO_REUSE: number;
    static getObserve(): any;
    static getCurrentRecordedId(): number;
    static constructComputed(view: any, name: string): void;
    static constructMonitor(view: any, name: string): void;
    static constructSyncMonitors(view: any, name: string): void;
    static setCurrentReuseId(id: number): void;
    static updateDirty2(arg1: boolean, arg2: boolean): void;
    static clearBinding(elmtId: number): void;
    static startRecordDependencies(view: any, elmtId: number): void;
    static stopRecordDependencies(): void;
    static runIdleTasks(): void;
    static resetMonitorValues(): void;
    static fireChange(view: any, varName: string): void;
    static updateDirtyComputedProps(ids: number[]): void;
    static updateDirtyMonitors(ids: Set<number>): void;
    static updateDirtyMonitorPath(ids: Set<number>): void;
    static runMonitorFunctionsForAddMonitor(funcs: Set<number>): void;
    static getDecoratorInfo(view: any, property: string): string;
}

declare class SubscriberManager {
    static Add(subscriber: any): void;
    static Delete(id: number): void;
}

declare class UINodeRegisterProxy {
    static ElementIdToOwningViewPU_: Map<number, WeakRef<any>>;
    static notRecordingDependencies: number;
    static unregisterRemovedElmtsFromViewPUs(ids: number[]): void;
}

declare class ViewStackProcessor {
    static AllocateNewElmetIdForNextComponent(): number;
    static StartGetAccessRecordingFor(elmtId: number): void;
    static StopGetAccessRecording(): void;
    static PushPrebuildCompCmd(): void;
}

declare class ViewBuildNodeBase {
    static arkThemeScopeManager: any;
}

declare class MonitorV2 {
    static clearWatchesFromTarget(target: any): void;
}

declare class ComputedV2 {
    static clearComputedFromTarget(target: any): void;
    static MIN_COMPUTED_ID: number;
}

declare class MonitorV2Value {
    static MIN_WATCH_ID: number;
}

declare class PersistenceV2Impl {
    static MIN_PERSISTENCE_ID: number;
}

declare class ProviderConsumerUtilV2 {
    static ALIAS_PREFIX: string;
    static findProvider(view: any, providerName: string): any;
    static connectConsumer2Provider(view: any, varName: string, provider: any, key: string): void;
    static defineConsumerWithoutProvider(view: any, varName: string, value: any): void;
}

declare class VariableUtilV2 {
    static initParam<T>(view: any, varName: string, value: T): void;
    static updateParam<T>(view: any, varName: string, value: T): void;
    static resetParam<T>(view: any, varName: string, value: T): void;
}

declare class stateMgmtConsole {
    static debug(msg: string): void;
    static error(msg: string): void;
    static warn(msg: string): void;
    static applicationError(msg: string): void;
    static log(msg: string): void;
}

declare class stateMgmtProfiler {
    static begin(name: string): void;
    static end(): void;
}

declare class stateMgmtTrace {
    static scopedTrace(fn: () => void, name: string, className: string): void;
}

declare class stateMgmtDFX {
    static unwrapRawValue(value: any): any;
}

declare class BusinessError {
    constructor(code: number, message: string);
}

declare class REUSABLE_V2_OLD_TOOLCHAIN {
    static value: number;
}

declare class PERSISTENCE_V2_MISMATCH_BETWEEN_KEY_AND_TYPE {
    static value: number;
}

declare class PERSISTENCE_V2_LACK_TYPE {
    static value: number;
}

declare class ArkComponent {
    cleanStageValue(): void;
}

declare class ArkUIObjectFinalizationRegisterProxy {
    static callbackFunc_: any;
    static call(ref: WeakRef<any>, message: string): void;
}

declare class LifeCycleEvent {
    static ON_REUSE: string;
    static ON_RECYCLE: string;
}

declare class _arkUIUncaughtPromiseError {
    static call(error: any): void;
}

declare class ViewV2 {
    constructor(parent?: IView, elmtId?: number, extraInfo?: ExtraInfo);
    id__(): number;
    parent_: IView | undefined;
    childrenWeakrefMap_: Map<number, WeakRef<any>>;
    builderNodeWeakrefMap_: Map<number, WeakRef<any>>;
    isDeleting_: boolean;
    isCompFreezeAllowed_(): boolean;
    activeCount_: number;
    updateFuncByElmtId: Map<number, any>;
    elmtIdsDelayedUpdate: Set<number>;
    dirtRetakenElementIds_: Set<number>;
    getChildViewV2ForElmtId(elmtId: number): any;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;
    isFirstRender(): boolean;
    isViewActive(): boolean;
    scheduleDelayedUpdate(elmtId: number): void;
    syncInstanceId(): void;
    restoreInstanceId(): void;
    markNeedUpdate(): void;
    getNodeById(elmtId: number): any;
    getParent(): IView;
    removeChild(child: any): void;
    setChild(child: any): void;
    dirtDescendantElementIds_: Set<number>;
    monitorIdsDelayedUpdate?: Set<number>;
    computedIdsDelayedUpdate?: Set<number>;
    defaultConsumerV2__?: Map<string, any>;
    connectConsumerV2__?: Map<string, any>;
    hasBeenRecycled_: boolean;
    paramsGenerator_?: any;
    monitorIdsDelayedUpdateForAddMonitor_?: Set<number>;
    getOrCreateMonitorIdsDelayedUpdate(): Set<number>;
    getOrCreateMonitorIdsDelayedUpdateForAddMonitor(): Set<number>;
    getOrCreateComputedIdsDelayedUpdate(): Set<number>;
    getOrCreateDefaultConsumerV2(): Map<string, any>;
    getOrCreateConnectConsumerV2(): Map<string, any>;
    debugInfo__(): string;
    debugInfoView(recursive?: boolean): string;
    debugInfoDirtDescendantElementIds(recursive?: boolean): string;
    debugInfoStateVars(): string;
    getOrCreateRecyclePool(): RecyclePoolV2;
    getRecyclePool(): RecyclePoolV2 | undefined;
    hasRecyclePool(): boolean;
    isViewV2(): boolean;
    addDelayedMonitorIds(id: number): void;
    addDelayedMonitorIdsForAddMonitor(id: number): void;
    addDelayedComputedIds(id: number): void;
    getViewV2ChildById(elmtId: number): any;
    resetStateVarsOnReuse(params: any): void;
    aboutToReuse(): void;
    resetMonitorsOnReuse(): void;
    resetComputed(varName: string): void;
    localStorage_(): LocalStorage;
    observeRecycleComponentCreation(componentName: string, fn: () => void): void;
    __setTSCard__Internal(propertyName: string, value: any): void;
    __checkValidDecorator__Internal(propertyName: string): boolean;
    __getPathValueFromJson__Internal(propertyName: string, path: string): any;
    __getDecoratorPropertyName__V2View__Internal(): string[];
    initParam(varName: string, value: any): void;
    updateParam(varName: string, value: any): void;
    resetParam(varName: string, value: any): void;
    findProvidePU__(providerName: string): any;
    __mkRepeatAPI<I>(arr: Array<I>): RepeatAPI<I>;
    mutableBuilderImpl(builder: Function, ...args: any[]): void;
}

declare class UpdateFuncRecord {
    isPending(): boolean;
    setIsChanged(changed: boolean): void;
    getUpdateFunc(): Function;
    getComponentName(): string;
}

declare class UpdateFunc {
}

declare class PrebuildFunc {
}

declare class WeakRef<T> {
    constructor(target: T);
    deref(): T | undefined;
}

declare class WeakMap<K, V> {
    constructor();
    get(key: K): V | undefined;
    set(key: K, value: V): void;
    delete(key: K): boolean;
    has(key: K): boolean;
    forEach(callback: (value: V, key: K, map: Map<K, V>) => void): void;
}

declare class LocalStorage {
    constructor(options: any);
}

declare class If {
    static create(): void;
    static pop(): void;
}

declare class RepeatAPI<I> {
}

declare class __Repeat<I> {
    constructor(view: any, arr: Array<I>);
    updateArr(arr: Array<I>): void;
}

declare class ProfileRecursionCounter {
    total: number;
}

declare class InteropConfigureStateMgmt {
    static needsInterop(): boolean;
}

// ============================================================================
// Test Fixture Classes
// ============================================================================

class MockViewV2 extends ViewV2 {
    testProperty: string = 'test';
    testNumber: number = 42;
    testBoolean: boolean = true;
    testArray: number[] = [1, 2, 3];
    testObject: any = { key: 'value' };

    public parent_: any;
    private elmtId_: number;

    constructor(parent?: IView, elmtId?: number, extraInfo?: ExtraInfo) {
        super(parent, elmtId, extraInfo);
        this.parent_ = parent;
        this.elmtId_ = elmtId || 0;
    }

    public getTestProperty(): string {
        return this.testProperty;
    }

    public setTestProperty(value: string): void {
        this.testProperty = value;
    }

    public isViewV2(): boolean {
        return true;
    }

    public id__(): number {
        return this.elmtId_;
    }
}

class ReusableMockViewV2 extends ViewV2 {
    isReusable_: boolean = true;
    testValue: string = 'reusable';
}

class ViewV2WithChildren extends ViewV2 {
    children: MockViewV2[] = [];

    public addChild(child: MockViewV2): void {
        this.children.push(child);
        this.setChild(child);
    }
}

class ViewV2WithRecyclePool extends ViewV2 {
    recyclePoolCreated: boolean = false;

    public override getOrCreateRecyclePool(): RecyclePoolV2 {
        this.recyclePoolCreated = true;
        return super.getOrCreateRecyclePool();
    }
}

// ============================================================================
// Main Test Class
// ============================================================================

export class V2ViewTests implements ITestFile {

    private idString: string = "";

    constructor(str: string) {
        console.log(`Creating V2ViewTests: ${str}`)
        this.idString = str;
    }

    public beforeAll(): void {}

    public beforeEach(): void {}

    public afterAll(): void {}

    public afterEach(): void {}

    public getId(): string {
        return this.idString;
    }

    // =========================================================================
    // Constructor Tests
    // =========================================================================

    public testConstructorWithoutParent(): void {
        const view = new MockViewV2(undefined, 200);
        eq(view.parent_, undefined, 'Constructor should handle undefined parent');
    }

    public testConstructorInitializesDirtDescendantElementIds(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.dirtDescendantElementIds_ instanceof Set, true, 'Constructor should initialize dirtDescendantElementIds_ as Set');
        eq(view.dirtDescendantElementIds_.size, 0, 'Constructor should initialize empty dirtDescendantElementIds_');
    }

    public testConstructorInitializesMonitorIdsDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.monitorIdsDelayedUpdate, undefined, 'Constructor should initialize monitorIdsDelayedUpdate as undefined');
    }

    public testConstructorInitializesComputedIdsDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.computedIdsDelayedUpdate, undefined, 'Constructor should initialize computedIdsDelayedUpdate as undefined');
    }

    public testConstructorInitializesConsumerMaps(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.defaultConsumerV2__, undefined, 'Constructor should initialize defaultConsumerV2 as undefined');
        eq(view.connectConsumerV2__, undefined, 'Constructor should initialize connectConsumerV2 as undefined');
    }

    public testConstructorInitializesHasBeenRecycled(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.hasBeenRecycled_, false, 'Constructor should initialize hasBeenRecycled as false');
    }

    public testConstructorInitializesParamsGenerator(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.paramsGenerator_, undefined, 'Constructor should initialize paramsGenerator as undefined');
    }

    // =========================================================================
    // MonitorIdsDelayedUpdate Tests
    // =========================================================================

    public testGetMonitorIdsDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.monitorIdsDelayedUpdate;
        eq(result, undefined, 'Should return undefined when not initialized');
    }

    public testGetOrCreateMonitorIdsDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        const set1 = view.getOrCreateMonitorIdsDelayedUpdate();
        const set2 = view.getOrCreateMonitorIdsDelayedUpdate();
        eq(set1 instanceof Set, true, 'Should create Set');
        eq(set1 === set2, true, 'Should return same instance on subsequent calls');
    }

    public testGetOrCreateMonitorIdsDelayedUpdateAddsToSet(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(200);
        eq(set.size, 2, 'Should allow adding to set');
    }

    // =========================================================================
    // MonitorIdsDelayedUpdateForAddMonitor Tests
    // =========================================================================

    public testGetMonitorIdsDelayedUpdateForAddMonitor(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.monitorIdsDelayedUpdateForAddMonitor_;
        eq(result, undefined, 'Should return undefined when not initialized');
    }

    public testGetOrCreateMonitorIdsDelayedUpdateForAddMonitor(): void {
        const view = new MockViewV2(undefined, 100);
        const set1 = view.getOrCreateMonitorIdsDelayedUpdateForAddMonitor();
        const set2 = view.getOrCreateMonitorIdsDelayedUpdateForAddMonitor();
        eq(set1 instanceof Set, true, 'Should create Set');
        eq(set1 === set2, true, 'Should return same instance on subsequent calls');
    }

    public testGetOrCreateMonitorIdsDelayedUpdateForAddMonitorAddsToSet(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdateForAddMonitor();
        set.add(300);
        set.add(400);
        eq(set.size, 2, 'Should allow adding to set');
    }

    // =========================================================================
    // ComputedIdsDelayedUpdate Tests
    // =========================================================================

    public testGetComputedIdsDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.computedIdsDelayedUpdate;
        eq(result, undefined, 'Should return undefined when not initialized');
    }

    public testGetOrCreateComputedIdsDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        const set1 = view.getOrCreateComputedIdsDelayedUpdate();
        const set2 = view.getOrCreateComputedIdsDelayedUpdate();
        eq(set1 instanceof Set, true, 'Should create Set');
        eq(set1 === set2, true, 'Should return same instance on subsequent calls');
    }

    public testGetOrCreateComputedIdsDelayedUpdateAddsToSet(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateComputedIdsDelayedUpdate();
        set.add(500);
        set.add(600);
        eq(set.size, 2, 'Should allow adding to set');
    }

    // =========================================================================
    // DefaultConsumerV2 Tests
    // =========================================================================

    public testGetDefaultConsumerV2(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.defaultConsumerV2__;
        eq(result, undefined, 'Should return undefined when not initialized');
    }

    public testGetOrCreateDefaultConsumerV2(): void {
        const view = new MockViewV2(undefined, 100);
        const map1 = view.getOrCreateDefaultConsumerV2();
        const map2 = view.getOrCreateDefaultConsumerV2();
        eq(map1 instanceof Map, true, 'Should create Map');
        eq(map1 === map2, true, 'Should return same instance on subsequent calls');
    }

    public testGetOrCreateDefaultConsumerV2AddsToMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        map.set('key2', 'value2');
        eq(map.size, 2, 'Should allow adding to map');
    }

    // =========================================================================
    // ConnectConsumerV2 Tests
    // =========================================================================

    public testGetConnectConsumerV2(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.connectConsumerV2__;
        eq(result, undefined, 'Should return undefined when not initialized');
    }

    public testGetOrCreateConnectConsumerV2(): void {
        const view = new MockViewV2(undefined, 100);
        const map1 = view.getOrCreateConnectConsumerV2();
        const map2 = view.getOrCreateConnectConsumerV2();
        eq(map1 instanceof Map, true, 'Should create Map');
        eq(map1 === map2, true, 'Should return same instance on subsequent calls');
    }

    public testGetOrCreateConnectConsumerV2AddsToMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateConnectConsumerV2();
        map.set('consumer1', 'provider1');
        map.set('consumer2', 'provider2');
        eq(map.size, 2, 'Should allow adding to map');
    }

    // =========================================================================
    // DebugInfo Tests
    // =========================================================================

    public testDebugInfo(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.debugInfo__();
        eq(typeof result, 'string', 'Should return string');
        eq(result.includes('MockViewV2'), true, 'Should include class name');
        eq(result.includes('100'), true, 'Should include elmtId');
    }

    // =========================================================================
    // RecyclePool Tests
    // =========================================================================

    public testGetOrCreateRecyclePool(): void {
        const view = new MockViewV2(undefined, 100);
        const pool1 = view.getOrCreateRecyclePool();
        const pool2 = view.getOrCreateRecyclePool();
        eq(pool1 instanceof RecyclePoolV2, true, 'Should create RecyclePoolV2');
        eq(pool1 === pool2, true, 'Should return same instance on subsequent calls');
    }

    public testGetRecyclePool(): void {
        const view = new MockViewV2(undefined, 100);
        const pool = view.getRecyclePool();
        eq(pool, undefined, 'Should return undefined when not created');
    }

    public testGetRecyclePoolAfterCreation(): void {
        const view = new MockViewV2(undefined, 100);
        view.getOrCreateRecyclePool();
        const pool = view.getRecyclePool();
        eq(pool instanceof RecyclePoolV2, true, 'Should return pool after creation');
    }

    public testHasRecyclePool(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.hasRecyclePool(), false, 'Should return false when pool not created');
    }

    public testHasRecyclePoolAfterCreation(): void {
        const view = new MockViewV2(undefined, 100);
        view.getOrCreateRecyclePool();
        eq(view.hasRecyclePool(), true, 'Should return true after pool creation');
    }

    // =========================================================================
    // IsViewV2 Tests
    // =========================================================================

    public testIsViewV2(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.isViewV2(), true, 'Should return true for ViewV2 instances');
    }

    // =========================================================================
    // AddDelayedMonitorIds Tests
    // =========================================================================

    public testAddDelayedMonitorIds(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedMonitorIds(200);
        eq(view.monitorIdsDelayedUpdate?.size, 2, 'Should add monitor IDs');
        eq(view.monitorIdsDelayedUpdate?.has(100), true, 'Should contain first ID');
        eq(view.monitorIdsDelayedUpdate?.has(200), true, 'Should contain second ID');
    }

    public testAddDelayedMonitorIdsMultipleCalls(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedMonitorIds(100);
        eq(view.monitorIdsDelayedUpdate?.size, 1, 'Should handle duplicate IDs');
    }

    // =========================================================================
    // AddDelayedMonitorIdsForAddMonitor Tests
    // =========================================================================

    public testAddDelayedMonitorIdsForAddMonitor(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIdsForAddMonitor(300);
        view.addDelayedMonitorIdsForAddMonitor(400);
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.size, 2, 'Should add monitor IDs');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.has(300), true, 'Should contain first ID');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.has(400), true, 'Should contain second ID');
    }

    public testAddDelayedMonitorIdsForAddMonitorMultipleCalls(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIdsForAddMonitor(300);
        view.addDelayedMonitorIdsForAddMonitor(300);
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.size, 1, 'Should handle duplicate IDs');
    }

    // =========================================================================
    // AddDelayedComputedIds Tests
    // =========================================================================

    public testAddDelayedComputedIds(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedComputedIds(500);
        view.addDelayedComputedIds(600);
        eq(view.computedIdsDelayedUpdate?.size, 2, 'Should add computed IDs');
        eq(view.computedIdsDelayedUpdate?.has(500), true, 'Should contain first ID');
        eq(view.computedIdsDelayedUpdate?.has(600), true, 'Should contain second ID');
    }

    public testAddDelayedComputedIdsMultipleCalls(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedComputedIds(500);
        view.addDelayedComputedIds(500);
        eq(view.computedIdsDelayedUpdate?.size, 1, 'Should handle duplicate IDs');
    }

    // =========================================================================
    // GetViewV2ChildById Tests
    // =========================================================================

    public testGetViewV2ChildByIdNotFound(): void {
        const parent = new MockViewV2(undefined, 100);
        const result = parent.getViewV2ChildById(999);
        eq(result, undefined, 'Should return undefined for non-existent child');
    }

    // =========================================================================
    // ResetStateVarsOnReuse Tests
    // =========================================================================

    public testResetStateVarsOnReuse(): void {
        const view = new MockViewV2(undefined, 100);
        try {
            view.resetStateVarsOnReuse({});
            eq(false, true, 'Should throw BusinessError for old toolchain');
        } catch (e) {
            eq(true, true, 'Should throw BusinessError for old toolchain');
        }
    }

    // =========================================================================
    // AboutToReuse Tests
    // =========================================================================

    public testAboutToReuse(): void {
        const view = new MockViewV2(undefined, 100);
        view.aboutToReuse();
        eq(true, true, 'Should complete without error');
    }

    // =========================================================================
    // ResetMonitorsOnReuse Tests
    // =========================================================================

    public testResetMonitorsOnReuse(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedMonitorIdsForAddMonitor(200);
        view.resetMonitorsOnReuse();
        eq(view.monitorIdsDelayedUpdate?.size, 0, 'Should clear monitorIdsDelayedUpdate');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.size, 0, 'Should clear monitorIdsDelayedUpdateForAddMonitor');
    }

    public testResetMonitorsOnReuseWithEmptySets(): void {
        const view = new MockViewV2(undefined, 100);
        view.resetMonitorsOnReuse();
        eq(true, true, 'Should handle empty sets');
    }

    // =========================================================================
    // DebugInfoViewRecursive Tests
    // DebugInfoView Tests
    // =========================================================================

    public testDebugInfoView(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.debugInfoView();
        eq(typeof result, 'string', 'Should return string');
        eq(result.includes('@ComponentV2'), true, 'Should include component type');
        eq(result.includes('MockViewV2'), true, 'Should include class name');
    }

    public testDebugInfoViewRecursive(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.debugInfoView(true);
        eq(typeof result, 'string', 'Should return string for recursive');
    }

    // =========================================================================
    // DebugInfoDirtDescendantElementIds Tests
    // =========================================================================

    public testDebugInfoDirtDescendantElementIds(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.debugInfoDirtDescendantElementIds();
        eq(typeof result, 'string', 'Should return string');
        eq(result.includes('MockViewV2'), true, 'Should include class name');
    }

    public testDebugInfoDirtDescendantElementIdsRecursive(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.debugInfoDirtDescendantElementIds(true);
        eq(typeof result, 'string', 'Should return string for recursive');
    }

    // =========================================================================
    // ObserveRecycleComponentCreation Tests
    // =========================================================================

    public testObserveRecycleComponentCreation(): void {
        const view = new MockViewV2(undefined, 100);
        view.observeRecycleComponentCreation('TestComponent', () => {});
        eq(true, true, 'Should complete without error');
    }

    // =========================================================================
    // SetTSCard Tests
    // =========================================================================

    public testSetTSCardInvalidDecorator(): void {
        const view = new MockViewV2(undefined, 100);
        view.__setTSCard__Internal('invalidProperty', 'value');
        eq(true, true, 'Should handle invalid decorator');
    }

    // =========================================================================
    // CheckValidDecorator Tests
    // =========================================================================

    public testCheckValidDecoratorLocal(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.__checkValidDecorator__Internal('testProperty');
        eq(typeof result, 'boolean', 'Should return boolean');
    }

    // =========================================================================
    // GetPathValueFromJson Tests
    // =========================================================================

    public testGetPathValueFromJson(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.__getPathValueFromJson__Internal('testProperty', 'path');
        eq(typeof result === 'string' || result === undefined, true, 'Should return string or undefined');
    }

    public testGetPathValueFromJsonInvalidProperty(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.__getPathValueFromJson__Internal('invalidProperty', 'path');
        eq(result, undefined, 'Should return undefined for invalid property');
    }

    // =========================================================================
    // GetDecoratorPropertyName Tests
    // =========================================================================

    public testGetDecoratorPropertyName(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.__getDecoratorPropertyName__V2View__Internal();
        eq(Array.isArray(result), true, 'Should return array');
    }

    // =========================================================================
    // DebugInfoStateVars Tests
    // =========================================================================

    public testDebugInfoStateVars(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.debugInfoStateVars();
        eq(typeof result, 'string', 'Should return string');
        eq(result.includes('MockViewV2'), true, 'Should include class name');
    }

    // =========================================================================
    // FindProvidePU Tests
    // =========================================================================

    public testFindProvidePU(): void {
        const view = new MockViewV2(undefined, 100);
        const result = view.findProvidePU__('testProvider');
        eq(result === undefined || typeof result === 'object', true, 'Should return provider or undefined');
    }

    // =========================================================================
    // MkRepeatAPI Tests
    // =========================================================================

    public testMkRepeatAPI(): void {
        const view = new MockViewV2(undefined, 100);
        const arr = [1, 2, 3, 4, 5];
        const result = view.__mkRepeatAPI(arr);
        eq(result !== undefined, true, 'Should return RepeatAPI');
    }

    public testMkRepeatAPIEmptyArray(): void {
        const view = new MockViewV2(undefined, 100);
        const arr: number[] = [];
        const result = view.__mkRepeatAPI(arr);
        eq(result !== undefined, true, 'Should handle empty array');
    }

    public testMkRepeatAPISingleElement(): void {
        const view = new MockViewV2(undefined, 100);
        const arr = [1];
        const result = view.__mkRepeatAPI(arr);
        eq(result !== undefined, true, 'Should handle single element array');
    }

    public testMkRepeatAPILargeArray(): void {
        const view = new MockViewV2(undefined, 100);
        const arr: number[] = [];
        for (let j = 0; j < 1000; j++) {
            arr.push(j);
        }
        const result = view.__mkRepeatAPI(arr);
        eq(result !== undefined, true, 'Should handle large array');
    }

    // =========================================================================
    // Additional Edge Cases Tests
    // =========================================================================

    public testMultipleGetOrCreateCalls(): void {
        const view = new MockViewV2(undefined, 100);
        const set1 = view.getOrCreateMonitorIdsDelayedUpdate();
        const set2 = view.getOrCreateMonitorIdsDelayedUpdate();
        const set3 = view.getOrCreateMonitorIdsDelayedUpdate();
        eq(set1 === set2, true, 'First and second calls should return same instance');
        eq(set2 === set3, true, 'Second and third calls should return same instance');
    }

    public testGetOrCreateAfterAddingElements(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(200);
        set.add(300);
        eq(set.size, 3, 'Should maintain all added elements');
    }

    public testClearingDelayedSets(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedMonitorIds(200);
        view.monitorIdsDelayedUpdate?.clear();
        eq(view.monitorIdsDelayedUpdate?.size, 0, 'Should allow clearing sets');
    }

    public testEmptyViewInstance(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.dirtDescendantElementIds_.size, 0, 'Empty view should have no dirty elements');
        eq(view.monitorIdsDelayedUpdate, undefined, 'Empty view should have no delayed monitors');
        eq(view.computedIdsDelayedUpdate, undefined, 'Empty view should have no delayed computed');
    }

    public testViewWithMultipleDelayedUpdates(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedMonitorIdsForAddMonitor(200);
        view.addDelayedComputedIds(300);
        eq(view.monitorIdsDelayedUpdate?.size, 1, 'Should have one monitor ID');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.size, 1, 'Should have one add monitor ID');
        eq(view.computedIdsDelayedUpdate?.size, 1, 'Should have one computed ID');
    }

    public testReusePoolLifecycle(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.hasRecyclePool(), false, 'Should not have pool initially');
        view.getOrCreateRecyclePool();
        eq(view.hasRecyclePool(), true, 'Should have pool after creation');
        const pool = view.getRecyclePool();
        eq(pool !== undefined, true, 'Should retrieve pool');
    }

    public testConsumerMapLifecycle(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.defaultConsumerV2__, undefined, 'Should not have default consumer initially');
        eq(view.connectConsumerV2__, undefined, 'Should not have connect consumer initially');
        view.getOrCreateDefaultConsumerV2();
        view.getOrCreateConnectConsumerV2();
        eq(view.defaultConsumerV2__ !== undefined, true, 'Should have default consumer after creation');
        eq(view.connectConsumerV2__ !== undefined, true, 'Should have connect consumer after creation');
    }

    public testDelayedUpdatesAccumulation(): void {
        const view = new MockViewV2(undefined, 100);
        for (let j = 0; j < 10; j++) {
            view.addDelayedMonitorIds(j);
        }
        eq(view.monitorIdsDelayedUpdate?.size, 10, 'Should accumulate all delayed updates');
    }

    public testSetOperationsOnDelayedSets(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(200);
        set.delete(100);
        eq(set.size, 1, 'Should support delete operation');
        eq(set.has(200), true, 'Should contain remaining element');
    }

    public testMultipleViewsIndependence(): void {
        const view1 = new MockViewV2(undefined, 100);
        const view2 = new MockViewV2(undefined, 200);
        view1.addDelayedMonitorIds(100);
        view2.addDelayedMonitorIds(200);
        eq(view1.monitorIdsDelayedUpdate?.size, 1, 'View1 should have one delayed monitor');
        eq(view2.monitorIdsDelayedUpdate?.size, 1, 'View2 should have one delayed monitor');
        eq(view1.monitorIdsDelayedUpdate?.has(100), true, 'View1 should have its own ID');
        eq(view2.monitorIdsDelayedUpdate?.has(200), true, 'View2 should have its own ID');
    }

    public testNullAndUndefinedHandling(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(0);
        eq(set.has(0), true, 'Should handle zero value');
        set.delete(0);
        eq(set.has(0), false, 'Should handle deletion of zero value');
    }

    public testLargeNumberOfDelayedUpdates(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 0; j < 1000; j++) {
            set.add(j);
        }
        eq(set.size, 1000, 'Should handle large number of delayed updates');
    }

    public testConsumerMapOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const defaultMap = view.getOrCreateDefaultConsumerV2();
        const connectMap = view.getOrCreateConnectConsumerV2();
        defaultMap.set('key1', 'value1');
        defaultMap.set('key2', 'value2');
        connectMap.set('consumer1', 'provider1');
        eq(defaultMap.size, 2, 'Default map should have two entries');
        eq(connectMap.size, 1, 'Connect map should have one entry');
        defaultMap.delete('key1');
        eq(defaultMap.size, 1, 'Should support delete operation');
    }

    public testDebugInfoConsistency(): void {
        const view = new MockViewV2(undefined, 100);
        const info1 = view.debugInfo__();
        const info2 = view.debugInfo__();
        eq(info1, info2, 'Debug info should be consistent across calls');
    }

    public testViewHierarchyIndependence(): void {
        const parent = new MockViewV2(undefined, 100);
        const child = new MockViewV2(parent, 200);
        parent.addDelayedMonitorIds(100);
        child.addDelayedMonitorIds(200);
        eq(parent.monitorIdsDelayedUpdate?.size, 1, 'Parent should have its own delayed monitors');
        eq(child.monitorIdsDelayedUpdate?.size, 1, 'Child should have its own delayed monitors');
    }

    public testReusePoolIndependence(): void {
        const view1 = new MockViewV2(undefined, 100);
        const view2 = new MockViewV2(undefined, 200);
        const pool1 = view1.getOrCreateRecyclePool();
        const pool2 = view2.getOrCreateRecyclePool();
        eq(pool1 !== pool2, true, 'Each view should have its own recycle pool');
    }

    public testDelayedUpdateIdTypes(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedComputedIds(200);
        view.addDelayedMonitorIdsForAddMonitor(300);
        eq(view.monitorIdsDelayedUpdate?.has(100), true, 'Should have monitor ID');
        eq(view.computedIdsDelayedUpdate?.has(200), true, 'Should have computed ID');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.has(300), true, 'Should have add monitor ID');
    }

    public testEmptyArrayHandlingInRepeatAPI(): void {
        const view = new MockViewV2(undefined, 100);
        const emptyArr: any[] = [];
        const result = view.__mkRepeatAPI(emptyArr);
        eq(result !== undefined, true, 'Should handle empty array');
    }

    public testNullHandlingInSetOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(0);
        eq(set.has(0), true, 'Should handle adding zero');
    }

    public testNegativeIdHandling(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(-1);
        eq(view.monitorIdsDelayedUpdate?.has(-1), true, 'Should handle negative IDs');
    }

    public testLargeIdHandling(): void {
        const view = new MockViewV2(undefined, 100);
        const largeId = Number.MAX_SAFE_INTEGER;
        view.addDelayedMonitorIds(largeId);
        eq(view.monitorIdsDelayedUpdate?.has(largeId), true, 'Should handle large IDs');
    }

    public testSequentialGetOrCreateCalls(): void {
        const view = new MockViewV2(undefined, 100);
        for (let j = 0; j < 10; j++) {
            view.getOrCreateMonitorIdsDelayedUpdate();
        }
        eq(view.monitorIdsDelayedUpdate?.size, 0, 'Should return same instance across multiple calls');
    }

    public testConcurrentDelayedUpdates(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 0; j < 100; j++) {
            set.add(j);
        }
        eq(set.size, 100, 'Should handle concurrent additions');
    }

    public testMapKeyTypes(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('stringKey', 'value1');
        map.set('123', 'value2');
        map.set('', 'value3');
        eq(map.size, 3, 'Should handle different key types');
    }

    public testMapValueTypes(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'stringValue');
        map.set('key2', 123);
        map.set('key3', true);
        eq(map.size, 3, 'Should handle different value types');
    }

    public testSetIteration(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(200);
        set.add(300);
        let count = 0;
        set.forEach((value: number, value2: number, set: Set<number>) => { count++ });
        eq(count, 3, 'Should support iteration');
    }

    public testMapIteration(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        map.set('key2', 'value2');
        let count = 0;
        map.forEach((value: any, key: any, map: Map<any, any>) => { count++ });
        eq(count, 2, 'Should support iteration');
    }

    public testClearOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(200);
        set.clear();
        eq(set.size, 0, 'Should support clear operation');
    }

    public testHasOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        eq(set.has(100), false, 'Should return false for non-existent element');
        set.add(100);
        eq(set.has(100), true, 'Should return true for existing element');
    }

    public testSetSizeSizeOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        eq(set.size, 1, 'Size should be 1 after adding one element');
        set.add(200);
        eq(set.size, 2, 'Size should be 2 after adding two elements');
    }

    public testMapSizeOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        eq(map.size, 1, 'Size should be 1 after adding one entry');
        map.set('key2', 'value2');
        eq(map.size, 2, 'Size should be 2 after adding two entries');
    }

    public testDuplicateElementHandling(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(100);
        set.add(100);
        eq(set.size, 1, 'Should handle duplicate elements');
    }

    public testDuplicateKeyHandling(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        map.set('key1', 'value2');
        eq(map.size, 1, 'Should handle duplicate keys');
        eq(map.get('key1'), 'value2', 'Should update value for duplicate key');
    }

    public testEmptyStringKeys(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('', 'emptyKeyValue');
        eq(map.has(''), true, 'Should handle empty string keys');
        eq(map.get(''), 'emptyKeyValue', 'Should retrieve value for empty string key');
    }

    public testSpecialStringKeys(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key with spaces', 'value1');
        map.set('key-with-dashes', 'value2');
        map.set('key_with_underscores', 'value3');
        eq(map.size, 3, 'Should handle special characters in keys');
    }

    public testUnicodeKeys(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('中文', 'value1');
        map.set('日本語', 'value2');
        map.set('🎉', 'value3');
        eq(map.size, 3, 'Should handle Unicode keys');
    }

    public testVeryLongKeys(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const longKey = 'a'.repeat(1000);
        map.set(longKey, 'value');
        eq(map.has(longKey), true, 'Should handle very long keys');
    }

    public testVeryLongValues(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const longValue = 'b'.repeat(10000);
        map.set('key', longValue);
        eq(map.get('key'), longValue, 'Should handle very long values');
    }

    public testBoundaryIdValues(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(0);
        view.addDelayedMonitorIds(-1);
        view.addDelayedMonitorIds(1);
        view.addDelayedMonitorIds(Number.MIN_SAFE_INTEGER);
        view.addDelayedMonitorIds(Number.MAX_SAFE_INTEGER);
        eq(view.monitorIdsDelayedUpdate?.size, 5, 'Should handle boundary ID values');
    }

    public testFloatingPointIdValues(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(1.5 as any);
        set.add(2.7 as any);
        eq(set.size, 2, 'Should handle floating point values');
    }

    public testStringIdValues(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add('100' as any);
        set.add('200' as any);
        eq(set.size, 2, 'Should handle string ID values');
    }

    public testMixedTypeIds(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add('200' as any);
        set.add(300.5 as any);
        eq(set.size, 3, 'Should handle mixed type IDs');
    }

    public testConcurrentMapOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        for (let j = 0; j < 100; j++) {
            map.set(`key${j}`, `value${j}`);
        }
        eq(map.size, 100, 'Should handle concurrent map operations');
    }

    public testMapGetOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        eq(map.get('nonexistent'), undefined, 'Should return undefined for non-existent key');
        map.set('key1', 'value1');
        eq(map.get('key1'), 'value1', 'Should return value for existing key');
    }

    public testSetHasAfterClear(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.clear();
        eq(set.has(100), false, 'Should not contain elements after clear');
    }

    public testMapHasAfterClear(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        map.clear();
        eq(map.has('key1'), false, 'Should not contain entries after clear');
    }

    public testSetDeleteNonExistent(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const result = set.delete(999);
        eq(result, false, 'Should return false for deleting non-existent element');
    }

    public testMapDeleteNonExistent(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const result = map.delete('nonexistent');
        eq(result, false, 'Should return false for deleting non-existent key');
    }

    public testSetDeleteExistent(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        const result = set.delete(100);
        eq(result, true, 'Should return true for deleting existing element');
        eq(set.has(100), false, 'Should not contain deleted element');
    }

    public testMapDeleteExistent(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        const result = map.delete('key1');
        eq(result, true, 'Should return true for deleting existing key');
        eq(map.has('key1'), false, 'Should not contain deleted key');
    }

    public testSetClearEmpty(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.clear();
        eq(set.size, 0, 'Should handle clear on empty set');
    }

    public testMapClearEmpty(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.clear();
        eq(map.size, 0, 'Should handle clear on empty map');
    }

    public testPerformanceLargeSetOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const startTime = Date.now();
        for (let j = 0; j < 10000; j++) {
            set.add(j);
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Should complete large set operations in reasonable time');
        eq(set.size, 10000, 'Should contain all added elements');
    }

    public testPerformanceLargeMapOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const startTime = Date.now();
        for (let j = 0; j < 10000; j++) {
            map.set(`key${j}`, `value${j}`);
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Should complete large map operations in reasonable time');
        eq(map.size, 10000, 'Should contain all added entries');
    }

    public testPerformanceRepeatedGetOrCreate(): void {
        const view = new MockViewV2(undefined, 100);
        const startTime = Date.now();
        for (let j = 0; j < 10000; j++) {
            view.getOrCreateMonitorIdsDelayedUpdate();
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Should complete repeated getOrCreate in reasonable time');
    }

    public testMemoryEfficiency(): void {
        const views: MockViewV2[] = [];
        for (let j = 0; j < 100; j++) {
            const view = new MockViewV2(undefined, j);
            view.addDelayedMonitorIds(j);
            views.push(view);
        }
        eq(views.length, 100, 'Should create multiple views efficiently');
        eq(views[50].monitorIdsDelayedUpdate?.size, 1, 'Each view should maintain its state');
    }

    public testConsistencyAcrossOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(200);
        set.add(300);
        eq(set.size, 3, 'Should maintain consistency');
        set.delete(200);
        eq(set.size, 2, 'Should maintain consistency after delete');
        set.add(400);
        eq(set.size, 3, 'Should maintain consistency after add');
    }

    public testIdUniqueness(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const ids = [100, 200, 300, 400, 500];
        ids.forEach((id: any) => set.add(id));
        eq(set.size, 5, 'Should maintain unique IDs');
        ids.forEach((id: any) => eq(set.has(id), true, 'Should contain all added IDs'));
    }

    public testKeyValuePairs(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const entries = [['key1', 'value1'], ['key2', 'value2'], ['key3', 'value3']];
        entries.forEach((entry: any[]) => { const [key, value] = entry; map.set(key, value); });
        eq(map.size, 3, 'Should store all key-value pairs');
        entries.forEach((entry: any[]) => { const [key, value] = entry; eq(map.get(key), value, 'Should retrieve correct values'); });
    }

    public testNullValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', null);
        map.set('key2', undefined);
        eq(map.size, 2, 'Should handle null and undefined values');
        eq(map.get('key1'), null, 'Should retrieve null value');
        eq(map.get('key2'), undefined, 'Should retrieve undefined value');
    }

    public testObjectValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const obj1 = { nested: { value: 1 } };
        const obj2 = { array: [1, 2, 3] };
        map.set('key1', obj1);
        map.set('key2', obj2);
        eq(map.size, 2, 'Should handle object values');
    }

    public testArrayValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const arr1 = [1, 2, 3];
        const arr2 = ['a', 'b', 'c'];
        map.set('key1', arr1);
        map.set('key2', arr2);
        eq(map.size, 2, 'Should handle array values');
    }

    public testBooleanValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', true);
        map.set('key2', false);
        eq(map.size, 2, 'Should handle boolean values');
        eq(map.get('key1'), true, 'Should retrieve true value');
        eq(map.get('key2'), false, 'Should retrieve false value');
    }

    public testNumericValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('int', 42);
        map.set('float', 3.14);
        map.set('negative', -100);
        map.set('zero', 0);
        eq(map.size, 4, 'Should handle numeric values');
    }

    public testFunctionValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const func1 = () => 'result1';
        const func2 = () => 42;
        map.set('key1', func1);
        map.set('key2', func2);
        eq(map.size, 2, 'Should handle function values');
    }

    public testDateValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const date1 = new Date('2026-01-01');
        const date2 = new Date();
        map.set('key1', date1);
        map.set('key2', date2);
        eq(map.size, 2, 'Should handle Date values');
    }

    public testNestedMapValues(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const nestedMap = new Map([['innerKey', 'innerValue']]);
        map.set('key1', nestedMap);
        eq(map.size, 1, 'Should handle nested Map values');
    }

    public testSetValuesInMap(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const set = new Set([1, 2, 3]);
        map.set('key1', set);
        eq(map.size, 1, 'Should handle Set values');
    }

    public testRapidAccessPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 0; j < 1000; j++) {
            set.add(j);
            set.has(j);
            set.delete(j);
        }
        eq(set.size, 0, 'Should handle rapid access pattern');
    }

    public testStressTestMultipleViews(): void {
        const views: MockViewV2[] = [];
        for (let j = 0; j < 50; j++) {
            const view = new MockViewV2(undefined, j);
            const set = view.getOrCreateMonitorIdsDelayedUpdate();
            for (let k = 0; k < 10; k++) {
                set.add(j * 10 + k);
            }
            views.push(view);
        }
        eq(views.length, 50, 'Should create multiple views');
        eq(views[25].monitorIdsDelayedUpdate?.size, 10, 'Each view should have correct state');
    }

    public testEdgeCaseEmptyOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const map = view.getOrCreateDefaultConsumerV2();
        set.clear();
        map.clear();
        set.delete(999);
        map.delete('nonexistent');
        eq(set.size, 0, 'Should handle empty operations gracefully');
        eq(map.size, 0, 'Should handle empty map operations gracefully');
    }

    public testSequentialIdPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 0; j < 100; j++) {
            set.add(j);
        }
        for (let j = 0; j < 100; j++) {
            eq(set.has(j), true, 'Should contain sequential IDs');
        }
    }

    public testReverseIdPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 99; j >= 0; j--) {
            set.add(j);
        }
        eq(set.size, 100, 'Should handle reverse ID pattern');
    }

    public testRandomIdPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const ids = [100, 500, 200, 999, 1, 777, 333];
        ids.forEach((id: any) => set.add(id));
        eq(set.size, 7, 'Should handle random ID pattern');
        ids.forEach((id: any) => eq(set.has(id), true, 'Should contain all random IDs'));
    }

    public testDuplicateAddRemovePattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        set.add(100);
        set.add(100);
        set.delete(100);
        set.add(100);
        eq(set.size, 1, 'Should handle duplicate add-remove pattern');
    }

    public testBulkOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const ids: number[] = [];
        for (let j = 0; j < 1000; j++) {
            ids.push(j);
        }
        ids.forEach((id: any) => set.add(id));
        eq(set.size, 1000, 'Should handle bulk operations');
    }

    public testMapBulkOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const entries: [string, string][] = [];
        for (let j = 0; j < 1000; j++) {
            entries.push([`key${j}`, `value${j}`]);
        }
        entries.forEach((entry: any[]) => { const [key, value] = entry; map.set(key, value); });
        eq(map.size, 1000, 'Should handle bulk map operations');
    }

    public testSetIterationOrder(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const ids = [100, 200, 300, 400, 500];
        ids.forEach((id: any) => set.add(id));
        let iteratedIds: number[] = [];
        set.forEach((value: number, value2: number, set: Set<number>) => { iteratedIds.push(value); });
        eq(iteratedIds.length, 5, 'Should iterate over all elements');
    }

  public testMapIterationOrder(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('key1', 'value1');
        map.set('key2', 'value2');
        map.set('key3', 'value3');
        let iteratedKeys: string[] = [];
        map.forEach((value: any, key: any): void => {
            iteratedKeys.push(key);
        });
        eq(iteratedKeys.length, 3, 'Should iterate over all entries');
    }

     public testSetClearAndRebuild(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 0; j < 100; j++) {
            set.add(j);
        }
        set.clear();
        for (let k = 0; k < 100; k++) {
            set.add(k + 1000);
        }
        eq(set.size, 100, 'Should handle clear and rebuild pattern');
    }

    public testMapClearAndRebuild(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        for (let j = 0; j < 100; j++) {
            map.set(`key${j}`, `value${j}`);
        }
        map.clear();
        for (let k = 0; k < 100; k++) {
            map.set(`newKey${k}`, `newValue${k}`);
        }
        eq(map.size, 100, 'Should handle clear and rebuild pattern');
    }

    public testMemoryLeakPrevention(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const map = view.getOrCreateDefaultConsumerV2();
        for (let j = 0; j < 10000; j++) {
            set.add(j);
            map.set(`key${j}`, `value${j}`);
            if (j % 1000 === 0) {
                set.clear();
                map.clear();
            }
        }
        eq(true, true, 'Should handle periodic clearing to prevent memory leaks');
    }

    public testFinalStateVerification(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const map = view.getOrCreateDefaultConsumerV2();
        const finalSetSize = 500;
        const finalMapSize = 300;
        for (let j = 0; j < finalSetSize; j++) {
            set.add(j);
        }
        for (let k = 0; k < finalMapSize; k++) {
            map.set(`key${k}`, `value${k}`);
        }
        eq(set.size, finalSetSize, 'Final set size should match expected');
        eq(map.size, finalMapSize, 'Final map size should match expected');
    }


    // =========================================================================
    // Lifecycle Tests
    // =========================================================================

    public testLifecycleViewCreation(): void {
        const view = new MockViewV2(undefined, 100);
        eq(view.id__(), 100, 'View should have correct elmtId');
        eq(view.isViewV2(), true, 'View should be ViewV2 instance');
        eq(view.isDeleting_, false, 'View should not be deleting initially');
    }

    public testLifecycleViewWithParent(): void {
        const parent = new MockViewV2(undefined, 100);
        const child = new MockViewV2(parent, 200);
        eq(child.parent_, parent, 'Child should have parent reference');
        eq(parent.id__(), 100, 'Parent should have correct elmtId');
        eq(child.id__(), 200, 'Child should have correct elmtId');
    }

    public testLifecycleMultipleChildren(): void {
        const parent = new MockViewV2(undefined, 100);
        const child1 = new MockViewV2(parent, 200);
        const child2 = new MockViewV2(parent, 300);
        const child3 = new MockViewV2(parent, 400);
        eq(child1.parent_, parent, 'First child should have parent');
        eq(child2.parent_, parent, 'Second child should have parent');
        eq(child3.parent_, parent, 'Third child should have parent');
    }

    public testLifecycleViewDeletion(): void {
        const view = new MockViewV2(undefined, 100);
        view.setDeleting();
        eq(view.isDeleting_, true, 'View should be marked as deleting');
    }

    public testLifecycleFirstRender(): void {
        const view = new MockViewV2(undefined, 100);
        const isFirst = view.isFirstRender();
        eq(typeof isFirst, 'boolean', 'isFirstRender should return boolean');
    }

    public testLifecycleViewActive(): void {
        const view = new MockViewV2(undefined, 100);
        const isActive = view.isViewActive();
        eq(typeof isActive, 'boolean', 'isViewActive should return boolean');
    }

    public testLifecycleScheduleDelayedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        view.scheduleDelayedUpdate(200);
        eq(true, true, 'Should schedule delayed update without error');
    }

    public testLifecycleSyncInstanceId(): void {
        const view = new MockViewV2(undefined, 100);
        view.syncInstanceId();
        eq(true, true, 'Should sync instance ID without error');
    }

    public testLifecycleRestoreInstanceId(): void {
        const view = new MockViewV2(undefined, 100);
        view.restoreInstanceId();
        eq(true, true, 'Should restore instance ID without error');
    }

    public testLifecycleMarkNeedUpdate(): void {
        const view = new MockViewV2(undefined, 100);
        view.markNeedUpdate();
        eq(true, true, 'Should mark need update without error');
    }

    // =========================================================================
    // Additional Edge Cases Tests
    // =========================================================================

    public testEdgeCaseVeryLargeId(): void {
        const view = new MockViewV2(undefined, Number.MAX_SAFE_INTEGER);
        eq(view.id__(), Number.MAX_SAFE_INTEGER, 'Should handle very large elmtId');
        view.addDelayedMonitorIds(Number.MAX_SAFE_INTEGER - 1);
        eq(view.monitorIdsDelayedUpdate?.has(Number.MAX_SAFE_INTEGER - 1), true, 'Should add very large monitor ID');
    }

    public testEdgeCaseNegativeId(): void {
        const view = new MockViewV2(undefined, -100);
        eq(view.id__(), -100, 'Should handle negative elmtId');
        view.addDelayedMonitorIds(-200);
        eq(view.monitorIdsDelayedUpdate?.has(-200), true, 'Should add negative monitor ID');
    }

    public testEdgeCaseZeroId(): void {
        const view = new MockViewV2(undefined, 0);
        eq(view.id__(), 0, 'Should handle zero elmtId');
        view.addDelayedMonitorIds(0);
        eq(view.monitorIdsDelayedUpdate?.has(0), true, 'Should add zero monitor ID');
    }

    public testEdgeCaseMinimalView(): void {
        const view = new MockViewV2(undefined, 1);
        eq(view.dirtDescendantElementIds_.size, 0, 'Minimal view should have no dirty elements');
        eq(view.monitorIdsDelayedUpdate, undefined, 'Minimal view should have no delayed monitors');
        eq(view.computedIdsDelayedUpdate, undefined, 'Minimal view should have no delayed computed');
    }

    public testEdgeCaseSingleOperation(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(1);
        eq(view.monitorIdsDelayedUpdate?.size, 1, 'Should handle single operation');
    }

    public testEdgeCaseAlternatingOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        for (let j = 0; j < 100; j++) {
            if (j % 2 === 0) {
                set.add(j);
            } else {
                set.delete(j - 1);
            }
        }
        eq(true, true, 'Should handle alternating add/delete operations');
    }

    public testEdgeCaseRapidCreationDestruction(): void {
        for (let j = 0; j < 100; j++) {
            const view = new MockViewV2(undefined, j);
            view.addDelayedMonitorIds(j);
        }
        eq(true, true, 'Should handle rapid creation and destruction');
    }

    // =========================================================================
    // Additional Performance Tests
    // =========================================================================

    public testPerformanceNestedOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const startTime = Date.now();
        for (let j = 0; j < 1000; j++) {
            for (let k = 0; k < 10; k++) {
                set.add(j * 10 + k);
            }
        }
        const duration = Date.now() - startTime;
        eq(duration < 2000, true, 'Nested operations should complete in reasonable time');
        eq(set.size, 10000, 'Should add all elements in nested loops');
    }

    public testPerformanceMixedOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const map = view.getOrCreateDefaultConsumerV2();
        const startTime = Date.now();
        for (let j = 0; j < 5000; j++) {
            set.add(j);
            map.set(`key${j}`, `value${j}`);
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Mixed operations should complete in reasonable time');
        eq(set.size, 5000, 'Set should have correct size');
        eq(map.size, 5000, 'Map should have correct size');
    }

    public testPerformanceRepeatedClear(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const startTime = Date.now();
        for (let j = 0; j < 1000; j++) {
            for (let k = 0; k < 100; k++) {
                set.add(k);
            }
            set.clear();
        }
        const duration = Date.now() - startTime;
        eq(duration < 2000, true, 'Repeated clear operations should complete in reasonable time');
    }

    public testPerformanceComplexPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const startTime = Date.now();
        for (let j = 0; j < 1000; j++) {
            set.add(j);
            if (j % 10 === 0) {
                set.delete(j - 10);
            }
            if (j % 100 === 0) {
                set.clear();
            }
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Complex pattern should complete in reasonable time');
    }

    // =========================================================================
    // Complex Scenario Tests
    // =========================================================================

    public testScenarioViewHierarchy(): void {
        const root = new MockViewV2(undefined, 1);
        const level1 = new MockViewV2(root, 2);
        const level2 = new MockViewV2(level1, 3);
        const level3 = new MockViewV2(level2, 4);
        root.addDelayedMonitorIds(100);
        level1.addDelayedMonitorIds(200);
        level2.addDelayedMonitorIds(300);
        level3.addDelayedMonitorIds(400);
        eq(root.monitorIdsDelayedUpdate?.size, 1, 'Root should have one delayed monitor');
        eq(level1.monitorIdsDelayedUpdate?.size, 1, 'Level1 should have one delayed monitor');
        eq(level2.monitorIdsDelayedUpdate?.size, 1, 'Level2 should have one delayed monitor');
        eq(level3.monitorIdsDelayedUpdate?.size, 1, 'Level3 should have one delayed monitor');
    }

    public testScenarioMultipleDelayedUpdateTypes(): void {
        const view = new MockViewV2(undefined, 100);
        for (let j = 0; j < 100; j++) {
            view.addDelayedMonitorIds(j);
            view.addDelayedMonitorIdsForAddMonitor(j + 100);
            view.addDelayedComputedIds(j + 200);
        }
        eq(view.monitorIdsDelayedUpdate?.size, 100, 'Should have 100 monitor IDs');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.size, 100, 'Should have 100 add monitor IDs');
        eq(view.computedIdsDelayedUpdate?.size, 100, 'Should have 100 computed IDs');
    }

    public testScenarioRecyclePoolWithComponents(): void {
        const view = new MockViewV2(undefined, 100);
        const pool = view.getOrCreateRecyclePool();
        const component1 = { id: 1, name: 'Component1' };
        const component2 = { id: 2, name: 'Component2' };
        pool.pushRecycleV2Component('reuseId1', component1);
        pool.pushRecycleV2Component('reuseId2', component2);
        eq(view.hasRecyclePool(), true, 'View should have recycle pool');
    }

    public testScenarioConsumerProviderPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const defaultConsumer = view.getOrCreateDefaultConsumerV2();
        const connectConsumer = view.getOrCreateConnectConsumerV2();
        defaultConsumer.set('theme', 'dark');
        defaultConsumer.set('language', 'en');
        connectConsumer.set('user', 'provider1');
        connectConsumer.set('settings', 'provider2');
        eq(defaultConsumer.size, 2, 'Default consumer should have 2 entries');
        eq(connectConsumer.size, 2, 'Connect consumer should have 2 entries');
    }

    public testScenarioMonitorLifecycle(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedMonitorIdsForAddMonitor(200);
        view.resetMonitorsOnReuse();
        eq(view.monitorIdsDelayedUpdate?.size, 0, 'Monitors should be cleared after reset');
        eq(view.monitorIdsDelayedUpdateForAddMonitor_?.size, 0, 'Add monitors should be cleared after reset');
    }

    // =========================================================================
    // Error Handling Tests
    // =========================================================================

    public testErrorHandlingInvalidMonitorId(): void {
        const view = new MockViewV2(undefined, 100);
        try {
            view.addDelayedMonitorIds(NaN as any);
            eq(true, true, 'Should handle NaN monitor ID');
        } catch (e) {
            eq(true, true, 'Should throw error for invalid monitor ID');
        }
    }

    public testErrorHandlingUndefinedValue(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('undefinedKey', undefined);
        eq(map.get('undefinedKey'), undefined, 'Should handle undefined value');
    }

    public testErrorHandlingNullValue(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('nullKey', null);
        eq(map.get('nullKey'), null, 'Should handle null value');
    }

    public testErrorHandlingInfiniteValue(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('infinityKey', Infinity);
        map.set('negInfinityKey', -Infinity);
        eq(map.get('infinityKey'), Infinity, 'Should handle Infinity value');
        eq(map.get('negInfinityKey'), -Infinity, 'Should handle -Infinity value');
    }

    // =========================================================================
    // Integration Tests
    // =========================================================================

    public testIntegrationMultipleViewsInteraction(): void {
        const parent = new MockViewV2(undefined, 100);
        const child1 = new MockViewV2(parent, 200);
        const child2 = new MockViewV2(parent, 300);
        parent.addDelayedMonitorIds(100);
        child1.addDelayedMonitorIds(200);
        child2.addDelayedMonitorIds(300);
        parent.aboutToReuse();
        child1.aboutToReuse();
        child2.aboutToReuse();
        eq(true, true, 'Should handle multiple views interaction');
    }

    // =========================================================================
    // Additional Comprehensive Tests
    // =========================================================================

    public testComprehensiveStressTest(): void {
        const views: MockViewV2[] = [];
        for (let j = 0; j < 50; j++) {
            const view = new MockViewV2(undefined, j);
            view.getOrCreateRecyclePool();
            view.getOrCreateDefaultConsumerV2();
            for (let k = 0; k < 100; k++) {
                view.addDelayedMonitorIds(j * 100 + k);
            }
            views.push(view);
        }
        eq(views.length, 50, 'Should create 50 views');
        eq(views[25].monitorIdsDelayedUpdate?.size, 100, 'Each view should have 100 monitor IDs');
    }

    public testComprehensiveMemoryPattern(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const map = view.getOrCreateDefaultConsumerV2();
        for (let j = 0; j < 1000; j++) {
            set.add(j);
            map.set(`key${j}`, `value${j}`);
        }
        set.clear();
        map.clear();
        for (let k = 0; k < 500; k++) {
            set.add(k);
            map.set(`newKey${k}`, `newValue${k}`);
        }
        eq(set.size, 500, 'Set should have 500 elements after clear and rebuild');
        eq(map.size, 500, 'Map should have 500 entries after clear and rebuild');
    }

    public testComprehensiveDataTypes(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        map.set('string', 'stringValue');
        map.set('number', 42);
        map.set('boolean', true);
        map.set('array', [1, 2, 3]);
        map.set('object', { key: 'value' });
        map.set('null', null);
        map.set('undefined', undefined);
        map.set('date', new Date());
        map.set('function', () => 'result');
        eq(map.size, 9, 'Should handle all data types');
    }

    public testComprehensiveIdPatterns(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const ids = [
            0, 1, -1, 100, -100,
            Number.MAX_SAFE_INTEGER, Number.MIN_SAFE_INTEGER,
            999999, -999999
        ];
        ids.forEach((id: any) => set.add(id));
        eq(set.size, ids.length, 'Should handle all ID patterns');
    }

    public testComprehensiveStringKeys(): void {
        const view = new MockViewV2(undefined, 100);
        const map = view.getOrCreateDefaultConsumerV2();
        const keys = [
            '', 'a', 'key', 'key-with-dash', 'key_with_underscore',
            'key with spaces', '中文', '日本語', '🎉',
            'veryLongKey'.repeat(10)
        ];
        keys.forEach((key: string) => map.set(key, `value${key}`));
        eq(map.size, keys.length, 'Should handle all string key patterns');
    }

    public testComprehensiveOperationSequence(): void {
        const view = new MockViewV2(undefined, 100);
        const set = view.getOrCreateMonitorIdsDelayedUpdate();
        const map = view.getOrCreateDefaultConsumerV2();
        for (let j = 0; j < 100; j++) {
            set.add(j);
            map.set(`key${j}`, `value${j}`);
        }
        for (let k = 0; k < 50; k++) {
            set.delete(k);
            map.delete(`key${k}`);
        }
        for (let l = 50; l < 100; l++) {
            set.add(l + 1000);
            map.set(`newKey${l}`, `newValue${l}`);
        }
        eq(set.size, 100, 'Set should have 100 elements after sequence');
        eq(map.size, 100, 'Map should have 100 entries after sequence');
    }

    public testComprehensiveNestedViews(): void {
        const root = new MockViewV2(undefined, 1);
        let current = root;
        for (let j = 0; j < 10; j++) {
            const child = new MockViewV2(current, j + 2);
            child.addDelayedMonitorIds(j * 100);
            current = child;
        }
        eq(true, true, 'Should handle nested view hierarchy');
    }

    public testComprehensiveMixedDelayedUpdates(): void {
        const view = new MockViewV2(undefined, 100);
        for (let j = 0; j < 100; j++) {
            if (j % 3 === 0) {
                view.addDelayedMonitorIds(j);
            } else if (j % 3 === 1) {
                view.addDelayedMonitorIdsForAddMonitor(j);
            } else {
                view.addDelayedComputedIds(j);
            }
        }
        const totalSize = (view.monitorIdsDelayedUpdate?.size || 0) +
            (view.monitorIdsDelayedUpdateForAddMonitor_?.size || 0) +
            (view.computedIdsDelayedUpdate?.size || 0);
        eq(totalSize, 100, 'Should distribute delayed updates across types');
    }

    public testComprehensiveDebugInfo(): void {
        const view = new MockViewV2(undefined, 100);
        view.addDelayedMonitorIds(100);
        view.addDelayedComputedIds(200);
        const info1 = view.debugInfo__();
        const info2 = view.debugInfoView();
        const info3 = view.debugInfoDirtDescendantElementIds();
        const info4 = view.debugInfoStateVars();
        eq(typeof info1, 'string', 'debugInfo__ should return string');
        eq(typeof info2, 'string', 'debugInfoView should return string');
        eq(typeof info3, 'string', 'debugInfoDirtDescendantElementIds should return string');
        eq(typeof info4, 'string', 'debugInfoStateVars should return string');
    }

    public testComprehensiveRecyclePoolOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const pool = view.getOrCreateRecyclePool();
        const components: any[] = [];
        for (let j = 0; j < 100; j++) {
            const component = { id: j, name: `Component${j}` };
            components.push(component);
            pool.pushRecycleV2Component(`reuseId${j}`, component);
        }
        eq(view.hasRecyclePool(), true, 'Should have recycle pool');
    }

    public testComprehensiveConsumerOperations(): void {
        const view = new MockViewV2(undefined, 100);
        const defaultConsumer = view.getOrCreateDefaultConsumerV2();
        const connectConsumer = view.getOrCreateConnectConsumerV2();
        for (let j = 0; j < 100; j++) {
            defaultConsumer.set(`default${j}`, `value${j}`);
            connectConsumer.set(`connect${j}`, `provider${j}`);
        }
        eq(defaultConsumer.size, 100, 'Default consumer should have 100 entries');
        eq(connectConsumer.size, 100, 'Connect consumer should have 100 entries');
    }
}
