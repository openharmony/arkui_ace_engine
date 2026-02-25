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

/**
 * ark_node_types.d.ts
 *
 * This file contains type definitions from state_mgmt.d.ts that are
 * actually used by ark_node/src directory. It provides a minimal set
 * of types needed for ark_node functionality, reducing the dependency
 * on the large state_mgmt.d.ts file.
 */

// ============================================================================
// Built-in Types (ES2020)
// ============================================================================

declare class WeakRef<T extends object> {
    constructor(o: T);
    deref(): T | undefined;
}

// ============================================================================
// Core Types
// ============================================================================

type PropertyInfo = string;

type UpdateFunc = (elmtId: number, isFirstRender: boolean, param?: Object) => void;

type UIClassObject = {
    prototype: Object;
    pop?: () => void;
};

type RecycleUpdateFunc = (elmtId: number, isFirstRender: boolean, recycleNode: ViewPU) => void;

type PrebuildFunc = () => void;

type ProfileRecursionCounter = {
    total: number;
};

type ExtraInfo = {
    page: string;
    line: number;
    col: number;
};

// ============================================================================
// Error Handling
// ============================================================================

declare class BusinessError extends Error {
    code: number | string;
    constructor(code: number | string, message: string);
}

// ============================================================================
// UIContext and Module System
// ============================================================================

interface InternalModuleMap {
  util: ArkTsUtil;
}

declare interface ArkTsUtil {
    getHash(object: object): number;
}

declare class UIContext {
  instanceId_: number;
  isAvailable(): boolean;
  getId(): number;
}

// ============================================================================
// Property System
// ============================================================================

interface AbstractProperty<T> {
    get(): T;
    set(value: T): void;
}

declare abstract class SubscribedAbstractProperty<T> {
    abstract get(): T;
    abstract set(newValue: T): void;
    abstract aboutToBeDeleted(): void;
}

declare abstract class ObservedPropertyAbstract<T> extends SubscribedAbstractProperty<T> implements AbstractProperty<T> {
    protected subscribers__?: Set<number>;
    private id_;
    protected info_?: PropertyInfo;
    protected isFake_: boolean;
    constructor(subscribeMe?: IPropertySubscriber, info?: PropertyInfo);
    get subscribers_(): Set<number> | undefined;
    getOrCreateSubscribers(): Set<number>;
    aboutToBeDeleted(): void;
    id__(): number;
    info(): PropertyInfo;
    setInfo(propName: PropertyInfo): void;
    __isFake_ObservedPropertyAbstract_Internal(): boolean;
    __setIsFake_ObservedPropertyAbstract_Internal(isFake: boolean): void;
    getUnmonitored(): T;
    updateElmtId(oldElmtId: number, newElmtId: number): void;
    subscribeMe(subscriber: ISinglePropertyChangeSubscriber<T>): void;
    unlinkSuscriber(subscriberId: number): void;
    addSubscriber(subscriber: ISinglePropertyChangeSubscriber<T>): void;
    removeSubscriber(subscriber: IPropertySubscriber, id?: number): void;
    protected notifyHasChanged(newValue: T): void;
    protected notifyPropertyRead(): void;
    numberOfSubscrbers(): number;
}

// ============================================================================
// ConfigureStateMgmt
// ============================================================================

declare class ConfigureStateMgmt {
    private static readonly HOW_TO_SAY;
    private static instance__?;
    private v2ObservedTrackInUse_;
    private puObservedTrackInUse_;
    static get instance(): ConfigureStateMgmt;
    usingV2ObservedTrack(feature: string, contextOfUse?: string): void;
    usingPUObservedTrack(feature: string, contextOfUse?: string): void;
    needsV2Observe(): boolean;
}

// ============================================================================
// stateMgmtProfiler
// ============================================================================

declare class stateMgmtProfiler {
    private static instance;
    static begin(blockName: string): void;
    static end(): void;
    static report(): void;
    static clear(): void;
    static init(instance: stateMgmtProfiler): void;
}

// ============================================================================
// UpdateFuncRecord and UpdateFuncsByElmtId
// ============================================================================

declare class UpdateFuncRecord {
    private updateFunc_: UpdateFunc;
    private classObject_: UIClassObject;
    private node_?: ArkComponent;
    private isPending_: boolean;
    private isChanged_: boolean;
    constructor(params: {
        updateFunc: UpdateFunc;
        classObject?: UIClassObject;
        node?: ArkComponent;
    });
    getUpdateFunc(): UpdateFunc | undefined;
    getComponentClass(): UIClassObject | undefined;
    getComponentName(): string;
    getPopFunc(): () => void;
    getNode(): ArkComponent | undefined;
    setNode(node: ArkComponent | undefined): void;
    isPending(): boolean;
    setPending(isPending: boolean): void;
    isChanged(): boolean;
    setIsChanged(isChanged: boolean): void;
}

declare class UpdateFuncsByElmtId {
    private map_;
    delete(elmtId: number): boolean;
    set(elmtId: number, params: UpdateFunc | {
        updateFunc: UpdateFunc;
        classObject?: UIClassObject;
        node?: ArkComponent;
    }): void;
    get(elmtId: number): UpdateFuncRecord | undefined;
    has(elmtId: number): boolean;
    keys(): IterableIterator<number>;
    clear(): void;
    get size(): number;
    forEach(callbackfn: (value: UpdateFuncRecord, key: number, map: Map<number, UpdateFuncRecord>) => void): void;
    debugInfoRegisteredElmtIds(): string;
    debugInfoElmtId(elmtId: number): string;
}

// ============================================================================
// IView and IPropertySubscriber
// ============================================================================

interface IPropertySubscriber {
    id__(): number;
    aboutToBeDeleted(owningView?: IPropertySubscriber): void;
}

interface ISinglePropertyChangeSubscriber<T> extends IPropertySubscriber {
    hasChanged(newValue: T): void;
}

interface IMultiPropertiesChangeSubscriber extends IPropertySubscriber {
    propertyHasChanged(info?: PropertyInfo): void;
}

interface IViewPropertiesChangeSubscriber extends IPropertySubscriber {
    viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void;
}

interface IView extends IPropertySubscriber {
    id__(): number;
    debugInfo__(): string;
    getCardId(): number;
    getParent(): IView | undefined;
    setParent(p: IView): void;
    setParentBuilderNode__(node: ViewBuildNodeBase): void;
    addChild(c: IView): boolean;
    getChildById(elmtId: number): IView | undefined;
    removeChild(child: IView): boolean;
    findViewInHierarchy(id: number): ViewPU | ViewV2 | undefined;
    purgeDeleteElmtId(rmElmtId: number): boolean;
    initialRenderView(): void;
    forceCompleteRerender(deep: boolean): void;
    forceRerenderNode(elmtId: number): void;
    uiNodeNeedUpdateV2(elmtId: number): void;
    updateStateVarsOfChildByElmtId(elmtId: any, params: Object): void;
    aboutToBeDeleted(): void;
    aboutToReuseInternal?(param?: Object): void;
    aboutToRecycleInternal?(): void;
    isDeleting(): boolean;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;
    isCompFreezeAllowed(): boolean;
    setActiveInternal(newState: boolean, isReuse: boolean): void;
    findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;
    localStorage_: LocalStorage;
    debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
    debugInfoUpdateFuncByElmtIdInternal(counter: ProfileRecursionCounter, depth: number, recursive: boolean): string;
    debugInfoDirtDescendantElementIdsInternal(depth: number, recursive: boolean, counter: ProfileRecursionCounter): string;
    onGlobalThemeChanged(): void;
    __ClearAllRecyle__PUV2ViewBase__Internal(): void;
}

// ============================================================================
// LocalStorage
// ============================================================================

declare class NativeLocalStorage {
    protected storage_: Map<string, any>;
}

declare class InteropStorage extends Map<string, any> {
}

declare class LocalStorage extends NativeLocalStorage {
    protected storage_: Map<string, ObservedPropertyAbstract<any>>;
    _getOriginStorageByInterop_(): InteropStorage;
    _setOriginStorageByInterop_(value: Map<string, ObservedPropertyAbstract<any>>): void;
    private proxy?;
    getProxy(): Object | undefined;
    setProxy(proxy: Object): void;
    static getShared(): LocalStorage;
    constructor(initializingProperties?: Object);
}

// ============================================================================
// ViewBuildNodeBase
// ============================================================================

declare class ArkThemeScopeManager {
    onComponentCreateEnter(_componentName: string, elmtId: number, isFirstRender: boolean, view: ViewBuildNodeBase): void;
    onComponentCreateExit(elmtId: number): void;
}

declare abstract class ViewBuildNodeBase {
    protected isView_: boolean;
    protected childrenWeakrefMap_: Map<number, WeakRef<IView>>;
    protected builderNodeWeakrefMap__?: Map<number, WeakRef<ViewBuildNodeBase>>;
    protected updateFuncByElmtId: UpdateFuncsByElmtId;
    protected id_: number;
    protected shareLocalStorage_: LocalStorage;
    __parentViewBuildNode__: ViewBuildNodeBase;
    protected __enableBuilderNodeConsume__: boolean;
    protected elmtId2Repeat_: Map<number, RepeatAPI>;
    protected static arkThemeScopeManager: ArkThemeScopeManager | undefined;
    abstract ifElseBranchUpdateFunctionDirtyRetaken(): void;
    abstract forceCompleteRerender(deep: boolean): void;
    abstract forceRerenderNode(elmtId: number): void;
    abstract purgeDeleteElmtId(rmElmtId: number): boolean;
    abstract findProvidePU__(providePropName: string): ObservedPropertyAbstractPU<any> | undefined;
    constructor(isView: boolean);
    get builderNodeWeakrefMap_(): Map<number, WeakRef<ViewBuildNodeBase>> | undefined;
    getOrCreateBuilderNodeWeakrefMap(): Map<number, WeakRef<ViewBuildNodeBase>>;
    id__(): number;
    debugInfo__(): string;
    __isReactiveBuilderNode__ViewBuildNodeBase__Internal(): boolean;
    addChildBuilderNode(child: ViewBuildNodeBase): boolean;
    removeChildBuilderNode(elmtId: number): void;
    clearChildBuilderNode(): void;
    protected purgeDeletedElmtIds(): void;
    setShareLocalStorage(localStorage: LocalStorage): void;
    protected propagateToChildren(weakRefMap: Map<number, WeakRef<IView | ViewBuildNodeBase>> | undefined, active: boolean, isReuse: boolean): void;
}

// ============================================================================
// PUV2ViewBase
// ============================================================================

declare abstract class PUV2ViewBase extends ViewBuildNodeBase {
    protected static readonly inactiveComponents_: Set<string>;
    protected get isReusable_(): boolean;
    static readonly compareNumber: (a: number, b: number) => number;
    protected builderIdMap_: WeakMap<Object, number>;
    protected nextBuilderId_: number;
    protected currentlyRenderedElmtIdStack_: Array<number>;
    protected dirtDescendantElementIds_: Set<number>;
    protected dirtRetakenElementIds_: Set<number>;
    protected parent_: IView | undefined;
    static renderingPaused: boolean;
    protected activeCount_: number;
    protected isDeleting_: boolean;
    protected isCompFreezeAllowed_: boolean;
    protected static prebuildFuncQueues: Map<number, Array<PrebuildFunc>>;
    protected static propertyChangedFuncQueues: Map<number, Array<PrebuildFunc>>;
    __isBlockRecycleOrReuse__: boolean;
    protected __updatedInstanceId__?: number;
    isCompFreezeAllowed(): boolean;
}

// ============================================================================
// ViewPU
// ============================================================================

declare abstract class ViewPU extends PUV2ViewBase implements IViewPropertiesChangeSubscriber, IView {
    private isRenderInProgress;
    private isInitialRenderDone;
    private runReuse_;
    paramsGenerator_: () => Object;
    private watchedProps;
    private recycleManager_;
    hasBeenRecycled_: boolean;
    private preventRecursiveRecycle_;
    private delayRecycleNodeRerender;
    private delayRecycleNodeRerenderDeep;
    defaultConsume__?: Map<string, SynchedPropertyTwoWayPU<any>>;
    reconnectConsume__?: Map<string, SynchedPropertyTwoWayPU<any>>;
    protected providedVars__?: Map<string, ObservedPropertyAbstractPU<any>>;
    dirtyElementIdsNeedsUpdateSynchronously__?: Set<number>;
    protected localStoragebackStore_: LocalStorage;
    private ownObservedPropertiesStore__?;
    get providedVars_(): Map<string, ObservedPropertyAbstractPU<any>> | undefined;
    getOrCreateProvidedVars(): Map<string, ObservedPropertyAbstractPU<any>>;
    get dirtyElementIdsNeedsUpdateSynchronously_(): Set<number> | undefined;
    getOrCreateDirtyElementIdsNeedsUpdateSynchronously(): Set<number>;
    get defaultConsume_(): Map<string, SynchedPropertyTwoWayPU<any>> | undefined;
    getOrCreateDefaultConsume(): Map<string, SynchedPropertyTwoWayPU<any>>;
    get reconnectConsume_(): Map<string, SynchedPropertyTwoWayPU<any>> | undefined;
    getOrCreateReconnectConsume(): Map<string, SynchedPropertyTwoWayPU<any>>;
    get localStorage_(): LocalStorage;
    set localStorage_(instance: LocalStorage);
    protected get isViewV2(): boolean;
    aboutToReuseInternal(initialParams?: Object): void;
    aboutToRecycleInternal(): void;
    aboutToBeDeleted(owningView?: IPropertySubscriber): void;
    viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void;
    id__(): number;
    debugInfo__(): string;
    getCardId(): number;
    getParent(): IView | undefined;
    setParent(p: IView): void;
    setParentBuilderNode__(node: ViewBuildNodeBase): void;
    addChild(c: IView): boolean;
    getChildById(elmtId: number): IView | undefined;
    removeChild(child: IView): boolean;
    findViewInHierarchy(id: number): ViewPU | ViewV2 | undefined;
    purgeDeleteElmtId(rmElmtId: number): boolean;
    initialRenderView(): void;
    forceCompleteRerender(deep: boolean): void;
    forceRerenderNode(elmtId: number): void;
    uiNodeNeedUpdateV2(elmtId: number): void;
    updateStateVarsOfChildByElmtId(elmtId: any, params: Object): void;
    isDeleting(): boolean;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;
    isCompFreezeAllowed(): boolean;
    setActiveInternal(newState: boolean, isReuse: boolean): void;
    findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;
    debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
    debugInfoUpdateFuncByElmtIdInternal(counter: ProfileRecursionCounter, depth: number, recursive: boolean): string;
    debugInfoDirtDescendantElementIdsInternal(depth: number, recursive: boolean, counter: ProfileRecursionCounter): string;
    onGlobalThemeChanged(): void;
    __ClearAllRecyle__PUV2ViewBase__Internal(): void;
}

// ============================================================================
// ObservedPropertyAbstractPU
// ============================================================================

declare abstract class ObservedPropertyAbstractPU<T> extends ObservedPropertyAbstract<T> implements ISinglePropertyChangeSubscriber<T>, IMultiPropertiesChangeSubscriber {
    static readonly DelayedNotifyChangesEnum: {
        new (): {};
        readonly do_not_delay: 0;
        readonly delay_none_pending: 1;
        readonly delay_notification_pending: 2;
    };
    private owningView_;
    changeNotificationIsOngoing_: boolean;
    protected subscriberRefs_?: Set<IPropertySubscriber>;
    private delayedNotification_;
    protected shouldInstallTrackedObjectReadCb: boolean;
    private dependentElmtIdsByProperty__;
    private get dependentElmtIdsByProperty_();
    private proxy?;
    getProxy(): Object | undefined;
    hasChanged(newValue: T): void;
    hasChangedSynceToPropsAreDone(): void;
    propertyHasChanged(info?: PropertyInfo): void;
    propertyRead(info?: PropertyInfo): void;
    markDependentElmtIdDirty(elmtId: number): void;
    addSubscriber(subscriber: IPropertySubscriber): void;
    removeSubscriber(subscriber: IPropertySubscriber, id?: number): void;
    isPropertyUnlinked(): boolean;
    unlinkSuscriber(subscriberId: number): void;
}

// ============================================================================
// SynchedPropertyTwoWayPU
// ============================================================================

declare class SynchedPropertyTwoWayPU<C> extends ObservedPropertyAbstractPU<C> {
    get(): C;
    set(newValue: C): void;
}

// ============================================================================
// UINodeRegisterProxy
// ============================================================================

declare class UINodeRegisterProxy {
    static readonly notRecordingDependencies: number;
    static obtainDeletedElmtIds(): void;
    static unregisterElmtIdsFromIViews(): void;
    static unregisterRemovedElmtsFromViewPUs(removedElements: Array<number>): void;
    private populateRemoveElementInfo;
    private obtainDeletedElmtIds;
    unregisterElmtIdsFromIViews(): void;
    static GetView(elmtId: number): ViewBuildNodeBase | undefined;
    static GetViewBuildNodeBase(elmtId: number): ViewBuildNodeBase | undefined;
    static instance_: UINodeRegisterProxy;
    removeElementsInfo_: Array<number>;
    static ElementIdToOwningViewPU_: Map<number, WeakRef<ViewBuildNodeBase>>;
}

// ============================================================================
// ObserveV2
// ============================================================================

declare class ViewV2 {
}

declare class MonitorV2 {
}

declare class ComputedV2 {
}

declare class PersistenceV2Impl {
}

declare class ObserveV2 {
    static readonly V2_DECO_META: unique symbol;
    static readonly V2_DECO_METHOD_META: unique symbol;
    static readonly SYMBOL_REFS: unique symbol;
    static readonly ID_REFS: unique symbol;
    static readonly MONITOR_REFS: unique symbol;
    static readonly ADD_MONITOR_REFS: unique symbol;
    static readonly SYNC_MONITOR_REFS: unique symbol;
    static readonly COMPUTED_REFS: unique symbol;
    static readonly SYMBOL_PROXY_GET_TARGET: unique symbol;
    static readonly SYMBOL_MAKE_OBSERVED: unique symbol;
    static readonly OB_PREFIX = "__ob_";
    static readonly ENV_PREFIX = "__env_";
    static readonly OB_PREFIX_LEN = 5;
    static readonly NO_REUSE = -1;
    static readonly OB_LENGTH = "___obj_length";
    private static setMapProxy;
    private static arrayProxy;
    private static objectProxy;
    private stackOfRenderedComponents_;
    id2cmp_: {
        number: WeakRef<ViewBuildNodeBase>;
    };
    id2ViewV2_: {
        number: WeakRef<ViewV2>;
    };
    id2Others_: {
        number: WeakRef<MonitorV2 | ComputedV2 | PersistenceV2Impl>;
    };
    id2targets_: {
        number: Set<WeakRef<Object>>;
    };
    idleTasks_: (Array<[(...any: any[]) => any, ...any[]]> & {
        first: number;
        end: number;
    });
    static readonly idleTasksInitLength = 1000;
    elmtIdsChanged_: Set<number>;
    private computedPropIdsChanged_;
    private monitorIdsChangedForAddMonitor_;
    private monitorSyncIdsChangedForAddMonitor_;
    private monitorIdsChanged_;
    private persistenceChanged_;
    monitorFuncsToRun_: Set<number>;
    private viewV2NeedUpdateMap_;
    private scheduledContainerIds_;
    private startDirty_;
    private disabled_;
    private disableRecording_;
    private calculatingComputedProp_;
    protected currentReuseId_: number;
    isParentChildOptimizable_: boolean;
    private applySyncRunningCount_;
    private static obsInstance_;
    __interopInStaticRendering_internal_: boolean;
    static getObserve(): ObserveV2;
    startRecordDependencies(cmp: MonitorV2 | ComputedV2 | PersistenceV2Impl | ViewBuildNodeBase, id: number, doClearBinding?: boolean): void;
    stopRecordDependencies(): void;
}

// ============================================================================
// RepeatAPI
// ============================================================================

declare interface RepeatAPI {
}
