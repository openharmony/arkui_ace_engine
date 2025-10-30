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
 */

import { eq, neq, gt, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.

declare class PUV2ViewBase {
  protected get isViewV2(): boolean;
}

declare class ViewPU extends PUV2ViewBase{
  public debugInfoStateVars(): string;
  get isViewV2(): boolean;
}

declare class ViewV2 extends PUV2ViewBase{
  public debugInfoStateVars(): string;
  get isViewV2(): boolean;
}

/**
 *  SDK API of Repeat and its attribute functions.
 */
interface RepeatItem<T> {
    readonly item: T;
    readonly index?: number;
}
type RepeatItemGenFunc<T> = (i: RepeatItem<T>) => void;
type RepeatTTypeGenFunc<T> = (item: T, index: number) => string;
type RepeatKeyGenFunc<T> = (item: T, index?: number) => string;
type RepeatTemplateOptions = {
    cachedCount?: number;
};
type RepeatTemplateImplOptions = {
    cachedCountSpecified: boolean;
    cachedCount?: number;
};
type OnMoveHandler = (from: number, to: number) => void;
interface ItemDragEventHandler {
    onLongPress?: (index: number) => void;
    onDragStart?: (index: number) => void;
    onMoveThrough?: (from: number, to: number) => void;
    onDrop?: (index: number) => void;
}
declare const Repeat: <T>(arr: Array<T>, owningView?: PUV2ViewBase) => RepeatAPI<T>;
interface RepeatAPI<T> {
    key: (keyGenFunc: RepeatKeyGenFunc<T>) => RepeatAPI<T>;
    each: (itemGenFunc: RepeatItemGenFunc<T>) => RepeatAPI<T>;
    virtualScroll: (options?: {
        totalCount?: number;
        onTotalCount?(): number;
        onLazyLoading?(index: number): void;
        reusable?: boolean;
    }) => RepeatAPI<T>;
    templateId: (typeFunc: RepeatTTypeGenFunc<T>) => RepeatAPI<T>;
    template: (type: string, itemGenFunc: RepeatItemGenFunc<T>, options?: RepeatTemplateOptions) => RepeatAPI<T>;
    render(isInitialRender: boolean): void;
    onMove: (handler: OnMoveHandler, eventHandler: ItemDragEventHandler) => RepeatAPI<T>;
}
interface __IRepeatItemInternal<T> {
    updateItem: (newItemVal: T) => void;
    updateIndex: (newIndexValue: number) => void;
    aboutToBeDeleted?: () => void;
}
interface __RepeatItemFactoryReturn<T> extends RepeatItem<T>, __IRepeatItemInternal<T> {
}
declare class __RepeatItemPU<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {
    public _observedItem;
    public _observedIndex?;
    constructor(owningView: ViewPU, initialItem: T, initialIndex?: number);
    get item(): T;
    get index(): number | undefined;
    updateItem(newItemValue: T): void;
    updateIndex(newIndex: number): void;
    aboutToBeDeleted(): void;
}
declare class __RepeatItemV2<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {
    constructor(initialItem: T, initialIndex?: number);
    item: T;
    index?: number;
    updateItem(newItemValue: T): void;
    updateIndex(newIndex: number): void;
    hasBindingToIndex(): boolean;
}
interface __RepeatItemInfo<T> {
    key: string;
    index: number;
    repeatItem?: __RepeatItemFactoryReturn<T>;
}
declare class __RepeatDefaultKeyGen {
    public static weakMap_;
    public static lastKey_;
    static func<T>(item: T): string;
    static funcWithIndex<T>(item: T, index: number): string;
    public static funcImpl;
}
interface __RepeatConfig<T> {
    owningView_?: ViewV2;
    arr?: Array<T>;
    itemGenFuncs?: {
        [type: string]: RepeatItemGenFunc<T>;
    };
    keyGenFunc?: RepeatKeyGenFunc<T>;
    keyGenFuncSpecified?: boolean;
    ttypeGenFunc?: RepeatTTypeGenFunc<T>;
    totalCountSpecified?: boolean;
    totalCount?: number | (() => number);
    onLazyLoading?: (index: number) => void;
    templateOptions?: {
        [type: string]: RepeatTemplateImplOptions;
    };
    mkRepeatItem?: (item: T, index?: number) => __RepeatItemFactoryReturn<T>;
    onMoveHandler?: OnMoveHandler;
    itemDragEventHandler?: ItemDragEventHandler;
    reusable?: boolean;
}
declare const RepeatEachFuncTtype: string;
declare class __Repeat<T> implements RepeatAPI<T> {
    public config;
    public impl;
    public isVirtualScroll;
    constructor(owningView: ViewV2 | ViewPU, arr: Array<T>);
    each(itemGenFunc: RepeatItemGenFunc<T>): RepeatAPI<T>;
    key(keyGenFunc: RepeatKeyGenFunc<T>): RepeatAPI<T>;
    virtualScroll(options?: {
        totalCount?: number;
        onTotalCount?: () => number;
        onLazyLoading?: (index: number) => void;
        reusable?: boolean;
    }): RepeatAPI<T>;
    templateId(ttypeGenFunc: RepeatTTypeGenFunc<T>): RepeatAPI<T>;
    template(ttype: string, itemGenFunc: RepeatItemGenFunc<T>, options?: RepeatTemplateOptions): RepeatAPI<T>;
    updateArr(arr: Array<T>): RepeatAPI<T>;
    render(isInitialRender: boolean): void;
    onMove(handler: OnMoveHandler, eventHandler?: ItemDragEventHandler): RepeatAPI<T>;
    aboutToBeDeleted(): void;
    public normTemplateOptions;
}
declare class ActiveDataItem<T> {
    item: T;
    rid?: number;
    ttype?: string;
    key?: string;
    state: number;
    static UINodeExists;
    static UINodeRenderFailed;
    static UINodeToBeRendered;
    static NoValue;
    protected constructor(state: number, itemValue?: T, rid?: number, ttype?: string, key?: string);
    static createWithUINode<T>(itemValue: T, rid: number, ttype: string, key?: string): ActiveDataItem<T>;
    static createFailedToCreateUINodeDataItem<T>(itemValue: T): ActiveDataItem<T>;
    static createMissingDataItem(): ActiveDataItem<void>;
    static createToBeRenderedDataItem<T>(itemValue: T, ttype: string, key?: string): ActiveDataItem<T>;
    toString(): string;
    dump(): string;
    shortDump(): string;
}
declare class RIDMeta<T> {
    readonly repeatItem_: __RepeatItemV2<T>;
    readonly ttype_: string;
    key_?: string;
    constructor(repeatItem: __RepeatItemV2<T>, ttype: string, key?: string);
}
declare enum NotificationType {
    START_CHANGE_POSITION = 0,
    END_CHANGE_POSITION = 1,
    START_AND_END_CHANGE_POSITION = 2
}
declare const NOOP: () => void;
declare class __RepeatVirtualScroll2Impl<T> {
    static readonly REF_META: unique symbol;
    public arr_;
    public selfPtr_;
    public keyGenFunc_?;
    public useKeys_;
    public key4Index_;
    public index4Key_;
    public oldDuplicateKeys_;
    public itemGenFuncs_;
    public ttypeGenFunc_?;
    public totalCount_;
    public onLazyLoadingFunc_;
    public lazyLoadingIndex_;
    public templateOptions_;
    public allowUpdate_?;
    public mkRepeatItem_;
    public onMoveHandler_?;
    public itemDragEventHandler_?;
    public moveFromTo_?;
    repeatElmtId_: number;
    public owningViewV2_;
    public nextRid;
    public activeRange_;
    public visibleRange_;
    public activeRangeAdjustedStart_;
    public visibleRangeAdjustedStart_;
    public meta4Rid_;
    public activeDataItems_;
    public spareRid_;
    public firstIndexChanged_;
    public firstIndexChangedInTryFastRelayout_;
    public hasItemBindingsToIndex_;
    public rerenderOngoing_;
    public nextTickTask_;
    public preventReRender_;
    public startRecordDependencies;
    public stopRecordDependencies;
    /**
     * return array item if it exists
     *
     * @param index
     * @returns tuple data item exists , data item
     *   (need to do like this to differentiate missing data item and undefined item value
     *   same as std::optional in C++)
     */
    public getItemUnmonitored;
    public getItemMonitored;
    public totalCount;
    render(config: __RepeatConfig<T>, isInitialRender: boolean): void;
    public updateTemplateOptions;
    public initialRender;
    public findDataItemInOldActivateDataItemsByValue;
    public findDataItemInOldActivateDataItemsByKey;
    public onUpdateDirty;
    public reRender;
    public moveItemsUnchanged;
    public moveRetainedItems;
    public addRemovedItemsToSpare;
    public newItemsNeedToRender;
    public computeTtype;
    public computeKey;
    public mkRandomKey;
    public handleDuplicateKey;
    /**
     * called from C++ GetFrameChild whenever need to create new node and add to L1
     * or update spare node and add back to L1
     *
     * @param forIndex
     * @returns
     */
    public onGetRid4Index;
    public canUpdate;
    public canUpdateTryMatch;
    public sortSpareRid;
    /**
     * crete new Child node onto the ViewStackProcessor
     *
     * @param forIndex
     * @param ttype
     * @returns [ success, 1 for new node created ]
     */
    public createNewChild;
    /**
    * update given rid / RepeatItem to data item of given index
    *
    * @param rid
    * @param ttype
    * @param forIndex
    * @returns [ success, 2 for updated existing node ]
    */
    public updateChild;
    /**
     * overloaded function from FrameNode
     * called from layout, inform index range of active / L1 items that can be removed from L1
     * to spare nodes, allow to update them
     * Note: Grid, List layout has a bug: Frequently calls GetFrameChildForIndex for the index 'fromIndex'
     *       which moves this item back to L1
     *
     * @param fromIndex
     * @param toIndex
     */
    public onRecycleItems;
    public onMoveFromTo;
    public isNonNegative;
    /**
     * What is the effective time of these two function(convertFromToIndex, convertFromToIndexRevert)?
     * - Only valid when ListItem is being dragged up and moved without dropping.
     * - Otherwise, this.moveFromTo_ is undefined, nothing will be processed and the original index value
     *  will be returned directly.
     *
     * How does this function convert index value?
     * - Look at this scenario.
     * - If original arr is [a, b, c, d], and users long-press item 'a' and drag it up and move it to pos after 'c'
     *  without dropping. What users see is [b, c, a, d]. Then this.moveFromTo_ is [0, 2].
     * - If mapping index by convertFromToIndex:
     *  index is 2, then the mappedIndex is 0.
     *  index is 1, then the mappedIndex is 2.
     *  index is 0, then the mappedIndex is 1.
     * - If mapping index by convertFromToIndexRevert:
     *  index is 0, then the mappedIndex is 2.
     *  index is 1, then the mappedIndex is 0.
     *  index is 2, then the mappedIndex is 1.
     *
     * Why these two function is needed?
     * - Simply put, they are used for onActiveRange and onRecycleItems when drag and drop sorting is on-going.
     * - Specifically, also based on the scenario upon and List is scrolling at the same time:
     *  a) if onActiveRange(1, 3) is being called, then, convertFromToIndexRevert is needed.
     *      "onActiveRange" is iterating activeDataItems_ and need to map each index in it by convertFromToIndexRevert,
     *      to judge mappedIndex whether is in active range. Otherwise, item 'a' whose index is 0 is not in active
     *      range and will be deleted. But actually, item 'a' whose index is 0 has been dragged to index 2.
     *      So item that need to be deleted is 'b', whose index is 1 and its mappedIndex is 0.
     *  b) if onRecycleItems(0, 1) is being called, then, convertFromToIndex is needed.
     *      "onRecycleItems(0, 1)" is iterating index from fromIndex to toIndex. In this scene, it needs to
     *      map each index by convertFromToIndex. Otherwise, item 'a' whose index is 0 will be removed from L1.
     *      But actually, item 'a' whose index is 0 has been dragged to index 2. So item that need to be removed
     *      is 'b', whose index is 1 and its mappedIndex is 0.
     */
    public convertFromToIndex;
    public convertFromToIndexRevert;
    public dropFromL1ActiveNodes;
    public onActiveRange;
    public isIndexInRange;
    public hasOverlapWithActiveRange;
    public needRerenderChange;
    public adjustActiveRangeStart;
    tryFastRelayout(arrChange: string, args: Array<unknown>): boolean;
    public tryFastRelayoutForChange;
    public tryFastRelayoutForChangeNormalized;
    public updateFirstIndexChangedInTryFastRelayout;
    public notifyContainerLayoutChangeAcc;
    public notifyContainerLayoutChange;
    public requestContainerReLayout;
    public onPurge;
    public purgeNode;
    public dumpSpareRid;
    public dumpRepeatItem4Rid;
    public dumpDataItems;
    public dumpCachedCount;
    public dumpKeys;
}

export class RepeatVirtualScrollTest1 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll(): void {}

  // Executed before every invidual tests. Can be empty
  public beforeEach(): void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}

  public getId(): string {
    return this.idString;
  }

  /// -- Test cases

  /* Test creation of __RepeatVirtualScroll2Impl
  * Calls:
   __RepeatVirtualScroll2Impl.constructor
  */
  public RepeatCreate(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = () => { return ''; };
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = (item) => { return JSON.stringify(item); };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    eq(repeatNode.arr_.length, 5, 'RepeatVirtualScrollTest1_RepeatCreate_01');
  }

  /* Test __RepeatVirtualScroll2Impl.totalCount
  * Calls:
   __RepeatVirtualScroll2Impl.totalCount
  */
  public RepeatTotalCountFunc(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = () => { return ''; };
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = (item) => { return JSON.stringify(item); };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    eq(repeatNode.totalCount(), 5, 'RepeatVirtualScrollTest1_RepeatTotalCountFunc_01');
    repeatNode.totalCount_ = 4;
    eq(repeatNode.totalCount(), 4, 'RepeatVirtualScrollTest1_RepeatTotalCountFunc_02');
    repeatNode.totalCount_ = () => { return 3; };
    eq(repeatNode.totalCount(), 3, 'RepeatVirtualScrollTest1_RepeatTotalCountFunc_03');
    repeatNode.totalCount_ = () => { return 2.5; };
    eq(repeatNode.totalCount(), 5, 'RepeatVirtualScrollTest1_RepeatTotalCountFunc_04');
    repeatNode.totalCount_ = () => { return -1; };
    eq(repeatNode.totalCount(), 5, 'RepeatVirtualScrollTest1_RepeatTotalCountFunc_05');
    repeatNode.totalCount_ = () => { return undefined; };
    eq(repeatNode.totalCount(), 5, 'RepeatVirtualScrollTest1_RepeatTotalCountFunc_06');
  }

  /* Test __RepeatVirtualScroll2Impl.updateTemplateOptions
  * Calls:
   __RepeatVirtualScroll2Impl.updateTemplateOptions
  */
  public RepeatUpdateTemplateOptionsFunc(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = () => { return ''; };
    repeatNode.templateOptions_ = { ['']: {cachedCountSpecified: false, cachedCount: 1 } };
    repeatNode.keyGenFunc_ = (item) => { return JSON.stringify(item); };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    eq(repeatNode.templateOptions_[''].cachedCountSpecified, false,
        'RepeatVirtualScrollTest1_RepeatUpdateTemplateOptionsFunc_01');
    eq(repeatNode.templateOptions_[''].cachedCount, 1,
        'RepeatVirtualScrollTest1_RepeatUpdateTemplateOptionsFunc_02');
    repeatNode.updateTemplateOptions();
    eq(repeatNode.templateOptions_[''].cachedCountSpecified, false,
        'RepeatVirtualScrollTest1_RepeatUpdateTemplateOptionsFunc_03');
    eq(repeatNode.templateOptions_[''].cachedCount, 1,
        'RepeatVirtualScrollTest1_RepeatUpdateTemplateOptionsFunc_04');
    repeatNode.allowUpdate_ = false;
    repeatNode.updateTemplateOptions();
    eq(repeatNode.templateOptions_[''].cachedCountSpecified, true,
        'RepeatVirtualScrollTest1_RepeatUpdateTemplateOptionsFunc_05');
    eq(repeatNode.templateOptions_[''].cachedCount, 0,
        'RepeatVirtualScrollTest1_RepeatUpdateTemplateOptionsFunc_06');
  }

  /* Test __RepeatVirtualScroll2Impl.computeTtype
  * Calls:
   __RepeatVirtualScroll2Impl.computeTtype
  */
  public RepeatComputeTtypeFunc(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = undefined;
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = (item) => { return JSON.stringify(item); };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    eq(repeatNode.computeTtype(0, 0, false), '', 'RepeatVirtualScrollTest1_RepeatComputeTtypeFunc_01');
    repeatNode.ttypeGenFunc_ = () => { return 'type'; };
    eq(repeatNode.computeTtype(0, 0, false), '', 'RepeatVirtualScrollTest1_RepeatComputeTtypeFunc_02');
    repeatNode.itemGenFuncs_['type'] = () => {};
    eq(repeatNode.computeTtype(0, 0, false), 'type', 'RepeatVirtualScrollTest1_RepeatComputeTtypeFunc_03');
  }

  /* Test __RepeatVirtualScroll2Impl.computeKey
  * Calls:
   __RepeatVirtualScroll2Impl.computeKey
  */
  public RepeatComputeKeyFunc(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = undefined;
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = (item) => { return JSON.stringify(item); };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    repeatNode.useKeys_ = false;
    eq(repeatNode.computeKey(0, 0, false), undefined, 'RepeatVirtualScrollTest1_RepeatComputeKeyFunc_01');
    repeatNode.useKeys_ = true;
    eq(repeatNode.computeKey(0, 0, false), '0', 'RepeatVirtualScrollTest1_RepeatComputeKeyFunc_02');
    repeatNode.key4Index_.set(0, 'new_key')
    eq(repeatNode.computeKey(0, 0, false), 'new_key', 'RepeatVirtualScrollTest1_RepeatComputeKeyFunc_03');
  }

  /* Test __RepeatVirtualScroll2Impl.handleDuplicateKey
  * Calls:
   __RepeatVirtualScroll2Impl.handleDuplicateKey
  */
  public RepeatHandleDuplicateKeyFunc(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = undefined;
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = (item) => { return JSON.stringify(item); };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    repeatNode.key4Index_.set(0, 'key');
    repeatNode.index4Key_.set('key', 0);
    repeatNode.handleDuplicateKey(1, 'key', 0);
    neq(repeatNode.key4Index_.get(0), 'key', 'RepeatVirtualScrollTest1_RepeatHandleDuplicateKeyFunc_01');
    neq(repeatNode.key4Index_.get(1), 'key', 'RepeatVirtualScrollTest1_RepeatHandleDuplicateKeyFunc_02');
    neq(repeatNode.key4Index_.get(0), repeatNode.key4Index_.get(1), 'RepeatVirtualScrollTest1_RepeatHandleDuplicateKeyFunc_03');
    eq([...repeatNode.oldDuplicateKeys_][0], 'key', 'RepeatVirtualScrollTest1_RepeatHandleDuplicateKeyFunc_04');
  }

  /* Test __RepeatVirtualScroll2Impl.computeKey with duplicate
  * Calls:
   __RepeatVirtualScroll2Impl.computeKey
  */
  public RepeatComputeKeyFuncWithDuplicate1(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = undefined;
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = () => { return 'key'; };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    repeatNode.useKeys_ = true;
    repeatNode.key4Index_.set(0, 'key');
    repeatNode.index4Key_.set('key', 0);
    neq(repeatNode.computeKey(0, 1, false), 'key', 'RepeatVirtualScrollTest1_RepeatComputeKeyFuncWithDuplicate1_01');
    neq(repeatNode.computeKey(0, 0, false), 'key', 'RepeatVirtualScrollTest1_RepeatComputeKeyFuncWithDuplicate1_02');
  }

  /* Test __RepeatVirtualScroll2Impl.computeKey with duplicate
  * Calls:
   __RepeatVirtualScroll2Impl.computeKey
  */
  public RepeatComputeKeyFuncWithDuplicate2(): void {
    let repeatNode = new __RepeatVirtualScroll2Impl();
    repeatNode.arr_ = [ 0, 1, 2, 3, 4 ];
    repeatNode.totalCount_ = undefined;
    repeatNode.onMoveHandler_ = undefined;
    repeatNode.itemDragEventHandler_ = undefined;
    repeatNode.owningViewV2_ = new ViewV2();
    repeatNode.itemGenFuncs_ = { ['']: () => {} };
    repeatNode.ttypeGenFunc_ = undefined;
    repeatNode.templateOptions_ = undefined;
    repeatNode.keyGenFunc_ = () => { return 'key'; };
    repeatNode.allowUpdate_ = true;
    repeatNode.mkRepeatItem_ = (item, index?) => new __RepeatItemV2(item, index);
    repeatNode.useKeys_ = true;
    repeatNode.oldDuplicateKeys_.add('key')
    neq(repeatNode.computeKey(0, 0, false), 'key', 'RepeatVirtualScrollTest1_RepeatComputeKeyFuncWithDuplicate2_01');
  }
}