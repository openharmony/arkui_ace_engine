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
 * all definitions in this file are framework internal
*/

/**
 * Repeat with .virtualScroll TS side implementation
 * for C++ side part of the implementation read the comments at top of file
 * core/components_ng/syntax/repeat_virtual_scroll_node.h
 *
 * See the factory solutions in pu_repeat.ts
 * __RepeatVirtualScroll2Impl gets created before first render
 *
 * onGetRid4Index(index) called upon layout calling C++ GetFrameChildByIndex
 * (whenever C++ does not find UINode sub-tree for index in L1)
 * 1- gets the data item - item might be lazy loaded (documented below)
 * 2- calculates the templateId (called ttype internally) for this index, then
 * 3- canUpdateTryMatch(index, ttype) tries to find spare UINode tree (identified by its RID)
 * 4- if found calls updateChild(rid, item, index, ....)
 *     updateChild simply updates repeatItem.item, .index, and requests UI updates synchronously (updateDirty2(true)
 *     TS informs to C++ the RID , and that existing UINode sub-tree has been updated
 * 5- if not fond calls createNewChild(index, ttype, ...)
 *    creates a new RepeatItem instance with a new RID
 *    calls the .each or .template item builder function to perform initial render
 *    TS informs C++ about the RID and that new UINode sub-tree root node should be taken from ViewStackProcessor
 *    added to C++ side RID -> UINode map / general cache
 *
 * onRecycleItems(fromIndex, upToBeforeIndex) - called from C++ RecycleItems
 * - move L1 items with fromIndex <= index < upToBeforeIndex to L2.
 *   calls C++ RepeatVirtualScroll2Native.setInvalid so also C++ side moves the RID from L1 to L2
 *   C++ does NOT remove the item from active tree, or change its Active status
 *   if so needed at the end of one processing cycle onActiveRange will do
 *
 * onActiveRange(....) - called from C++
 * - TS iterates over L1 items to check which which one is still in informed range, move to L2
 *   does NOT call RepeatVirtualScroll2Caches::SetInvalid
 * - C++ does the same
 *   a) iterate over L1 to remove items no longer in active range, move to L2
 *   b) iterate over L2, remove from render tree and set Active status
 *   c) order purge idle task
 *   d) calculate dynamicCachedCount for .each and for templateIds that do not have specified cachedCount option
 *
 * - Note: the rather convolute algorithm that uses parameters to decide if item is in active range or not
 *         needs to be exactly same in this function on TS side and on C++ side to ensure L1 info in TS and in C++ side
 *         reman in sync.
 *
 * onMoveFromTo(moveFrom, moveTo) - called from C++, used for drag drop sorting
 * - TS received moveFromTo from C++ and updated its own moveFromTo. Mainly used to do the following two things:
 *   a) update its own moveFromTo.
 *   b) reset its own moveFromTo.
 * 
 * How does the drag-drop-sorting work?
 *    1)users long press the ListItem and drag starts
 *    2)whenever the index of the dragged item changes, the translation table(this.moveFromTo_) takes care of fixing
 *      the order. While drag is on-going we do not expect the app to make any changes to the array. If it does,
 *      the visual result might not be what is expected
 *    3)user drops item
 *    4)FireOnMove resets the translation table
 *    5)onMove callback to the application, application changes the array
 *    6)frameWork observes array change, triggers rerender
 *    7)Repeat rerender
 * 
 * why TS needs maintain moveFromTo_?
 * - Mainly used to serve step_2 above
 * - For a more specific description, please refer to the description above function "convertFromToIndex"
 *  
 * when onMoveFromTo will be called from C++?
 * - When users drag item and move item without dropping, each order change will trigger MoveData(function in C++).
 *  For example, [a, b, c, d] shows in List, user drags item 'a' and move it after to 'c' without dropping.
 *  During this period, MoveData(0, 1) and MoveData(1, 2) will be called separately, and this.onMoveFromTo_ will
 *  be updated to [0, 1] and [0, 2] in sequence
 * 
 * 
 * onPurge called from C++  RepeatVirtualScrollNode::Purge in idle task
 *  ensure L1 side is within limits (cachedCount), deletes UINode subtrees that do not fit the permissible side
 *  cachedCount is defined for each templateId / ttype for for .each separately
 *
 *
 * rerender called from ViewV2 UpdateElement(repeatElmtId)
 *
 * what triggers Repeat rerender?
 * - new source array assignment; array add, delete, move item
 * - input to templateId function changed
 * - input to key function changed (if key used)
 * - totalCount changed
 *
 * cached array item at index and new array item at index2 are considered the same if
 * - the keys computed from them are the same (if key used)
 * - if items compare equal with === operator
 * the algorithm that compares items can handle duplicate array items.
 * the algorithm will fail unnoticed if cached array item and new array item are different but their key is the same
 *   (this violates the requirement of stable keys)
 *
 * read the source code of rerender, each step has documentation
 *
 * the outcome of rerender is
 * 1- array items in cached and new array (active range), aka retained array items, repeatItem.index updated if changed
 * 2- delete array items -> RID / UINode sub-tree moved to L2
 * 3- added array items - try to find fitting RID / UINode subtree (same templateId / ttype) and
 *    update by updating repeatItem.item and .index newly added array items that can not be rendered
 *    by update are NOT rendered, will deal with new renders when GetFrameChildByIndex requests
 * 4- synchronous partial update to update all bindings that need update from step 1 and 3.
 * 5- inform new L1 (and thereby also L2) to C++ by calling updateL1Rid4Index(list of rid), same call also
 *    invalidates container layout starting from first changes item index, updates also totalCount on C++ side
 *
 * 
 * Lazy loading feature, available for API 18 ->
 * 
 * 1- getItemUnmonitored() executes onLazyLoadingFunc_ function if the function is defined and requested item is not in
 *    the source array. Member variable lazyLoadingIndex_ is used to store the requested index.
 * 2- ArrayProxyHandler catches the operation (this.arr_[index] = newItem) and calls tryFastRelayout.
 * 3- tryFastRelayout calls updateTotalCount(), enqueues a requestContainerReLayout call to the container (that lets the
 *    container know there is a new item and the new total count) and returns true, meaning Repeat should be excluded 
 *    from following fireChange.
 * 4- onLazyLoadingFunc_ function returns, lazyLoadingIndex_ is set to -1
 * 5- getItemUnmonitored() returns the lazy loaded item
 * 
 * Lazy loading can happen in these situations:
 * 1- onGetRid4Index(index) is called the first time for this index
 * 2- rerender step 1 checks if item in this.arr_[index] (from the old active range) has changed,
 *    but there is no item at this.arr_[index]
 *    (this can happen e.g. when the application calls this.arr_ = [])
 * 
 * Why lazy loading does not need rerender?
 *   In case 2 abowe Repeat is already rerendering, and onGetRid4Index executes always either createNewChild or 
 *   updateChild, so we don't need a rerender after a lazy loading. Rerender CAN still happen if the totalCount
 *   was defined with a variable that updates its value after lazy loading has added an item (changed the array length)!
 *   Therefore using onTotalCount function is recommended with onLazyLoading.
 * 
 * Situations when an Error is thrown:
 * 1- if during lazy loading the ArrayProxyHandler reports some other operation than 'set' (arr[index] = ...)
 * 2- if during lazy loading the ArrayProxyHandler reports 'set' to some other index than lazyLoadingIndex_
 * 
 * Also, it is considered an error situation if there still is no item in this.arr_[index] after onLazyLoadingFunc_(index)
 * returns, but we will not throw Error. Note that the container stops renderding when this happens.
 *
 *
 * The most important data structures
 *
 * RID - Repeat Item ID - a unique number, uniquely identifies a RepeatItem - templateId - UINode triple
 *    these found data items remain together until deleted from the system
 *    (ie.. until purge or unload deletes the UINode subtree)
 *
 * meta4Rid_: Map<number, RIDMeta<T>>
 * - for each RID:
 *    - constant: RepeatItem
 *    - constant: ttype
 *    - mutable: key
 * - counterpart on C++ side RepeatVirtualScroll2Caches.cacheItem4Rid_ maps RID -> UINode
 *
 * activeDataItems -  Array<ActiveDataItem<T | void>>
 *   This is the central data structure for rerender, as allows to compare previous item value / keys
 *   Sparse array, only includes items for active range
 *   - array item value at last render/update, rid, ttype, key (if used), some state info
 *
 * spareRid_ : set<RID>  RID currently not in active range, "L2"
 *
 * ttypeGenFunc_: templateId function
 * itemGenFuncs_: map of item builder functions  per templateId / ttype and .each
 */

class ActiveDataItem<T> {
    public item: T;
    public rid?: number;
    public ttype?: string;
    public key?: string;
    public state: number;

    public static readonly UINodeExists = 1;
    public static readonly UINodeRenderFailed = 2;
    public static readonly UINodeToBeRendered = 3;
    public static readonly NoValue = 4;

    protected constructor(state: number, itemValue?: T, rid?: number, ttype?: string, key?: string) {
        this.state = state;
        this.item = itemValue;
        this.rid = rid;
        this.ttype = ttype;
        this.key = key;
    }

    // factory functions for permissible ActiveDataItems
    public static createWithUINode<T>(itemValue: T, rid: number, ttype: string, key?: string): ActiveDataItem<T> {
        return new ActiveDataItem(ActiveDataItem.UINodeExists, itemValue, rid, ttype, key);
    }

    public static createFailedToCreateUINodeDataItem<T>(itemValue: T): ActiveDataItem<T> {
        return new ActiveDataItem(ActiveDataItem.UINodeRenderFailed, itemValue);
    }

    public static createMissingDataItem(): ActiveDataItem<void> {
        return new ActiveDataItem<void>(ActiveDataItem.NoValue);
    }

    public static createToBeRenderedDataItem<T>(itemValue: T, ttype: string, key?: string): ActiveDataItem<T> {
        return new ActiveDataItem(ActiveDataItem.UINodeToBeRendered, itemValue, undefined, ttype, key);
    }

    public toString(): string {
        return this.state === ActiveDataItem.UINodeExists
            ? `[rid: ${this.rid}, ttype: ${this.ttype}${this.key ? ', key: ' + this.key : ''}]`
            : `[no item]`;
    }

    public dump(): string {
        const state = this.state === ActiveDataItem.UINodeExists
            ? 'UINode exists'
            : this.state === ActiveDataItem.UINodeRenderFailed
                ? 'UINode failed to render'
                : this.state === ActiveDataItem.UINodeToBeRendered
                    ? 'UINode to be rendered'
                    : this.state === ActiveDataItem.NoValue
                        ? 'No data value'
                        : 'unknown state (error)';
        const rid = this.rid ?? 'no RID/not rendered';
        const ttype = this.ttype ?? 'ttype N/A';
        return (this.state === ActiveDataItem.UINodeExists)
            ? `state: '${state}', RID: ${rid}, ttype: ${ttype}, key: ${this.key}`
            : `state: '${state}'`;
    }

    public shortDump() : string {
        const state = this.state === ActiveDataItem.UINodeExists
            ? 'UINode exists'
            : this.state === ActiveDataItem.UINodeRenderFailed
                ? 'UINode failed to render'
                : this.state === ActiveDataItem.NoValue
                    ? 'No data value'
                    : 'unknown state (error)';
        const rid = this.rid ?? 'no RID/not rendered';
        const ttype = this.ttype ?? 'ttype N/A';
        return (this.state === ActiveDataItem.UINodeExists) 
            ? `state: '${state}', RID: ${rid}, ttype: ${ttype}`
            : `state: '${state}'`;
    }
}

// info about each created UINode / each RepeatItem / each RID
// only optional key is allowed to change
class RIDMeta<T> {
    public readonly repeatItem_: __RepeatItemV2<T>;
    public readonly ttype_: string;
    public key_?: string;

    constructor(repeatItem: __RepeatItemV2<T>, ttype: string, key?: string) {
        this.repeatItem_ = repeatItem;
        this.ttype_ = ttype;
        this.key_ = key;
    }
}

// see enum NG::UINode::NotificationType
enum NotificationType {
    START_CHANGE_POSITION = 0, END_CHANGE_POSITION, START_AND_END_CHANGE_POSITION
}

// empty function
const NOOP : () => void = function() {};

class __RepeatVirtualScroll2Impl<T> {
    public static readonly REF_META = Symbol('__repeat_ref_meta__');

    private arr_: Array<T>;

    // pointer to self, used to subscribe to source array
    private selfPtr_ = new WeakRef<__RepeatVirtualScroll2Impl<T>>(this);

    // key function
    private keyGenFunc_?: RepeatKeyGenFunc<T>;

    // is key function specified ?
    private useKeys_: boolean = false;

    // index <-> key bidirectional mapping
    private key4Index_: Map<number, string> = new Map<number, string>();
    private index4Key_: Map<string, number> = new Map<string, number>();
    // duplicate keys
    private oldDuplicateKeys_: Set<string> = new Set<string>();

    // map if .each and .template functions
    private itemGenFuncs_: { [type: string]: RepeatItemGenFunc<T> };

    // templateId function 
    private ttypeGenFunc_?: RepeatTTypeGenFunc<T>;

    // virtualScroll({ totalCount: number }), optional to set
    private totalCount_: (() => number) | number | undefined;

    // virtualScroll({ onLazyLoading: (index: number) => void }), optional to set
    private onLazyLoadingFunc_: (index : number) => void;
    private lazyLoadingIndex_: number = -1;

    // .template 3rd parameter, cachedCount
    private templateOptions_: { [type: string]: RepeatTemplateImplOptions };

    // reuse node in L2 cache or not
    private allowUpdate_?: boolean = true;

    // factory for interface RepeatItem<T> objects
    private mkRepeatItem_: (item: T, index?: number) => __RepeatItemFactoryReturn<T>;

    // register drag drop manager, only used for List
    private onMoveHandler_?: OnMoveHandler;

    // register drag drop Handler Class, only used for List onMove
    private itemDragEventHandler_?: ItemDragEventHandler;

    // update from C++ when MoveData happens
    // reset from C++ when FireOnMove happens
    private moveFromTo_?: [number, number] = undefined;

    // RepeatVirtualScroll2Node elmtId
    public repeatElmtId_: number = -1;

    private owningViewV2_: ViewV2;

    // used to generate unique RID
    private nextRid: number = 1;

    // previously informed active range from - to
    private activeRange_: [number, number] = [Number.NaN, Number.NaN];

    // previously informed visible range from - to
    private visibleRange_: [number, number] = [Number.NaN, Number.NaN];

    // adjusted activeRange[0] based on accumulated array mutations
    private activeRangeAdjustedStart_ = Number.NaN;

    // adjusted visibleRange[0] based on accumulated array mutations
    private visibleRangeAdjustedStart_ = Number.NaN;

    // Map containing all rid: rid -> RepeatItem, ttype, key?
    // entires never change
    private meta4Rid_: Map<number, RIDMeta<T>> = new Map<number, RIDMeta<T>>();

    // Map containing all rid: rid -> ttype,
    // entires never change
    // private ttype4Rid_: Map<number, string> = new Map<number, string>();

    // sparse Array containing copy of data items and optionally keys in active range
    private activeDataItems_: Array<ActiveDataItem<T | void>> = new Array<ActiveDataItem<T | void>>();

    // rid not in L1 / not in active range belong to this set
    // they are no longer associated with a data item
    private spareRid_: Set<number> = new Set<number>();

    // record the additional spare rid added in addRemovedItemsToSpare()
    private additionalSpareRid_: Set<number> = new Set<number>();

    // record the rid that need to Call OnRecycle() on C++ side
    private ridNeedToRecycle_: Set<number> = new Set<number>();

    // request container re-layout
    private firstIndexChanged_: number = 0;

    private firstIndexChangedInTryFastRelayout_: number = Number.NaN;

    // optimization: true if any items have bindings with their indexes
    private hasItemBindingsToIndex_ = false;

    // optimization: flag for checking if rerender is already ongoing
    private rerenderOngoing_: boolean = false;

    // microtask to sync render-tree after tryFastRelayout
    private nextTickTask_: ((changeIndex?: number) => void) | undefined = undefined;

    // prevents reRender() trigger
    private preventReRender_: boolean = false;

    // when access view model record dependency on 'this'.
    private startRecordDependencies(clearBindings: boolean = false): void {
        ObserveV2.getObserve().startRecordDependencies(this.owningViewV2_, this.repeatElmtId_, clearBindings);
    }

    private stopRecordDependencies(): void {
        ObserveV2.getObserve().stopRecordDependencies();
    }

    /**
     * return array item if it exists
     *
     * @param index 
     * @returns tuple data item exists , data item 
     *   (need to do like this to differentiate missing data item and undefined item value
     *   same as std::optional in C++)
     */
    private getItemUnmonitored(index: number | string): [boolean, T] {
        stateMgmtConsole.debug(`getItemUnmonitored ${index} data item exists: ${index in this.arr_}`);
        if (this.onLazyLoadingFunc_ && !(index in this.arr_)) {
            this.lazyLoadingIndex_ = index as number;
            // ensure unrecorded lazy loading!
            ObserveV2.getObserve().executeUnrecorded(() => { this.onLazyLoadingFunc_(this.lazyLoadingIndex_) });
            if (!(index in this.arr_)) {
                const msg = ` onLazyLoading function did not provide data to index ${index}`;
                stateMgmtConsole.applicationError(`${this.constructor.name}(${this.repeatElmtId_}): ${msg}`);
            }
            this.lazyLoadingIndex_ = -1;
        }
        return [(index in this.arr_), this.arr_[index]];
    }

    private getItemMonitored(index: number | string): [boolean, T] {
        stateMgmtConsole.debug(`getItemMonitored ${index} data item exists: ${index in this.arr_}`);

        this.startRecordDependencies(/* do not clear bindings */ false);

        const result = this.arr_[index];

        this.stopRecordDependencies();

        return [(index in this.arr_), result];
    }

    private totalCount(forceRetrieveTotalCount = false): number {
        // when 'totalCount' is set as an <observable>, we call updateElement() just to
        // retrieve its actual value - prevent triggering re-render here.
        if (forceRetrieveTotalCount && typeof this.totalCount_ === 'number') {
            this.preventReRender_ = true;
            this.owningViewV2_.UpdateElement(this.repeatElmtId_);
            this.preventReRender_ = false;
            return this.totalCount();
        }
        if (typeof this.totalCount_ === 'function') {
            let totalCount = this.totalCount_();
            return (Number.isInteger(totalCount) && totalCount >= 0) ? totalCount : this.arr_.length;
        }
        return this.totalCount_ ?? this.arr_.length;
    }

    // initial render
    // called from __Repeat.render
    public render(config: __RepeatConfig<T>, isInitialRender: boolean): void {

        if (this.arr_ && this.arr_ !== config.arr && this.arr_[__RepeatVirtualScroll2Impl.REF_META] !== undefined) {
            // unsubscribe from the old source array
            this.arr_[__RepeatVirtualScroll2Impl.REF_META].delete(this.selfPtr_);
        }
        
        // switch to the new array
        this.arr_ = config.arr;
        
        // add subscribers Set if needed
        if (!(__RepeatVirtualScroll2Impl.REF_META in this.arr_)) {
            this.arr_[__RepeatVirtualScroll2Impl.REF_META] = new Set<WeakRef<__RepeatVirtualScroll2Impl<T>>>();
        }
        
        // subscribe to the new source array
        if (this.arr_[__RepeatVirtualScroll2Impl.REF_META] !== undefined) {
            this.arr_[__RepeatVirtualScroll2Impl.REF_META].add(this.selfPtr_);
        }

        // totalCount can be function, number or undefined
        this.totalCount_ = config.totalCount;

        this.onMoveHandler_ = config.onMoveHandler;
        this.itemDragEventHandler_ = config.itemDragEventHandler;

        this.owningViewV2_ = config.owningView_;
        if ((this.owningViewV2_ instanceof ViewV2) && ('onLazyLoading' in config)) {
            this.onLazyLoadingFunc_ = config.onLazyLoading;
        }

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_})`,
            `totalCount ${this.totalCount()} arr length ${this.arr_.length} .`);

        if (!this.onLazyLoadingFunc_ && this.totalCount() > this.arr_.length) {
            stateMgmtConsole.applicationError(`${this.constructor.name}(${this.repeatElmtId_})`,
                `'totalCount' must not exceed the array length without 'onLazyLoading' being defined!`);
        }

        if (isInitialRender) {
            this.itemGenFuncs_ = config.itemGenFuncs;
            this.ttypeGenFunc_ = config.ttypeGenFunc;
            this.templateOptions_ = config.templateOptions;

            this.keyGenFunc_ = config.keyGenFunc;
            this.allowUpdate_ = config.reusable;

            this.mkRepeatItem_ = config.mkRepeatItem;

            if (!(this.owningViewV2_ instanceof ViewV2)) {
                stateMgmtConsole.applicationWarn(`${this.constructor.name}(${this.repeatElmtId_}))`,
                    `it is not allowed to use Repeat virtualScroll inside a @Component!`);
            }

            if (!this.itemGenFuncs_[RepeatEachFuncTtype]) {
                throw new Error(`${this.constructor.name}(${this.repeatElmtId_}))` +
                    `lacks mandatory '.each' attribute function, i.e. has no default item builder. Application error!`);
            }

            this.initialRender();
        } else {
            this.preventReRender_ || this.reRender();
        }

        this.updateTemplateOptions();
    }

    private updateTemplateOptions(): void {
        if (!this.allowUpdate_) {
            for (const templateType in this.templateOptions_) {
                this.templateOptions_[templateType] = { cachedCountSpecified: true, cachedCount: 0 };
            }
        }
    }

    private initialRender(): void {
        this.repeatElmtId_ = ObserveV2.getCurrentRecordedId();

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) initialRender()`,
            `data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - start`);

        const arrLen = this.onLazyLoadingFunc_ ? this.totalCount() : this.arr_.length;
        // Create the RepeatVirtualScroll2Node object
        // pass the C++ to TS callback functions.
        RepeatVirtualScroll2Native.create(arrLen, this.totalCount(), {
            onGetRid4Index: this.onGetRid4Index.bind(this),
            onRecycleItems: this.onRecycleItems.bind(this),
            onActiveRange: this.onActiveRange.bind(this),
            onMoveFromTo: this.onMoveFromTo.bind(this),
            onPurge: this.onPurge.bind(this)
        });

        // init onMove
        RepeatVirtualScroll2Native.onMove(this.repeatElmtId_, this.onMoveHandler_, this.itemDragEventHandler_);

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) initialRender() data array length: `,
            `${this.arr_.length}, totalCount: ${this.totalCount()} - done`);
    }

    // given data item and the ttype it needs to be rendered with from updated array:
    // find same data item in activeDataItems, it also still needs to use same ttype as given
    // return its { index in activeDataItems, its rid }
    private findDataItemInOldActivateDataItemsByValue(
        dataItem: T, ttype: string): { oldIndexStr: string, rid?: number } | undefined {
        for (const oldIndex in this.activeDataItems_) {
            const oldItem = this.activeDataItems_[oldIndex];
            if (oldItem.item === dataItem && oldItem.rid && oldItem.ttype === ttype) {
                return { oldIndexStr: oldIndex, rid: oldItem.rid };
            }
        }
        return undefined;
    }

    // find same data item in activeDataItems by key, it also still needs to use same ttype as given
    private findDataItemInOldActivateDataItemsByKey(
        key: string, ttype: string): {oldIndexStr: string, rid?: number} | undefined {
        for (const oldIndex in this.activeDataItems_) {
            const oldItem = this.activeDataItems_[oldIndex];
            if (oldItem.key === key && oldItem.rid && oldItem.ttype === ttype) {
                return { oldIndexStr: oldIndex, rid: oldItem.rid };
            }
        }
        return undefined;
    }

    // update Repeat, see overview documentation at the top of this file.
    private reRender(): void {
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) reRender() data array length: `,
            `${this.arr_.length}, totalCount: ${this.totalCount()} - start`);

        this.rerenderOngoing_ = true;

        // update onMove
        // scenario: developers control whether onMove exists or not dynamically. 
        RepeatVirtualScroll2Native.onMove(this.repeatElmtId_, this.onMoveHandler_, this.itemDragEventHandler_);

        const activeRangeFrom = this.activeRange_[0];
        const activeRangeTo = this.activeRange_[1];
        const arrLen = this.onLazyLoadingFunc_ ? this.totalCount() : this.arr_.length;

        stateMgmtConsole.debug(`checking range ${activeRangeFrom} - ${activeRangeTo}`);

        this.firstIndexChanged_ = Math.min(activeRangeTo + 1, this.arr_.length);

        // replacement for this.activeDataItems_
        const newActiveDataItems: Array<ActiveDataItem<void | T>> = new Array<ActiveDataItem<void | T>>();

        // replacement for l1Rid4Index_ index -> rid map on C++ side
        // will send to C++ when done
        const newL1Rid4Index: Map<number, number> = new Map<number, number>();

        // clear keys for new rerender
        this.key4Index_.clear();
        this.index4Key_.clear();
        this.oldDuplicateKeys_.clear();

        // step 1. move data items to newActiveDataItems that are unchanged
        // (same item / same key, still at same index, same ttype)
        // create createMissingDataItem -type entries for all other new data items.
        if (!this.moveItemsUnchanged(newActiveDataItems, newL1Rid4Index)) {
            this.rerenderOngoing_ = false;
            return;
        }

        // step 2. move retained data items
        // these are items with same value / same key in new and old array: 
        // their index has changed, ttype is unchanged
        this.moveRetainedItems(newActiveDataItems, newL1Rid4Index);

        // step 3. remaining old data items, i.e. data item removed from source array
        // add their rid to spare
        this.addRemovedItemsToSpare();

        // step 4: data items in new source array that are either new in the array
        // or have been there before but need to be rendered with different ttype
        // if canUpdate then do the update.
        // if need new render, do not do the new render right away. Wait for layout to ask
        // for the item to render.
        this.newItemsNeedToRender(newActiveDataItems, newL1Rid4Index);

        // render all data changes in one go
        ObserveV2.getObserve().updateDirty2(true);

        this.activeDataItems_ = newActiveDataItems;

        stateMgmtConsole.debug(`rerender result: `,
            `\nspareRid : ${this.dumpSpareRid()}`,
            `\nthis.dumpDataItems: ${this.activeDataItems_}`,
            `\nnewL1Rid4Index: ${JSON.stringify(Array.from(newL1Rid4Index))}`,
            `\nfirst item changed at index ${this.firstIndexChanged_} .`);

        if (!isNaN(this.firstIndexChangedInTryFastRelayout_)) {
            this.firstIndexChanged_ = Math.min(this.firstIndexChanged_, this.firstIndexChangedInTryFastRelayout_);
            this.firstIndexChangedInTryFastRelayout_ = Number.NaN;
        }
        RepeatVirtualScroll2Native.updateL1Rid4Index(this.repeatElmtId_, arrLen, this.totalCount(),
            this.firstIndexChanged_, Array.from(newL1Rid4Index), Array.from(this.ridNeedToRecycle_));

        this.rerenderOngoing_ = false;

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) reRender() data array length: `,
            `${this.arr_.length}, totalCount: ${this.totalCount()} - done`);
    }

    private moveItemsUnchanged(
        newActiveDataItems: Array<ActiveDataItem<void | T>>, newL1Rid4Index: Map<number, number>): boolean {
        let hasChanges = false;
        for (const indexS in this.activeDataItems_) {
            const activeIndex = parseInt(indexS);
            if (activeIndex < 0) {
                // out of range to consider
                continue;
            }
            if (activeIndex >= this.arr_.length || activeIndex >= this.totalCount()) {
                // data item has been popped from arr_ array that are part of active range
                hasChanges = true;
                break;
            }

            const [dataItemExists, dataItemAtIndex] = this.getItemUnmonitored(activeIndex);
            if (!dataItemExists) {
                stateMgmtConsole.debug(`index ${activeIndex} no data in new array, had data before `,
                    `${this.activeDataItems_[indexS].state !== ActiveDataItem.NoValue}`);
                hasChanges = hasChanges || (this.activeDataItems_[indexS].state !== ActiveDataItem.NoValue);
                newActiveDataItems[activeIndex] = ActiveDataItem.createMissingDataItem();
                continue;
            }

            const ttype = this.computeTtype(dataItemAtIndex, activeIndex,
                /* monitored access already enabled */ false);
            const key = this.computeKey(dataItemAtIndex, activeIndex,
                /* monitor access already on-going */ false, newActiveDataItems);

            // compare with ttype and data item, or with ttype and key
            if ((ttype === this.activeDataItems_[activeIndex].ttype) &&
                ((!this.useKeys_ && dataItemAtIndex === this.activeDataItems_[activeIndex].item) ||
                (this.useKeys_ && key === this.activeDataItems_[activeIndex].key))) {
                stateMgmtConsole.debug(
                    `index ${activeIndex} ttype '${ttype}'${this.useKeys_ ? ', key ' + key : ''} `,
                    `and dataItem unchanged.`);
                newActiveDataItems[activeIndex] = this.activeDataItems_[activeIndex];

                // add to index -> rid map to be sent to C++
                newL1Rid4Index.set(activeIndex, this.activeDataItems_[activeIndex].rid);

                // the data item is handled, remove it from old active data range
                // so we do not use it again
                delete this.activeDataItems_[activeIndex];
            } else {
                stateMgmtConsole.debug(`index ${activeIndex} has changed `,
                    `${dataItemAtIndex !== this.activeDataItems_[activeIndex].item}, ttype ${ttype} has changed `,
                    `${ttype !== this.activeDataItems_[activeIndex].ttype}, key ${key} has changed `,
                    `${key !== this.activeDataItems_[activeIndex].key}, using keys ${this.useKeys_}`);
                newActiveDataItems[activeIndex] =
                    ActiveDataItem.createToBeRenderedDataItem(dataItemAtIndex, ttype, key);
                hasChanges = true;
            }
        } // for activeItems

        // tells the container to adjust the scroll position (when it's needed)
        const hasNotifiedLayoutChange = this.notifyContainerLayoutChangeAcc();

        if (hasChanges) {
            return true;
        }

        // invalidate the layout only for items beyond active range
        // this is for the case that there is space for more visible items in the container.
        // triggers layout to request FrameCount() / totalCount and if increased newly added source array items
        this.activeDataItems_ = newActiveDataItems;

        if (hasNotifiedLayoutChange) {
            this.requestContainerReLayout();
        } else {
            this.requestContainerReLayout(Math.min(this.totalCount() - 1, this.activeRange_[1] + 1));
        }

        return false;
    }

    private moveRetainedItems(
        newActiveDataItems: Array<ActiveDataItem<void | T>>, newL1Rid4Index: Map<number, number>): void {
        for (const indexS in newActiveDataItems) {
            const activeIndex = parseInt(indexS);
            const newActiveDataItemAtActiveIndex = newActiveDataItems[activeIndex];

            if (newActiveDataItemAtActiveIndex.state === ActiveDataItem.UINodeExists) {
                // same index in new and old, processed in step 1
                continue;
            }

            this.firstIndexChanged_ = Math.min(this.firstIndexChanged_, activeIndex);

            if (newActiveDataItemAtActiveIndex.state === ActiveDataItem.NoValue) {
                stateMgmtConsole.debug(`new index ${activeIndex} missing in updated source array.`);
                continue;
            }

            // retainedItem must have same item value / same key, same ttype, but new index
            let movedDataItem;
            if (this.useKeys_) {
                const key = this.computeKey(newActiveDataItemAtActiveIndex.item as T, activeIndex,
                    /* monitor access already ongoing */ false, newActiveDataItems);
                movedDataItem =
                    this.findDataItemInOldActivateDataItemsByKey(key, newActiveDataItemAtActiveIndex.ttype);
            } else {
                movedDataItem = this.findDataItemInOldActivateDataItemsByValue(
                    newActiveDataItemAtActiveIndex.item as T, newActiveDataItemAtActiveIndex.ttype);
            }

            if (movedDataItem) {
                const ridMeta = this.meta4Rid_.get(movedDataItem.rid);
                if (!ridMeta) {
                    continue;
                }
                // data item rendered before, and needed ttype to render has not changed
                newActiveDataItemAtActiveIndex.rid = movedDataItem.rid;
                newActiveDataItemAtActiveIndex.state = ActiveDataItem.UINodeExists;
                
                // add to index -> rid map to be sent to C++
                newL1Rid4Index.set(activeIndex, movedDataItem.rid);

                // index has changed, update it in RepeatItem
                stateMgmtConsole.debug(`new index ${activeIndex} / old index ${movedDataItem.oldIndexStr}: `,
                    `keep in L1: rid ${movedDataItem.rid}, unchanged ttype '${newActiveDataItemAtActiveIndex.ttype}'`);
                ridMeta.repeatItem_.updateIndex(activeIndex);

                // the data item is handled, remove it from old active data range
                // so we do not use it again
                delete this.activeDataItems_[movedDataItem.oldIndexStr];
            } else {
                // update is needed for this data item
                // either because dataItem is new, or new ttype needs to used
                stateMgmtConsole.debug(`need update for index ${activeIndex}`);
            }
        } // for new data items in active range
    }

    private addRemovedItemsToSpare(): void {
        this.additionalSpareRid_.clear();
        for (let oldIndex in this.activeDataItems_) {
            if (this.activeDataItems_[oldIndex].rid) {
                this.spareRid_.add(this.activeDataItems_[oldIndex].rid);
                this.additionalSpareRid_.add(this.activeDataItems_[oldIndex].rid);
                const index = parseInt(oldIndex);
                this.index4Key_.delete(this.key4Index_.get(index));
                this.key4Index_.delete(index);
            }
        }
    }

    private newItemsNeedToRender(
        newActiveDataItems: Array<ActiveDataItem<void | T>>, newL1Rid4Index: Map<number, number>): void {
        this.ridNeedToRecycle_.clear();
        for (const indexS in newActiveDataItems) {
            const activeIndex = parseInt(indexS);
            const newActiveDataItemAtActiveIndex = newActiveDataItems[activeIndex];

            if (newActiveDataItemAtActiveIndex.state !== ActiveDataItem.UINodeToBeRendered) {
                continue;
            }

            const optRid = this.canUpdate(newActiveDataItemAtActiveIndex.ttype);
            if (optRid <= 0) {
                stateMgmtConsole.debug(`active range index ${activeIndex}: no rid found to update`);
                continue;
            }
            const ridMeta = this.meta4Rid_.get(optRid);
            if (ridMeta) {
                // found rid / repeatItem to update
                stateMgmtConsole.debug(`index ${activeIndex}: update rid ${optRid} / ttype `,
                    `'${newActiveDataItemAtActiveIndex.ttype}'`);

                newActiveDataItemAtActiveIndex.rid = optRid;
                newActiveDataItemAtActiveIndex.state = ActiveDataItem.UINodeExists;

                if (this.useKeys_) {
                    const key = this.computeKey(newActiveDataItemAtActiveIndex.item as T, activeIndex,
                        /* monitor access already ongoing */ false, newActiveDataItems);
                    newActiveDataItemAtActiveIndex.key = key;
                    ridMeta.key_ = key;
                }

                // spare rid is used
                this.spareRid_.delete(optRid);

                // add to index -> rid map to be sent to C++
                newL1Rid4Index.set(activeIndex, optRid);

                // if the rid is recycled in current render, notify C++ to call OnRecycle()
                if (this.additionalSpareRid_.has(optRid)) {
                    this.ridNeedToRecycle_.add(optRid);
                }

                // don't need to call getItem here, already checked that the data item exists
                ridMeta.repeatItem_.updateItem(newActiveDataItemAtActiveIndex.item as T);
                ridMeta.repeatItem_.updateIndex(activeIndex);

                this.firstIndexChanged_ = Math.min(this.firstIndexChanged_, activeIndex);
            }
        };
    }

    private computeTtype(item: T, index: number, monitorAccess: boolean): string {
        if (this.ttypeGenFunc_ === undefined) {
            return RepeatEachFuncTtype;
        }
        // record dependencies if monitoring is enabled
        monitorAccess && this.startRecordDependencies(false);
        let ttype = RepeatEachFuncTtype;
        try {
            ttype = this.ttypeGenFunc_(item, index);
        } catch (e) {
            stateMgmtConsole.applicationError(
                `${this.constructor.name}(${this.repeatElmtId_}): Error generating ttype at index: ${index}`,
                e?.message);
        }
        if (ttype in this.itemGenFuncs_ === false) {
            stateMgmtConsole.applicationError(`${this.constructor.name}(${this.repeatElmtId_}):`,
                `No template found for ttype '${ttype}'`);
            ttype = RepeatEachFuncTtype;
        }
        monitorAccess && this.stopRecordDependencies();
        return ttype;
    }

    private computeKey(item: T, index: number, monitorAccess: boolean = true,
        activateDataItems?: Array<ActiveDataItem<void | T>>): string | undefined {
        if (!this.useKeys_) {
            return undefined;
        }

        let key = this.key4Index_.get(index);
        if (!key) {
            monitorAccess && this.startRecordDependencies(false);
            try {
                key = this.keyGenFunc_(item, index);
            } catch {
                stateMgmtConsole.applicationError(`${this.constructor.name}(${this.repeatElmtId_}):`,
                    `unstable key function. Fix the key gen function in your application!`);
                key = this.mkRandomKey(index, '_key-gen-crashed_');
            }
            monitorAccess && this.stopRecordDependencies();

            const optIndex1: number | undefined = this.index4Key_.get(key);
            if (optIndex1 !== undefined || this.oldDuplicateKeys_.has(key)) {
                key = this.handleDuplicateKey(index, key, optIndex1, activateDataItems);
            } else {
                this.key4Index_.set(index, key);
                this.index4Key_.set(key, index);
            }
        }
        return key;
    }

    private mkRandomKey(index: number, origKey: string): string {
        return `___${index}_+_${origKey}_+_${Math.random()}`;
    }

    // when generating key for index2, detected that index1 has same key already
    // need to change the key for both index'es
    // returns random key for index 2
    private handleDuplicateKey(curIndex: number, origKey: string, prevIndex?: number,
        activateDataItems?: Array<ActiveDataItem<void | T>>): string {
        this.oldDuplicateKeys_.add(origKey);

        const curKey = this.mkRandomKey(curIndex, origKey);
        this.key4Index_.set(curIndex, curKey);
        this.index4Key_.set(curKey, curIndex);

        if (prevIndex !== undefined) {
            // also make a new key for prevIndex
            const prevKey = this.mkRandomKey(prevIndex, origKey);
            this.key4Index_.set(prevIndex, prevKey);
            this.index4Key_.set(prevKey, prevIndex);
            this.index4Key_.delete(origKey);
            if (activateDataItems && activateDataItems[prevIndex] !== undefined) {
                stateMgmtConsole.debug(`correcting key of activeDataItem index ${prevIndex} from `,
                    `'${activateDataItems[prevIndex].key}' to '${prevKey}'.`);
                activateDataItems[prevIndex].key = prevKey;
            }
        }
        stateMgmtConsole.applicationError(`${this.constructor.name}(${this.repeatElmtId_}): `,
            `Detected duplicate key for index ${curIndex}! `,
            `Generated random key will decrease Repeat performance. Fix the key gen function in your application!`);
        return curKey;
    }

    /**
     * called from C++ GetFrameChild whenever need to create new node and add to L1 
     * or update spare node and add back to L1
     *
     * @param forIndex 
     * @returns 
     */
    private onGetRid4Index(forIndex: number): [number, number] {
        if (forIndex < 0 || forIndex >= this.totalCount()) {
            throw new Error(`${this.constructor.name}(${this.repeatElmtId_}) onGetRid4Index index ${forIndex}` +
                `\ndata array length: ${this.arr_.length}, totalCount: ${this.totalCount()}: ` +
                `Out of range, application error.`);
        }
        const [dataItemExists, dataItem] = this.getItemUnmonitored(forIndex);
        if (!dataItemExists) {
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) `,
                `onGetRid4Index index ${forIndex} - missing data item.`);
            this.activeDataItems_[forIndex] = ActiveDataItem.createMissingDataItem();
            return [0, /* failed to create or update */ 0];
        }

        const ttype = this.computeTtype(dataItem, forIndex, /* enable monitored access */ true);
        const key = this.computeKey(dataItem, forIndex, /* monitor access*/ true, this.activeDataItems_);
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onGetRid4Index index ${forIndex}, `,
            `ttype is '${ttype}' data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - start`);

        // spare UINode / RID available to update?
        const optRid = this.canUpdateTryMatch(ttype, dataItem, key);

        const result: [number, number] = (optRid > 0)
            ? this.updateChild(optRid, ttype, forIndex, key)
            : this.createNewChild(forIndex, ttype, key);

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onGetRid4Index index ${forIndex} `,
            `ttype is '${ttype}' data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - DONE`);
        return result;
    }

    // return RID of Node that can be updated (matching ttype), 
    // or -1 if none
    private canUpdate(ttype: string): number {
        if (!this.allowUpdate_) {
            return -1;
        }
        for (const rid of this.spareRid_) {
            const ridMeta = this.meta4Rid_.get(rid);
            if (ridMeta && ridMeta.ttype_ === ttype) {
                stateMgmtConsole.debug(`canUpdate: Found spare rid ${rid} for ttype '${ttype}'`);
                return rid;
            }
        }
        stateMgmtConsole.debug(`canUpdate: Found NO spare rid for ttype '${ttype}'`);
        return -1;
    }

    // return RID of Node that can be updated (matching ttype), 
    // or -1 if none
    private canUpdateTryMatch(ttype: string, dataItem: T, key?: string): number {
        if (!this.allowUpdate_) {
            return -1;
        }
        // 1. round: find matching RID, also data item matches
        for (const rid of this.spareRid_) {
            const ridMeta = this.meta4Rid_.get(rid);
            // compare ttype and data item, or ttype and key
            if (ridMeta && ridMeta.ttype_ === ttype &&
                ((!this.useKeys_ && ridMeta.repeatItem_?.item === dataItem) ||
                (this.useKeys_ && ridMeta.key_ === key))) {
                stateMgmtConsole.debug(
                    `canUpdateTryMatch: Found spare rid ${rid} for ttype '${ttype}' contentItem matches.`);
                return rid;
            }
        }

        // just find a matching RID
        for (const rid of this.spareRid_) {
            const ridMeta = this.meta4Rid_.get(rid);
            if (ridMeta && ridMeta.ttype_ === ttype) {
                stateMgmtConsole.debug(`canUpdateTryMatch: Found spare rid ${rid} for ttype '${ttype}'`);
                return rid;
            }
        }
        stateMgmtConsole.debug(`canUpdateTryMatch: Found NO spare rid for ttype '${ttype}'`);
        return -1;
    }

    /**
     * crete new Child node onto the ViewStackProcessor
     *
     * @param forIndex 
     * @param ttype 
     * @returns [ success, 1 for new node created ]
     */
    private createNewChild(forIndex: number, ttype: string, key?: string): [number, number] {
        let itemGenFunc = this.itemGenFuncs_[ttype];
        this.startRecordDependencies();

        // item exists in arr_, has been checked before
        const [_, dataItem] = this.getItemUnmonitored(forIndex);
        const repeatItem = this.mkRepeatItem_(dataItem, forIndex) as __RepeatItemV2<T>;
        const rid = this.nextRid++;

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) createNewChild index ${forIndex} -> `,
            `new rid ${rid} / ttype ${ttype}, key ${key} - data array length: ${this.arr_.length}, `,
            `totalCount: ${this.totalCount()} - start`);

        try {
            // execute item builder function
            const isTemplate: boolean = (ttype !== RepeatEachFuncTtype);
            itemGenFunc(repeatItem);
            RepeatVirtualScroll2Native.setCreateByTemplate(isTemplate);
        } catch (e) {
            this.stopRecordDependencies();
            
            stateMgmtConsole.applicationError(`${this.constructor.name}(${this.repeatElmtId_}) `,
                `initialRenderChild(forIndex: ${forIndex}, templateId: '${ttype}') -> RID ${rid}: `,
                `data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - `,
                `item initial render failed!`);
            this.activeDataItems_[forIndex] = ActiveDataItem.createFailedToCreateUINodeDataItem(this.arr_[forIndex]);
            return [0, /* did not success creating new UINode */ 0];
        }

        // do any items have bindings with their indexes?
        // // this.hasItemBindingsToIndex_ ||= repeatItem.hasBindingToIndex();

        // a new UINode subtree, create a new rid -> RepeatItem, ttype, key
        this.meta4Rid_.set(rid, new RIDMeta(repeatItem, ttype, key));
        this.activeDataItems_[forIndex] = ActiveDataItem.createWithUINode(this.arr_[forIndex], rid, ttype, key);

        this.stopRecordDependencies();

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) createNewChild index ${forIndex} -> `,
            `new rid ${rid} / ttype ${ttype}, key ${key} - data array length: ${this.arr_.length}, `,
            `totalCount: ${this.totalCount()} - done`);
        return [rid, /* created new UINode successfully */ 1];
    }

    /**
    * update given rid / RepeatItem to data item of given index
    *
    * @param rid 
    * @param ttype 
    * @param forIndex 
    * @returns [ success, 2 for updated existing node ]
    */
    private updateChild(rid: number, ttype: string, forIndex: number, key?: string): [number, number] {
        const ridMeta = this.meta4Rid_.get(rid);
        if (!ridMeta || !ridMeta.repeatItem_) {
            // error
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) `,
                `updateChild(forIndex: ${forIndex}, templateId: ${ttype}) <- RID ${rid}: `,
                `data array length: ${this.arr_.length}, totalCount: ${this.totalCount()}. `,
                `Failed to find RepeatItem. Internal error!.`);
            this.activeDataItems_[forIndex] = ActiveDataItem.createFailedToCreateUINodeDataItem(this.arr_[forIndex]);
            return [0, /* failed to update */ 0];
        }

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) updateChild`,
            `(forIndex: ${forIndex}, templateId: ${ttype}) <- RID ${rid}, key: ${key}: `,
            `data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - start`);

        // item exists in arr_, has been checked before
        const [_, dataItem] = this.getItemMonitored(forIndex);

        // rid is taken, move out of spare Set
        this.spareRid_.delete(rid);
        this.activeDataItems_[forIndex] = ActiveDataItem.createWithUINode(dataItem, rid, ttype, key);
        if (this.useKeys_ && key !== undefined) {
            // rid, repeatItem, ttype are constant, but key changes in ridMeta on child update
            ridMeta.key_ = key;
        }

        if (ridMeta.repeatItem_.item !== dataItem || ridMeta.repeatItem_.index !== forIndex) {
            // repeatItem needs update, will trigger partial update to using UINodes:
            ridMeta.repeatItem_.updateItem(dataItem);
            ridMeta.repeatItem_.updateIndex(forIndex);

            ObserveV2.getObserve().updateDirty2(/* update synchronously */ true);
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) updateChild`,
                `(forIndex: ${forIndex}, templateId: ${ttype}) <- RID ${rid}, key: ${key}: `,
                `update has been done - done`);
        } else {
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) updateChild`,
                `(forIndex: ${forIndex}, templateId: ${ttype}) <- RID ${rid}, key: ${key}: `,
                `item and index value as in spare, no update needed - done`);
        }

        return [rid, /* update success */ 2];
    }

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
    private onRecycleItems(fromIndex: number, toIndex: number): void {
        // avoid negative fromIndex
        fromIndex = Math.max(0, fromIndex);
        for (let index = fromIndex; index < toIndex; index++) {
            // when ListItem is being dragged without dropping, index will be mapped.
            let indexMapped = this.convertFromToIndex(index);
            if (indexMapped >= this.totalCount() || !(indexMapped in this.activeDataItems_)) {
                continue;
            }
            if (this.activeDataItems_[indexMapped].state === ActiveDataItem.UINodeExists) {
                this.dropFromL1ActiveNodes(indexMapped);
            }
        }
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onRecycleItems(${fromIndex}...<${toIndex})`,
            `after applying changes:\n${this.dumpSpareRid()}\n${this.dumpDataItems()}`);
    }

    private onMoveFromTo(moveFrom: number, moveTo: number): void {
        moveFrom = Math.trunc(moveFrom);
        moveTo = Math.trunc(moveTo);
        if (!this.isNonNegative(moveFrom) || !this.isNonNegative(moveTo)) {
            this.moveFromTo_ = undefined;
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onMoveFromTo param invalid,`,
                `reset moveFromTo.`);
            return;
        }
        if (this.moveFromTo_) {
            this.moveFromTo_[1] = moveTo;
            if (this.moveFromTo_[1] === this.moveFromTo_[0]) {
                this.moveFromTo_ = undefined;
            }
        } else {
            this.moveFromTo_ = [moveFrom, moveTo];
        }
        if (this.moveFromTo_) {
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onMoveFromTo updated`,
                `(${this.moveFromTo_[0]}, ${this.moveFromTo_[1]})`);
        } else {
            stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onMoveFromTo data moved`,
                `to original pos, reset moveFromTo.`);
        }
    }

    private isNonNegative(index: number): boolean {
        return (Number.isFinite(index) && index >= 0);
    }

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
    private convertFromToIndex(index: number): number {
        if (!this.moveFromTo_) {
            return index;
        }
        if (this.moveFromTo_[1] === index) {
            return this.moveFromTo_[0];
        }
        if (this.moveFromTo_[0] <= index && index < this.moveFromTo_[1]) {
            return index + 1;
        }
        if (this.moveFromTo_[1] < index && index <= this.moveFromTo_[0]) {
            return index - 1;
        }
        return index;
    }

    // used for onActiveRange. Specific instructions are provided above.
    private convertFromToIndexRevert(index: number): number {
        if (!this.moveFromTo_) {
            return index;
        }
        if (this.moveFromTo_[0] === index) {
            return this.moveFromTo_[1];
        }
        if (this.moveFromTo_[0] < index && index <= this.moveFromTo_[1]) {
            return index - 1;
        }
        if (this.moveFromTo_[1] <= index && index < this.moveFromTo_[0]) {
            return index + 1;
        }
        return index;
    }

    private dropFromL1ActiveNodes(index: number, invalidate: boolean = true): boolean {
        if (!(index in this.activeDataItems_)) {
            return false;
        }

        const rid: number | undefined = this.activeDataItems_[index].rid;
        const ttype: string | undefined = this.activeDataItems_[index].ttype;

        // delete makes array item empty, does not re-index.
        delete this.activeDataItems_[index];
        this.index4Key_.delete(this.key4Index_.get(index));
        this.key4Index_.delete(index);

        if (rid === undefined || ttype === undefined) {
            // data item is not rendered, yet
            stateMgmtConsole.debug(`dropFromL1ActiveNodes index: ${index} no rid ${rid} or no ttype `,
                `'${ttype ? ttype : 'undefined'}'. Dropping un-rendered item silently.`);
            return false;
        }

        // add to spare rid Set
        this.spareRid_.add(rid);

        if (invalidate) {
            stateMgmtConsole.debug(`dropFromL1ActiveNodes index: ${index} - rid: ${rid}/ttype: '${ttype}' `,
                `- spareRid: ${this.dumpSpareRid()} - invalidate in RepeatVirtualScroll2Node ...`);
            // call RepeatVirtualScroll2Caches::SetInvalid
            RepeatVirtualScroll2Native.setInvalid(this.repeatElmtId_, rid);
        } else {
            stateMgmtConsole.debug(`dropFromL1ActiveNodes index: ${index} - rid: ${rid}/ttype: '${ttype}' `,
                `- spareRid: ${this.dumpSpareRid()}`);
        }

        return true;
    }

    private onActiveRange(nStart: number, nEnd: number, vStart: number, vEnd: number, isLoop: boolean,
        forceUpdate: boolean): void {
        if (Number.isNaN(this.activeRange_[0])) {
            // first call to onActiveRange / no active node
            this.activeRange_ = [nStart, nEnd];
            this.visibleRange_ = [vStart, vEnd];
            this.activeRangeAdjustedStart_ = nStart;
            this.visibleRangeAdjustedStart_ = vStart;
        } else if (this.activeRange_[0] === nStart && this.activeRange_[1] === nEnd) {
            if (this.visibleRange_[0] !== vStart || this.visibleRange_[1] !== vEnd) {
                stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onActiveRange`,
                    `update visibleRange_ (vStart: ${vStart}, vEnd: ${vEnd})`);
                this.visibleRange_ = [vStart, vEnd];
                this.visibleRangeAdjustedStart_ = vStart;
            }
            if (!isLoop && !forceUpdate) {
                stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onActiveRange`,
                    `(nStart: ${nStart}, nEnd: ${nEnd})`,
                    `data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - unchanged, skipping.`);
                return;
            }
        }

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) onActiveRange`,
            `(nStart: ${nStart}, nEnd: ${nEnd}), (start: ${vStart}, end: ${vEnd})`,
            `data array length: ${this.arr_.length}, totalCount: ${this.totalCount()} - start`);

        // check which of the activeDataItems needs to be removed from L1 & activeDataItems
        let numberOfActiveItems = 0;
        for (let index = 0; index < this.activeDataItems_.length; index++) {
            // when ListItem is being dragged without dropping, index will be mapped.
            let indexMapped = this.convertFromToIndexRevert(index);
            if (!(index in this.activeDataItems_)) {
                continue;
            }

            // same condition as in C++ RepeatVirtualScroll2Node::CheckNode4IndexInL1
            let remainInL1 = (nStart <= indexMapped && indexMapped <= nEnd);
            if (isLoop) {
                remainInL1 = remainInL1 ||
                    (nStart > nEnd && (nStart <= index || index <= nEnd)) ||
                    (nStart < 0 && index >= nStart + this.totalCount()) ||
                    (nEnd >= this.totalCount() && index <= nEnd - this.totalCount());
            }
            stateMgmtConsole.debug(`index: ${index}: ${remainInL1 ? 'keep in L1' : 'drop from L1'}`,
                `dataItem: ${this.activeDataItems_[index].dump()}`);

            if (remainInL1) {
                if (this.activeDataItems_[index].state === ActiveDataItem.UINodeExists) {
                    numberOfActiveItems += 1;
                }
            } else {
                if (this.activeDataItems_[index].state === ActiveDataItem.UINodeExists) {
                    this.dropFromL1ActiveNodes(index, /* call C++ RepeatVirtualScroll2Caches::SetInvalid */ false);
                }
            }
        }

        // memorize
        this.activeRange_ = [nStart, nEnd];
        this.visibleRange_ = [vStart, vEnd];
        this.activeRangeAdjustedStart_ = nStart;
        this.visibleRangeAdjustedStart_ = vStart;

        stateMgmtConsole.debug(`onActiveRange Result: number remaining activeItems ${numberOfActiveItems}.`,
            `\n${this.dumpDataItems()}\n${this.dumpSpareRid()}\n${this.dumpRepeatItem4Rid()}`);

        // adjust dynamic cachedCount for each template type that is using dynamic cached count
        stateMgmtConsole.debug(`templateOptions_ ${JSON.stringify(this.templateOptions_)}`);
        Object.entries(this.templateOptions_).forEach((pair) => {
            const options: RepeatTemplateImplOptions = pair[1];
            if (!options.cachedCountSpecified) {
                options.cachedCount = Number.isInteger(options.cachedCount)
                    ? Math.max(numberOfActiveItems, options.cachedCount)
                    : numberOfActiveItems;
            }
        });
        stateMgmtConsole.debug(this.dumpCachedCount());
    }

    // handles circular ranges by normalizing the start and end values within
    // the circular range [-totalCount, +totalCount]
    private isIndexInRange(index: number, start: number, end: number, totalCount = this.totalCount()): boolean {
        // to codechecker: yes, need switch to math names here
        let [i, a, b, n] = [index, start, end, totalCount];

        // convert all indices to range [0, n-1], e.g. [-1] should become [0]
        a = ((a >= 0) ? a : Math.abs(a + 1)) % n;
        b = ((b >= 0) ? b : Math.abs(b + 1)) % n;

        // shift values so that 'start' ('a') becomes 0
        i = (i - a + n) % n;
        b = (b - a + n) % n;

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) isIndexInRange:`,
            `${index} in [${start}, ${end}] totalCount=${this.totalCount()} =>`, i <= b);
        return i <= b;
    }

    private hasOverlapWithActiveRange(startIndex: number, endIndex: number): boolean {
        // ensure we are not out of bounds
        const start = Math.min(startIndex, this.totalCount() - 1);
        const end = Math.min(endIndex, this.totalCount() - 1);

        // ranges ovelap if at least one boundary of one range is inside the other
        return this.isIndexInRange(start, this.activeRange_[0], this.activeRange_[1]) ||
            this.isIndexInRange(end, this.activeRange_[0], this.activeRange_[1]) ||
            this.isIndexInRange(this.activeRange_[0], start, end) ||
            this.isIndexInRange(this.activeRange_[1], start, end);
    }

    private needRerenderChange(changeIndex: number, deleteCount: number, addCount: number): boolean {
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) needRerenderChange(${changeIndex},`,
            `${deleteCount}, ${addCount}), activeRange:`, ...this.activeRange_);

        // 0. Looping detected. We're in Swiper or another fancy container, need rerender
        if (this.activeRange_[1] < this.activeRange_[0]) {
            stateMgmtConsole.debug(`needRerenderChange (0) return`, true);
            return true;
        }

        // 1. All changed or shifted items are behind the end of the activeRange, no need rerender
        if (changeIndex > this.activeRange_[1]) {
            stateMgmtConsole.debug(`needRerenderChange (1) return`, false);
            return false;
        }

        // 2. New items have added within the activeRange, need rerender
        if (this.hasOverlapWithActiveRange(changeIndex, changeIndex + addCount)) {
            stateMgmtConsole.debug(`needRerenderChange (2) return`, true);
            return true;
        }

        // 3. All changes are before the active range, no shifts
        if (deleteCount === addCount) {
            stateMgmtConsole.debug(`needRerenderChange (3) return`, false);
            return false;
        }

        // 4. Items in the activeRange have only shifted. If there are no index-dependent items,
        // no need rerender

        // Keep the code below commented out until FrameNode::NotifyChange is fixed
        // // let hasDependencyOnIndex = true;
        // // has dependency on index in itemgen func ?
        // // hasDependencyOnIndex = this.hasItemBindingsToIndex_;
        // // has dependency on index in typegen func ?
        // // hasDependencyOnIndex ||= (this.ttypeGenFunc_?.length >= 2);
        // // has dependency on index in keygen func ?
        // // hasDependencyOnIndex ||= (this.keyGenFunc_?.length >= 2);

        // // if (!hasDependencyOnIndex) {
        // //     stateMgmtConsole.debug(`needRerenderChange (4) return`, false);
        // //     return false;
        // // }

        stateMgmtConsole.debug(`needRerenderChange return`, true);
        return true;
    }

    // update this.activeRangeAdjustedStart_
    private adjustActiveRangeStart(index: number, deleteCount: number, addCount: number): void {
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_})`,
            `adjustActiveRangeStart(${index}, ${deleteCount}, ${addCount})`);

        // If activeRange_ is not yet known, do nothing
        if (isNaN(this.activeRangeAdjustedStart_) || isNaN(this.visibleRangeAdjustedStart_)) {
            this.activeRangeAdjustedStart_ = this.activeRange_[0];
            this.visibleRangeAdjustedStart_ = this.visibleRange_[0];
        }
        if (isNaN(this.activeRangeAdjustedStart_) || isNaN(this.visibleRangeAdjustedStart_)) {
            return;
        }

        // count changes before visible range
        if (index <= this.visibleRangeAdjustedStart_) {
            this.visibleRangeAdjustedStart_ -= Math.min(deleteCount, this.visibleRangeAdjustedStart_ - index);
            this.visibleRangeAdjustedStart_ += addCount;
        }

        // count changes before active range
        if (index <= this.activeRangeAdjustedStart_) {
            this.activeRangeAdjustedStart_ -= Math.min(deleteCount, this.activeRangeAdjustedStart_ - index);
            this.activeRangeAdjustedStart_ += addCount;
        }

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_})`,
            `activeRangeAdjustedStart_ = ${this.activeRangeAdjustedStart_}`,
            `visibleRangeAdjustedStart_ = ${this.visibleRangeAdjustedStart_}`);
    }

    // Return false if a regular re-render is required. Otherwise, only notify the container
    // about a layout change and schedule a re-layout
    public tryFastRelayout(arrChange: string, args: Array<unknown>): boolean {
        // if rerender is already running, just skip everything
        if (this.rerenderOngoing_) {
            return true;
        }
        
        if (this.lazyLoadingIndex_ !== -1 && arrChange !== 'set') {
            const msg = `onLazyLoading function executed illegal operation: ${arrChange}!`;
            throw new Error(`${this.constructor.name}(${this.repeatElmtId_}) ${msg}`);
        }

        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) tryFastRelayout for '${arrChange}'`,
            `args: ${args}, activeRange: ${this.activeRange_}, visibleRange: ${this.visibleRange_}`);

        // Note that the change in the array has already been done!
        // Now our activeRange reflects the array before the change
        // and this.arr_.length is the change after the change!

        if (arrChange === 'push') {
            const originalLength = this.arr_.length - args.length;
            return this.tryFastRelayoutForChange(originalLength, this.arr_.length - args.length, 0, args.length);
        }

        if (arrChange === 'pop') {
            const originalLength = this.arr_.length + 1;
            return this.tryFastRelayoutForChange(originalLength, this.arr_.length, 1, 0);
        }

        if (arrChange === 'shift') {
            const originalLength = this.arr_.length + 1;
            return this.tryFastRelayoutForChange(originalLength, 0, 1, 0);
        }

        if (arrChange === 'unshift') {
            const originalLength = this.arr_.length - args.length;
            return this.tryFastRelayoutForChange(originalLength, 0, 0, args.length);
        }

        if (arrChange === 'splice') {
            // first parameter contains original array length before splice
            const [originalLength, index = undefined, deleteCount = undefined, ...items] = args as number[];
            return this.tryFastRelayoutForChange(originalLength, index, deleteCount, items.length);
        }

        if (arrChange === 'set') {
            const changeIndex = args[0] as number;
            if (this.lazyLoadingIndex_ !== -1 && changeIndex !== this.lazyLoadingIndex_) {
                const msg = `onLazyLoading function illegally set to index: ${changeIndex}`;
                throw new Error(`${this.constructor.name}(${this.repeatElmtId_}) ${msg}`);
            }
            return (changeIndex >= 0) && this.tryFastRelayoutForChange(this.arr_.length, changeIndex, 0, 0);
        }

        // discard nextTickTask if it's scheduled
        this.nextTickTask_ &&= NOOP;
        return false;
    }

    private tryFastRelayoutForChange(originalLength: number, index: number | undefined, 
        deleteCount: number | undefined, addCount: number): boolean {

        // array hasn't changed, render is not needed
        if (index === undefined && deleteCount === undefined && addCount === 0) {
            return true;
        }

        // normalize index
        let nIndex = index ?? 0;
        if (nIndex < 0) {
            nIndex = Math.max(nIndex + originalLength, 0);
        }
        if (nIndex > originalLength) {
            nIndex = originalLength;
        }

        // normalize deleteCount
        let nDeleteCount = deleteCount ?? (originalLength - nIndex);
        nDeleteCount = Math.min(nDeleteCount, originalLength - nIndex);
        nDeleteCount = Math.max(nDeleteCount, 0);

        return this.tryFastRelayoutForChangeNormalized(nIndex, nDeleteCount, addCount);
    }

    private tryFastRelayoutForChangeNormalized(index: number, deleteCount: number, addCount: number): boolean {
        // update accumulated active-range offset here
        this.adjustActiveRangeStart(index, deleteCount, addCount);

        if (this.lazyLoadingIndex_ === -1 && this.needRerenderChange(index, deleteCount, addCount)) {
            // discard nextTickTask if it's scheduled
            this.nextTickTask_ &&= NOOP;
            this.updateFirstIndexChangedInTryFastRelayout(index);
            return false;
        }

        if (deleteCount !== addCount) {
            // forcibly retrieve totalCount (needed only when 'totalCount' option is used)
            this.totalCount(true);
        }

        // schedule microtask to run after all synchronous array updates
        if (this.nextTickTask_ === undefined) {
            Promise.resolve().then(() => {
                this.nextTickTask_?.();
                this.nextTickTask_ = undefined;
            });
            this.nextTickTask_ = () : void => {
                stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}), nextTickTask()`);
                this.notifyContainerLayoutChangeAcc();
                this.requestContainerReLayout();
            };
        }

        return true;
    }

    private updateFirstIndexChangedInTryFastRelayout(index: number): void {
        if (isNaN(this.firstIndexChangedInTryFastRelayout_)) {
            this.firstIndexChangedInTryFastRelayout_ = index;
        } else {
            this.firstIndexChangedInTryFastRelayout_ = Math.min(this.firstIndexChangedInTryFastRelayout_, index);
        }
    }

    private notifyContainerLayoutChangeAcc(): boolean {
        const changeCount = this.visibleRangeAdjustedStart_ - this.visibleRange_[0];
        if (isNaN(changeCount) || changeCount === 0) {
            return false;
        }

        // get changeIndex to notify container with accumulated changes
        let changeIndex = (changeCount < 0) ? 0 : this.visibleRange_[0];

        // tells the container to adjust the scroll position, exact behavior is determined by
        // List.maintainVisibleContentPosition(bool)
        this.notifyContainerLayoutChange(changeIndex, changeCount);
        this.visibleRangeAdjustedStart_ = NaN;
        this.activeRangeAdjustedStart_ = NaN;
        return true;
    }

    private notifyContainerLayoutChange(changeIndex: number, changeCount: number,
        notificationType = NotificationType.END_CHANGE_POSITION): void {
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_})`,
            `notifyContainerLayoutChange(${changeIndex}, ${changeCount}, ${NotificationType[notificationType]})`);

        const arrLen = this.onLazyLoadingFunc_ ? this.totalCount() : this.arr_.length;
        // triggers FrameNode::NotifyChange in CPP side
        RepeatVirtualScroll2Native.notifyContainerLayoutChange(this.repeatElmtId_, arrLen, this.totalCount(),
            changeIndex, changeCount, notificationType);
    }

    private requestContainerReLayout(changeIndex?: number): void {
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) requestContainerReLayout`, changeIndex);

        const arrLen = this.onLazyLoadingFunc_ ? this.totalCount() : this.arr_.length;
        // trigger MarkNeedSyncRenderTree, MarkNeedFrameFlushDirty in CPP side
        RepeatVirtualScroll2Native.requestContainerReLayout(this.repeatElmtId_, arrLen, this.totalCount(), changeIndex);
    }

    private onPurge(): void {
        stateMgmtConsole.debug(`${this.constructor.name}(${this.repeatElmtId_}) purge(), totalCount: `,
            `${this.totalCount()} - start`);

        // deep copy templateOptions_
        let availableCachedCount: { [ttype: string]: number } = {};
        Object.entries(this.templateOptions_).forEach((pair) => {
            availableCachedCount[pair[0]] = pair[1].cachedCount as number;
        });

        // Improvement needed:
        // this is a simplistic purge is more or less randomly purges 
        // extra nodes
        // avoid delete on iterated Set, copy into Array
        const spareRid1 : Array<number> = Array.from(this.spareRid_);
        for (const rid of spareRid1) {
            const ridMeta = this.meta4Rid_.get(rid);
            if (!ridMeta) {
                continue;
            }
            const ttype: string = ridMeta.ttype_;
            if (availableCachedCount[ttype] === 0) {
                // purge rid
                this.purgeNode(rid);
            } else {
                availableCachedCount[ttype] -= 1;
            }
        }
        stateMgmtConsole.debug(`onPurge after applying changes: \n${this.dumpSpareRid()}\n${this.dumpDataItems()}`);
    }

    private purgeNode(rid: number): void {
        stateMgmtConsole.debug(`delete node rid: ${rid}.`);
        this.meta4Rid_.delete(rid);
        this.spareRid_.delete(rid);
        RepeatVirtualScroll2Native.removeNode(rid);
    }

    private dumpSpareRid(): string {
        return `spareRid size: ${this.spareRid_.size} ` +
            `${JSON.stringify(Array.from(this.spareRid_).map(rid => `rid: ${rid}`))}.`;
    }

    private dumpRepeatItem4Rid(): string {
        return `meta4Rid_ size: ${this.meta4Rid_.size}: ${JSON.stringify(Array.from(this.meta4Rid_))}.`;
    }

    private dumpDataItems(): string {
        let result = ``;
        let sepa = '';
        let count = 0;
        for (const index in this.activeDataItems_) {
            const dataItemDump = this.activeDataItems_[index].dump();
            const repeatItemIndex = this.activeDataItems_[index].rid
                ? this.meta4Rid_.get(this.activeDataItems_[index].rid)?.repeatItem_?.index
                : 'N/A';
            result += `${sepa}index ${index}, ${dataItemDump} (repeatItemIndex ${repeatItemIndex})`;
            sepa = ', \n';
            count += 1;
        }
        return `activeDataItems(array): length: ${this.activeDataItems_.length}, ` +
            `range: [${this.activeRange_[0]}-${this.activeRange_[1]}], ` +
            `entries count: ${count} =============\n${result}`;
    }

    private dumpCachedCount(): string {
        let result = '';
        let sepa = '';
        Object.entries(this.templateOptions_).forEach((pair) => {
            const options: RepeatTemplateImplOptions = pair[1];
            result += `${sepa}'template ${pair[0]}': specified: ${options.cachedCountSpecified} ` +
                `cachedCount: ${options.cachedCount}: `;
            sepa = ', ';
        });
        return result;
    }

    private dumpKeys(): string {
        let result = '';
        let sepa = '';
        this.key4Index_.forEach((key, index) => {
            result += `${sepa}${index}: ${key}`;
            sepa = '\n';
        });
        return result;
    }
};