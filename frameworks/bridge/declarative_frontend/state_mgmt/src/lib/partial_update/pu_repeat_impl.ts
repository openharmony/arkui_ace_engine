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

class __RepeatImpl<T> {
    private arr_: Array<T>;
    private itemGenFuncs_: { [type: string]: RepeatItemGenFunc<T> };
    private keyGenFunction_?: RepeatKeyGenFunc<T>;
    private typeGenFunc_: RepeatTypeGenFunc<T>;
    //
    private mkRepeatItem_: (item: T, index?: number) =>__RepeatItemFactoryReturn<T>;
    private onMoveHandler_?: OnMoveHandler;

    private key2Item_ = new Map<string, __RepeatItemInfo<T>>();

    /**/
    constructor() {
    }

    /**/
    public render(config: __RepeatConfig<T>, isInitialRender: boolean): void {
        this.arr_ = config.arr;
        this.itemGenFuncs_ = config.itemGenFuncs;
        this.typeGenFunc_ = config.typeGenFunc;
        this.keyGenFunction_ = config.keyGenFunc;
        this.mkRepeatItem_ = config.mkRepeatItem;
        this.onMoveHandler_ = config.onMoveHandler;

        isInitialRender ? this.initialRender() : this.reRender();
    }

    private genKeys(): Map<string, __RepeatItemInfo<T>> {
        const key2Item = new Map<string, __RepeatItemInfo<T>>();
        this.arr_.forEach((item, index) => {
            const key = this.keyGenFunction_(item, index);
            key2Item.set(key, { key, index });
        });
        if (key2Item.size < this.arr_.length) {
            stateMgmtConsole.warn('__RepeatImpl: Duplicates detected, fallback to index-based keyGen.');
            // Causes all items to be re-rendered
            this.keyGenFunction_ = __RepeatDefaultKeyGen.funcWithIndex;
            return this.genKeys();
        }
        return key2Item;
    }

    private initialRender(): void {
        //console.log('__RepeatImpl initialRender() 0')
        this.key2Item_ = this.genKeys();

        RepeatNative.startRender();

        let index = 0;
        this.key2Item_.forEach((itemInfo, key) => {
            itemInfo.repeatItem = this.mkRepeatItem_(this.arr_[index], index);
            this.initialRenderItem(key, itemInfo.repeatItem);
            index++;
        });
        let removedChildElmtIds = new Array<number>();
        // Fetch the removedChildElmtIds from C++ to unregister those elmtIds with UINodeRegisterProxy
        RepeatNative.onMove(this.onMoveHandler_);
        RepeatNative.finishRender(removedChildElmtIds);
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        stateMgmtConsole.debug(`__RepeatImpl: initialRender elmtIds need unregister after repeat render: ${JSON.stringify(removedChildElmtIds)}`);
    }

    private reRender(): void {
        const oldKey2Item: Map<string, __RepeatItemInfo<T>> = this.key2Item_;
        this.key2Item_ = this.genKeys();

        // identify array items that have been deleted
        // these are candidates for re-use
        const deletedKeysAndIndex = new Array<__RepeatItemInfo<T>>();
        for (const [key, feInfo] of oldKey2Item) {
            if (!this.key2Item_.has(key)) {
                deletedKeysAndIndex.push(feInfo);
            }
        }

        // C++: mv children_ aside to tempchildren_
        RepeatNative.startRender();

        let index = 0;
        this.key2Item_.forEach((itemInfo, key) => {
            const item = this.arr_[index];
            let oldItemInfo = oldKey2Item.get(key);

            if (oldItemInfo) {
                // case #1 retained array item
                // moved from oldIndex to index
                const oldIndex = oldItemInfo.index;
                itemInfo.repeatItem = oldItemInfo!.repeatItem!;
                stateMgmtConsole.debug(`__RepeatImpl: retained: key ${key} ${oldIndex}->${index}`);
                itemInfo.repeatItem.updateIndex(index);
                // C++ mv from tempChildren[oldIndex] to end of children_
                RepeatNative.moveChild(oldIndex);

                // TBD moveChild() only when item types are same
            } else if (deletedKeysAndIndex.length) {
                // case #2:
                // new array item, there is an deleted array items whose
                // UINode children cab re-used
                const oldItemInfo = deletedKeysAndIndex.pop();
                const reuseKey = oldItemInfo!.key;
                const oldKeyIndex = oldItemInfo!.index;
                const oldRepeatItem = oldItemInfo!.repeatItem!;
                itemInfo.repeatItem = oldRepeatItem;
                stateMgmtConsole.debug(`__RepeatImpl: new: key ${key} reuse key ${reuseKey}  ${oldKeyIndex}->${index}`);

                itemInfo.repeatItem.updateItem(item);
                itemInfo.repeatItem.updateIndex(index);

                // update key2item_ Map
                this.key2Item_.set(key, itemInfo);

                // TBD moveChild() only when item types are same
                // C++ mv from tempChildren[oldIndex] to end of children_
                RepeatNative.moveChild(oldKeyIndex);
            } else {
                // case #3:
                // new array item, there are no deleted array items
                // render new UINode children
                itemInfo.repeatItem = this.mkRepeatItem_(item, index);
                this.initialRenderItem(key, itemInfo.repeatItem);
            }

            index++;
        });

        // keep  this.id2item_. by removing all entries for remaining
        // deleted items
        deletedKeysAndIndex.forEach(delItem => {
            this.key2Item_.delete(delItem!.key);
        });

        // Finish up for.each update
        // C++  tempChildren.clear() , trigger re-layout
        let removedChildElmtIds = new Array<number>();
        // Fetch the removedChildElmtIds from C++ to unregister those elmtIds with UINodeRegisterProxy
        RepeatNative.onMove(this.onMoveHandler_);
        RepeatNative.finishRender(removedChildElmtIds);
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        stateMgmtConsole.debug(`__RepeatImpl: reRender elmtIds need unregister after repeat render: ${JSON.stringify(removedChildElmtIds)}`);
    }

    private initialRenderItem(key: string, repeatItem: __RepeatItemFactoryReturn<T>): void {
        //console.log('__RepeatImpl initialRenderItem()')
        // render new UINode children
        stateMgmtConsole.debug(`__RepeatImpl: new: key ${key} n/a->${repeatItem.index}`);

        // C++: initial render will render to the end of children_
        RepeatNative.createNewChildStart(key);

        // execute the itemGen function
        const itemType = this.typeGenFunc_(repeatItem.item, repeatItem.index) ?? '';
        const itemFunc = this.itemGenFuncs_[itemType] ?? this.itemGenFuncs_[''];
        itemFunc(repeatItem);

        RepeatNative.createNewChildFinish(key);
    }

};
