/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

// Implements ForEach with child re-use for both existing state observation and
// deep observation. For virtual-scroll code paths

class __RepeatVirtualScrollImpl<T> {
    private arr_: Array<T>;
    private itemGenFuncs_: { [type: string]: RepeatItemGenFunc<T> };
    private keyGenFunc_?: RepeatKeyGenFunc<T>;
    private ttypeGenFunc_?: RepeatTTypeGenFunc<T>;

    private totalCount_: number;
    private totalCountSpecified : boolean = false;
    private templateOptions_: { [type: string]: RepeatTemplateImplOptions };
    private reusable_: boolean = true;

    private mkRepeatItem_: (item: T, index?: number) => __RepeatItemFactoryReturn<T>;
    private onMoveHandler_?: OnMoveHandler;
    private itemDragEventHandler?: ItemDragEventHandler;

    // index <-> key maps
    private key4Index_: Map<number, string> = new Map<number, string>();
    private index4Key_: Map<string, number> = new Map<string, number>();

    // Map key -> RepeatItem
    // added to closure of following lambdas
    private repeatItem4Key_ = new Map<string, __RepeatItemFactoryReturn<T>>();

    // RepeatVirtualScrollNode elmtId
    private repeatElmtId_ : number = -1;

    // Last known active range (as sparse array)
    private lastActiveRangeData_: Array<{ item: T, ttype: string }> = [];

    public render(config: __RepeatConfig<T>, isInitialRender: boolean): void {
        this.arr_ = config.arr;
        this.itemGenFuncs_ = config.itemGenFuncs;
        this.keyGenFunc_ = config.keyGenFunc;
        this.ttypeGenFunc_ = config.ttypeGenFunc;

        // if totalCountSpecified==false, then need to create dependency on array length 
        // so when array length changes, will update totalCount
        this.totalCountSpecified = config.totalCountSpecified;
        this.totalCount_ = (!this.totalCountSpecified || (config.totalCount as number) < 0) 
            ? this.arr_.length
            : config.totalCount as number;

        this.templateOptions_ = config.templateOptions;

        this.mkRepeatItem_ = config.mkRepeatItem;
        this.onMoveHandler_ = config.onMoveHandler;
        this.itemDragEventHandler = config.itemDragEventHandler;

        if (isInitialRender) {
            this.reusable_ = config.reusable;
            if (!this.reusable_) {
                for (let templateType in this.templateOptions_) {
                    this.templateOptions_[templateType] = { cachedCountSpecified: true, cachedCount: 0 };
                }
            }
            this.initialRender(config.owningView_, ObserveV2.getCurrentRecordedId());
        } else {
            this.reRender();
        }
    }

    // wraps a type gen function with validation logic
    private ttypeGenFunc(item: T, index: number): string {
        if (this.ttypeGenFunc_ === undefined) {
            return RepeatEachFuncTtype;
        }
        let ttype = RepeatEachFuncTtype;
        try {
            ttype = this.ttypeGenFunc_(item, index);
        } catch (e) {
            stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl. Error generating ttype at index: ${index}`,
                e?.message);
        }
        if (ttype in this.itemGenFuncs_ === false) {
            stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl. No template found for ttype '${ttype}'`);
            ttype = RepeatEachFuncTtype;
        }
        return ttype;
    }

    /**/
    private initialRender(
        owningView: ViewV2, 
        repeatElmtId: number
    ): void {

        this.repeatElmtId_ = repeatElmtId;

        const onCreateNode = (forIndex: number): void => {
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onCreateNode index ${forIndex} - start`);
            if (forIndex < 0 || forIndex >= this.totalCount_ || forIndex >= this.arr_.length) {
                // STATE_MGMT_NOTE check also index < totalCount
                throw new Error(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onCreateNode: for index=${forIndex}  \
                    with data array length ${this.arr_.length}, totalCount=${this.totalCount_}  out of range error.`);
            }

            // create dependency array item [forIndex] -> Repeat
            // so Repeat updates when the array item changes
            // STATE_MGMT_NOTE observe dependencies, adding the array is insurgent for Array of objects
            ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, forIndex.toString());

            const repeatItem = this.mkRepeatItem_(this.arr_[forIndex], forIndex);
            let forKey = this.getOrMakeKey4Index(forIndex);
            this.repeatItem4Key_.set(forKey, repeatItem);

            // execute the itemGen function
            this.initialRenderItem(repeatItem);
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onCreateNode for index ${forIndex} key "${forKey}" - end`);
        }; // onCreateNode

        const onUpdateNode = (fromKey: string, forIndex: number): void => {
            if (!fromKey || fromKey === '' || forIndex < 0 || forIndex >= this.totalCount_ || forIndex >= this.arr_.length) {
                throw new Error(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onUpdateNode: fromKey "${fromKey}", \
                    forIndex=${forIndex}, with data array length ${this.arr_.length}, totalCount=${this.totalCount_}, invalid function input error.`);
            }
            // create dependency array item [forIndex] -> Repeat
            // so Repeat updates when the array item changes
            // STATE_MGMT_NOTE observe dependencies, adding the array is insurgent for Array of objects
            ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, forIndex.toString());
            const repeatItem = this.repeatItem4Key_.get(fromKey);
            if (!repeatItem) {
                stateMgmtConsole.error(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onUpdateNode: \
                    forIndex=${forIndex}, can not find RepeatItem for key. Unrecoverable error.`);
                return;
            }
            const forKey = this.getOrMakeKey4Index(forIndex);
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onUpdateNode: fromKey "${fromKey}", \
                forIndex=${forIndex} forKey="${forKey}". Updating RepeatItem ...`);

            // update Map according to made update:
            // del fromKey entry and add forKey
            this.repeatItem4Key_.delete(fromKey);
            this.repeatItem4Key_.set(forKey, repeatItem);

            if (repeatItem.item !== this.arr_[forIndex] || repeatItem.index !== forIndex) {
                // repeatItem needs update, will trigger partial update to using UINodes:
                repeatItem.updateItem(this.arr_[forIndex]);
                repeatItem.updateIndex(forIndex);

                stateMgmtConsole.debug(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onUpdateNode: fromKey "${fromKey}", \
                    forIndex=${forIndex} forKey="${forKey}". Initiating UINodes update synchronously ...`);
                ObserveV2.getObserve().updateDirty2(true);
            }
        }; // onUpdateNode

        const onGetKeys4Range = (from: number, to: number): Array<string> => {
            if (to > this.totalCount_ || to > this.arr_.length) {
                stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onGetKeys4Range: \
                    from ${from} to ${to} with data array length ${this.arr_.length}, totalCount=${this.totalCount_} \
                    Error!. Application fails to add more items to source data array on time. Trying with corrected input parameters ...`);
                to = this.totalCount_;
                from = Math.min(to, from);
            }
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: onGetKeys4Range from ${from} to ${to} - start`);
            const result = new Array<string>();

            // deep observe dependencies,
            // create dependency array item [i] -> Repeat
            // so Repeat updates when the array item or nested objects changes
            // not enough: ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, i.toString());
            ViewStackProcessor.StartGetAccessRecordingFor(this.repeatElmtId_);
            ObserveV2.getObserve().startRecordDependencies(owningView, this.repeatElmtId_, false);
            for (let i = from; i <= to && i < this.arr_.length; i++) {
                result.push(this.getOrMakeKey4Index(i));
            }
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();

            let needsRerender = false;
            result.forEach((key, index) => {
                const forIndex = index + from;
                // if repeatItem exists, and needs update then do the update, and call sync update as well
                // thereby ensure cached items are up-to-date on C++ side. C++ does not need to request update 
                // from TS side 
                const repeatItem4Key = this.repeatItem4Key_.get(key);
                // make sure the index is up-to-date
                if (repeatItem4Key && (repeatItem4Key.item !== this.arr_[forIndex] || repeatItem4Key.index !== forIndex)) {
                    // repeatItem needs update, will trigger partial update to using UINodes:
                    repeatItem4Key.updateItem(this.arr_[forIndex]);
                    repeatItem4Key.updateIndex(forIndex);
                    needsRerender = true;
                }
            }); // forEach

            if (needsRerender) {
                stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}) onGetKeys4Range: \
                    Initiating UINodes update synchronously ...`);
                ObserveV2.getObserve().updateDirty2(true);
            }

            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}): onGetKeys4Range \
                from ${from} to ${to} - returns ${result.toString()}`);
            return result;
        }; // const onGetKeys4Range 

        const onGetTypes4Range = (from: number, to: number): Array<string> => {
            if (to > this.totalCount_ || to > this.arr_.length) {
                stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onGetTypes4Range: \
                    from ${from} to ${to} with data array length ${this.arr_.length}, totalCount=${this.totalCount_} \
                    Error! Application fails to add more items to source data array on time. Trying with corrected input parameters ...`);
                to = this.totalCount_;
                from = Math.min(to, from);
            }
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}): onGetTypes4Range from ${from} to ${to} - start`);
            const result = new Array<string>();

            // deep observe dependencies,
            // create dependency array item [i] -> Repeat
            // so Repeat updates when the array item or nested objects changes
            // not enough: ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, i.toString());
            ViewStackProcessor.StartGetAccessRecordingFor(this.repeatElmtId_);
            ObserveV2.getObserve().startRecordDependencies(owningView, this.repeatElmtId_, false);

            for (let i = from; i <= to && i < this.arr_.length; i++) {
                let ttype = this.ttypeGenFunc(this.arr_[i], i);
                result.push(ttype);
            } // for
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();

            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}): onGetTypes4Range \
                from ${from} to ${to} - returns ${result.toString()}`);
            return result;
        }; // const onGetTypes4Range

        const onSetActiveRange = (from: number, to: number): void => {
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: onSetActiveRange(${from}, ${to}).`);
            // make sparse copy of this.arr_
            this.lastActiveRangeData_ = new Array<{item: T, ttype: string}>(this.arr_.length);

            if (from <= to) {
                for (let i = Math.max(0, from); i <= to && i < this.arr_.length; i++) {
                    const item = this.arr_[i];
                    const ttype = this.ttypeGenFunc(this.arr_[i], i);
                    this.lastActiveRangeData_[i] = { item, ttype };
                }
            } else {
                for (let i = 0; i <= to && i < this.arr_.length; i++) {
                    const item = this.arr_[i];
                    const ttype = this.ttypeGenFunc(this.arr_[i], i);
                    this.lastActiveRangeData_[i] = { item, ttype };
                }
                for (let i = Math.max(0, from); i < this.arr_.length; i++) {
                    const item = this.arr_[i];
                    const ttype = this.ttypeGenFunc(this.arr_[i], i);
                    this.lastActiveRangeData_[i] = { item, ttype };
                }
            }

            if (!this.reusable_) {
                this.updateRepeatItem4Key(from, to);
            }
        };

        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}): initialRenderVirtualScroll ...`);

        RepeatVirtualScrollNative.create(this.totalCount_, Object.entries(this.templateOptions_), {
            onCreateNode,
            onUpdateNode,
            onGetKeys4Range,
            onGetTypes4Range,
            onSetActiveRange
        }, this.reusable_);
        RepeatVirtualScrollNative.onMove(this.onMoveHandler_, this.itemDragEventHandler);
        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}): initialRenderVirtualScroll`);
    }

    private reRender(): void {
        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl(${this.repeatElmtId_}): reRender ...`);

        // When this.totalCount_ == 0 need render to clear visible items
        if (this.hasVisibleItemsChanged() || this.totalCount_ === 0) {
            this.purgeKeyCache();
            RepeatVirtualScrollNative.updateRenderState(this.totalCount_, true);
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: reRender - done.`);
        } else {
            // avoid re-render when data pushed outside visible area
            RepeatVirtualScrollNative.updateRenderState(this.totalCount_, false);
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: reRender (no changes in visible items) - done.`);
        }
    }

    private initialRenderItem(repeatItem: __RepeatItemFactoryReturn<T>): void {
        // execute the itemGen function
        const itemType = this.ttypeGenFunc(repeatItem.item, repeatItem.index);
        const isTemplate: boolean = (itemType !== '');
        const itemFunc = this.itemGenFuncs_[itemType];
        itemFunc(repeatItem);
        RepeatVirtualScrollNative.setCreateByTemplate(isTemplate);
    }

    private hasVisibleItemsChanged(): boolean {
        // has any item or ttype in the active range changed?
        for (let i in this.lastActiveRangeData_) {
            if (!(i in this.arr_)) {
                return true;
            }
            const oldItem = this.lastActiveRangeData_[+i]?.item;
            const oldType = this.lastActiveRangeData_[+i]?.ttype;
            const newItem = this.arr_[+i];
            const newType = this.ttypeGenFunc(this.arr_[+i], +i);

            if (oldItem !== newItem) {
                stateMgmtConsole.debug(`__RepeatVirtualScrollImpl.hasVisibleItemsChanged() i:#${i} item changed => true`);
                return true;
            }
            if (oldType !== newType) {
                stateMgmtConsole.debug(`__RepeatVirtualScrollImpl.hasVisibleItemsChanged() i:#${i} ttype changed => true`);
                return true;
            }
        }

        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl.hasVisibleItemsChanged() => false`);
        return false;
    }

    /**
     * maintain: index <-> key mapping
     * create new key from keyGen function if not in cache
     * check for duplicate key, and create random key if duplicate found
     * @param forIndex
     * @returns unique key
     */
    private getOrMakeKey4Index(forIndex: number): string {
        let key = this.key4Index_.get(forIndex);
        if (!key) {
            key = this.keyGenFunc_(this.arr_[forIndex], forIndex);
            const usedIndex = this.index4Key_.get(key);
            if (usedIndex !== undefined) {
                // duplicate key
                stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) getOrMakeKey4Index: \
                    Detected duplicate key for indices ${forIndex} and ${usedIndex}. \
                    Generated random key will decrease Repeat performance. Correct the key gen function in your application!`);
                key = `___${forIndex}_+_${key}_+_${Math.random()}`;
            }
            this.key4Index_.set(forIndex, key);
            this.index4Key_.set(key, forIndex);
        }
        return key;
    }

    private purgeKeyCache(): void {
        this.key4Index_.clear();
        this.index4Key_.clear();
    }

    private updateRepeatItem4Key(from: number, to: number): void {
        let newRepeatItem4Key = new Map<string, __RepeatItemFactoryReturn<T>>();
        if (from <= to) {
            for (let i = Math.max(0, from); i <= to && i < this.arr_.length; i++) {
                let key = this.key4Index_.get(i);
                if (key && this.repeatItem4Key_.has(key)) {
                    newRepeatItem4Key.set(key, this.repeatItem4Key_.get(key)!);
                }
            }
        } else {
            for (let i = 0; i <= to && i < this.arr_.length; i++) {
                let key = this.key4Index_.get(i);
                if (key && this.repeatItem4Key_.has(key)) {
                    newRepeatItem4Key.set(key, this.repeatItem4Key_.get(key)!);
                }
            }
            for (let i = Math.max(0, from); i < this.arr_.length; i++) {
                let key = this.key4Index_.get(i);
                if (key && this.repeatItem4Key_.has(key)) {
                    newRepeatItem4Key.set(key, this.repeatItem4Key_.get(key)!);
                }
            }
        }
        this.repeatItem4Key_ = newRepeatItem4Key;
    }
};