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
    private typeGenFunc_: RepeatTypeGenFunc<T>;

    private totalCount_: number;
    private templateOptions_: { [type: string]: RepeatTemplateOptions };

    private mkRepeatItem_: (item: T, index?: number) => __RepeatItemFactoryReturn<T>;
    private onMoveHandler_?: OnMoveHandler;

    // index <-> key maps
    key4Index_ : Map<number, string> = new Map<number, string>();
    index4Key_ : Map<string, number> = new Map<string, number>();

    public render(config: __RepeatConfig<T>, isInitialRender: boolean): void {
        this.arr_ = config.arr;
        this.itemGenFuncs_ = config.itemGenFuncs;
        this.keyGenFunc_ = config.keyGenFunc;
        this.typeGenFunc_ = config.typeGenFunc;

        this.totalCount_ = config.totalCount;
        this.templateOptions_ = config.templateOptions;

        this.mkRepeatItem_ = config.mkRepeatItem;
        this.onMoveHandler_ = config.onMoveHandler;

        if (isInitialRender) {
            this.initialRender(config.owningView_, ObserveV2.getCurrentRecordedId());
        } else {
            this.reRender();
        }
    }

    /**/
    private initialRender(owningView: ViewV2, repeatElmtId: number): void {
        // Map key -> RepeatItem
        // added to closure of following lambdas
        const _repeatItem4Key = new Map<string, __RepeatItemFactoryReturn<T>>();
        const repeatElmtId1 = repeatElmtId;

        const onCreateNode = (forIndex: number): void => {
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl onCreateNode index ${forIndex} - start`);
            if (forIndex < 0) {
                // STATE_MGMT_NOTE check also index < totalCount
                throw new Error(`__RepeatVirtualScrollImpl onCreateNode: for index=${forIndex} out of range error.`)
            }

            // create dependency array item [forIndex] -> Repeat
            // so Repeat updates when the array item changes
            // STATE_MGMT_NOTE observe dependencies, adding the array is insurgent for Array of objects
            ObserveV2.getObserve().addRef4Id(repeatElmtId1, this.arr_, forIndex.toString());

            const repeatItem = this.mkRepeatItem_(this.arr_[forIndex], forIndex);
            let forKey = this.getOrMakeKey4Index(forIndex);
            _repeatItem4Key.set(forKey, repeatItem);

            // execute the itemGen function
            this.initialRenderItem(repeatItem);
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl onCreateNode for index ${forIndex} key "${forKey}" - end `);
        };

        const onUpdateNode = (fromKey: string, forIndex: number): void => {
            if (!fromKey || fromKey == "" || forIndex < 0) {
                // STATE_MGMT_NOTE check also index < totalCount
                throw new Error(`__RepeatVirtualScrollImpl onUpdateNode: fromKey "${fromKey}", forIndex=${forIndex} invalid function input error.`)
            }
            // create dependency array item [forIndex] -> Repeat
            // so Repeat updates when the array item changes
            // STATE_MGMT_NOTE observe dependencies, adding the array is insurgent for Array of objects
            ObserveV2.getObserve().addRef4Id(repeatElmtId1, this.arr_, forIndex.toString());
            const repeatItem = _repeatItem4Key.get(fromKey);
            if (!repeatItem) {
                stateMgmtConsole.error(`__RepeatVirtualScrollImpl onUpdateNode: fromKey "${fromKey}", forIndex=${forIndex}, can not find RepeatItem for key. Unrecoverable error`);
                return;
            }
            const forKey = this.getOrMakeKey4Index(forIndex);
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl onUpdateNode: fromKey "${fromKey}", forIndex=${forIndex} forKey="${forKey}". Updating RepeatItem ...`);
            repeatItem.updateItem(this.arr_[forIndex]);
            repeatItem.updateIndex(forIndex);

            // update Map according to made update:
            // del fromKey entry and add forKey
            _repeatItem4Key.delete(fromKey);
            _repeatItem4Key.set(forKey, repeatItem);

            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl onUpdateNode: fromKey "${fromKey}", forIndex=${forIndex} forKey="${forKey}". Initiating UINodes update synchronously ...`);
            ObserveV2.getObserve().updateDirty2(true);
        };

        const onGetKeys4Range = (from: number, to: number): Array<string> => {
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: onGetKeys4Range from ${from} to ${to} - start`);

            const result = new Array<string>();

            // deep observe dependencies,
            // create dependency array item [i] -> Repeat
            // so Repeat updates when the array item or nested objects changes
            // not enough: ObserveV2.getObserve().addRef4Id(repeatElmtId1, this.arr_, i.toString());
            ViewStackProcessor.StartGetAccessRecordingFor(repeatElmtId1);
            ObserveV2.getObserve().startRecordDependencies(owningView, repeatElmtId1, false);
            for (let i = from; i <= to && i < this.arr_.length; i++) {
                result.push(this.getOrMakeKey4Index(i));
            }
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();

            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: onGetKeys4Range from ${from} to ${to} - returns ${result.toString()}`);
            return result;
        };

        const onGetTypes4Range = (from: number, to: number): Array<string> => {
            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: onGetTypes4Range from ${from} to ${to} - start`);

            const result = new Array<string>();
            
            // deep observe dependencies,
            // create dependency array item [i] -> Repeat
            // so Repeat updates when the array item or nested objects changes
            // not enough: ObserveV2.getObserve().addRef4Id(repeatElmtId1, this.arr_, i.toString());
            ViewStackProcessor.StartGetAccessRecordingFor(repeatElmtId1);
            ObserveV2.getObserve().startRecordDependencies(owningView, repeatElmtId1, false);

            for (let i = from; i <= to && i < this.arr_.length; i++) {
                result.push(this.typeGenFunc_(this.arr_[i], i) ?? '');
            }
            
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();

            stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: onGetTypes4Range from ${from} to ${to} - returns ${result.toString()}`);
            return result;
        };

        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: initialRenderVirtualScroll`);

        RepeatVirtualScrollNative.create(this.totalCount_, Object.entries(this.templateOptions_), {
            onCreateNode,
            onUpdateNode,
            onGetKeys4Range,
            onGetTypes4Range
        });
        RepeatVirtualScrollNative.onMove(this.onMoveHandler_);
        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: initialRenderVirtualScroll`);
    }

    private reRender() {
        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: reRender ...`);
        this.purgeKeyCache();
        RepeatVirtualScrollNative.invalidateKeyCache(this.totalCount_);
        stateMgmtConsole.debug(`__RepeatVirtualScrollImpl: reRender - done`);
    }

    private initialRenderItem(repeatItem: __RepeatItemFactoryReturn<T>): void {
        // execute the itemGen function
        const itemType = this.typeGenFunc_(repeatItem.item, repeatItem.index) ?? '';
        const itemFunc = this.itemGenFuncs_[itemType] ?? this.itemGenFuncs_[''];
        itemFunc(repeatItem);
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
            if (usedIndex) {
                // duplicate key
                stateMgmtConsole.applicationError(`Repeat key gen function: Detected duplicate key ${key} for indices ${forIndex} and ${usedIndex}. \
                            Generated random key will decrease Repeat performance. Correct the Key gen function in your application!`);
                key = `___${forIndex}_+_${key}_+_${Math.random()}`;
            }
            this.key4Index_.set(forIndex, key);
            this.index4Key_.set(key, forIndex);
        }
        return key;
    }

    private purgeKeyCache(): void {
        this.key4Index_.clear()
        this.index4Key_.clear();
    }
};