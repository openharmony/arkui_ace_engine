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

// declare add. functions beyond that framework needs internally
interface __IRepeatItemInternal<T> {
    // set new item value, used during Repeat.each update when
    // - array item has been replaced with new value (LazyForEach onDataChanged)
    // - on child reuse. reuse children to render newItemValue
    updateItem: (newItemVal: T) => void;

    // set new index value, used during  Repeat.each update when
    // - order of item in array has changed  (LazyforEach onDataMoved)
    // - on child reuse. reuse children to render newItemValue. index of 
    //   newItemValue is a new one
    updateIndex: (newIndexValue: number) => void;
}

interface __RepeatItemFactoryReturn<T> extends RepeatItem<T>, __IRepeatItemInternal<T> { }

// implementation for existing state observation system
class __RepeatItem<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {

    // ObservedPropertyPU is the framework class that implements @State, @Provide 
    // and App/LocalStorage properties
    private _observedItem: ObservedPropertyPU<T>;
    private _observedIndex?: ObservedPropertyPU<number>;

    constructor(owningView: PUV2ViewBase, initialItem: T, initialIndex?: number) {
        this._observedItem = new ObservedPropertyPU<T>(initialItem, owningView, "Repeat item");
        if (initialIndex !== undefined) {
            this._observedIndex = new ObservedPropertyPU<number>(initialIndex, owningView, "Repeat index");
        }
    }

    public get item(): T {
        return this._observedItem.get();
    }

    public get index(): number | undefined {
        return this._observedIndex?.get();
    }

    public updateItem(newItemValue: T): void {
        this._observedItem.set(newItemValue);
    }

    public updateIndex(newIndex: number): void {
        if (!this._observedIndex?.hasDependencies()) {
            return;
        }
        if (this._observedIndex?.getUnmonitored() != newIndex) {
            this._observedIndex?.set(newIndex);
        }
    }
}

// framework internal, deep observation 
// implementation for deep observation 

@ObservedV2
class __RepeatItemDeep<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {

    constructor(initialItem: T, initialIndex?: number) {
        this.item = initialItem;
        this.index = initialIndex
    }

    @Trace item: T;
    @Trace index?: number;

    public updateItem(newItemValue: T): void {
        this.item = newItemValue;
    }

    public updateIndex(newIndex: number): void {
        if (this.index !== undefined) {
            this.index = newIndex;
        }
    }
}


// helper, framework internal
interface __RepeatItemInfo<T> {
    key: string;
    // also repeatItem includes index 
    // we need separate index because repeatItem set set and updated later than index needs to be set.
    index: number;
    repeatItem?: __RepeatItemFactoryReturn<T>;
}

// helper
class __RepeatDefaultKeyGen {
    private static weakMap_ = new WeakMap<Object|Symbol, number>();
    private static lastKey_ = 0;

    // Return the same IDs for the same items
    public static func<T>(item: T): string {
        try {
            return __RepeatDefaultKeyGen.funcImpl(item);
        } catch(e) {
            throw new Error (`Repeat(). Default id gen failed. Application Error!`)
        }
    }

    // Return the same IDs for the same pairs <item, index>
    public static funcWithIndex<T>(item: T, index:number) {
        return `${index}__` + __RepeatDefaultKeyGen.func(item);
    }

    private static funcImpl<T>(item: T) {
        // fast keygen logic can be used with objects/symbols only
        if (typeof item != 'object' && typeof item != 'symbol') {
            return JSON.stringify(item);
        }
        // generate a numeric key, store mappings in WeakMap
        if (!this.weakMap_.has(item)) {
            return this.weakMap_.set(item, ++this.lastKey_), `${this.lastKey_}`;
        }
        // use cached key
        return `${this.weakMap_.get(item)}`;
    }
}

// __Repeat implements ForEach with child re-use for both existing state observation
// and deep observation , for non-virtual and virtual code paths (TODO)
class __Repeat<T> implements RepeatAPI<T> {
    private owningView_ : PUV2ViewBase;
    private arr_: Array<T>;
    private itemGenFunc_?: RepeatItemGenFunc<T>;
    private keyGenFunction_?: RepeatKeyGenFunc<T>;
    private isVirtualScroll: boolean = false;
    private key2Item_: Map<string, __RepeatItemInfo<T>> = new Map<string, __RepeatItemInfo<T>>();

    constructor(owningView: PUV2ViewBase, arr: Array<T>) {
        //console.log(`Repeat.constructor`);
        this.owningView_ = owningView;
        this.arr_ = arr ?? [];
        this.keyGenFunction_ = __RepeatDefaultKeyGen.func;
    }

    public updateArr(arr: Array<T>): RepeatAPI<T> {
        this.arr_ = arr ?? [];
        return this;
    }

    public each(itemGenFunc: RepeatItemGenFunc<T>): RepeatAPI<T> {
        //console.log(`Repeat.each`)
        this.itemGenFunc_ = itemGenFunc;
        return this;
    }

    public key(idGenFunc: RepeatKeyGenFunc<T>): RepeatAPI<T> {
        //console.log(`Repeat.key`)
        this.keyGenFunction_ = idGenFunc ?? __RepeatDefaultKeyGen.func;
        return this;
    }

    public virtualScroll(): RepeatAPI<T> {
        //console.log(`Repeat.virtualScroll`)
        this.isVirtualScroll = true;
        return this;
    }

    private genKeys(): Map<string, __RepeatItemInfo<T>> {
        const key2Item = new Map<string, __RepeatItemInfo<T>>();
        this.arr_.forEach((item, index) => {
            const key = this.keyGenFunction_(item, index);
            key2Item.set(key, { key, index })
        });
        if (key2Item.size < this.arr_.length) {
            stateMgmtConsole.warn("Duplicates detected, fallback to index-based keyGen.")
            // Causes all items to be re-rendered
            this.keyGenFunction_ = __RepeatDefaultKeyGen.funcWithIndex;
            return this.genKeys();
            
        }
        //console.log(`value2ids: ${JSON.stringify(Array.from(id2Item), null, 4)} .`)
        return key2Item;
    }

    private mkRepeatItem<T>(item: T, index?: number): __RepeatItemFactoryReturn<T> {
        if (ObserveV2.IsObservedObjectV3(item)) {
            return new __RepeatItemDeep(item as T, index);
        } else {
            return new __RepeatItem(this.owningView_, item, index);
        }
    }

    public render(isInitialRender: boolean): void {
        if (!this.itemGenFunc_) {
            throw new Error(`itemGen function undefined. Usage error`)
        }
        if (this.isVirtualScroll) {
            // TODO haoyu: add render for LazyforEach with child update
            // there might not any rerender , I am not sure.
            throw new Error("TODO virtual code path");
        } else {
            isInitialRender ? this.initialRenderNoneVirtual() : this.rerenderNoneVirtual();
        }
    }

    private initialRenderNoneVirtual(): void {
        //console.log(`Repeat.initialRenderNoneVirtual`)
        this.key2Item_ = this.genKeys();

        RepeatNative.startRender();

        let index = 0;
        this.key2Item_.forEach((itemInfo, key) => {
            itemInfo.repeatItem = this.mkRepeatItem(this.arr_[index], index);
            this.initialRenderItem(key, itemInfo.repeatItem);
            index++;
        })
        let removedChildElmtIds = new Array<number>();
        // Fetch the removedChildElmtIds from C++ to unregister those elmtIds with UINodeRegisterProxy
        RepeatNative.finishRender(removedChildElmtIds);
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        stateMgmtConsole.debug(`RepeatPU: initialRenderNoneVirtual elmtIds need unregister after repeat render: ${JSON.stringify(removedChildElmtIds)}`);
    }

    private rerenderNoneVirtual(): void {
        //console.log(`Repeat.rerenderNoneVirtual`)
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
                stateMgmtConsole.debug(`retained: key ${key} ${oldIndex}->${index}`)
                itemInfo.repeatItem.updateIndex(index);
                // C++ mv from tempChildren[oldIndex] to end of children_
                RepeatNative.moveChild(oldIndex);

            } else if (deletedKeysAndIndex.length) {
                // case #2:
                // new array item, there is an deleted array items whose 
                // UINode children cab re-used
                const oldItemInfo = deletedKeysAndIndex.pop();
                const reuseKey = oldItemInfo!.key;
                const oldKeyIndex = oldItemInfo!.index;
                const oldRepeatItem = oldItemInfo!.repeatItem!;
                itemInfo.repeatItem = oldRepeatItem;
                stateMgmtConsole.debug(`new: key ${key} reuse key ${reuseKey}  ${oldKeyIndex}->${index}`)

                itemInfo.repeatItem.updateItem(item);
                itemInfo.repeatItem.updateIndex(index);

                // update key2item_ Map
                this.key2Item_.set(key, itemInfo);

                // C++ mv from tempChildren[oldIndex] to end of children_
                RepeatNative.moveChild(oldKeyIndex);
            } else {
                // case #3:
                // new array item, there are no deleted array items
                // render new UINode children
                itemInfo.repeatItem = this.mkRepeatItem(item, index);
                this.initialRenderItem(key, itemInfo.repeatItem);
            }

            index++;
        })

        // keep  this.id2item_. by removing all entries for remaining
        // deleted items 
        deletedKeysAndIndex.forEach(delItem => {
            this.key2Item_.delete(delItem!.key);
        });

        // Finish up for.each update
        // C++  tempChildren.clear() , trigger re-layout
        let removedChildElmtIds = new Array<number>();
        // Fetch the removedChildElmtIds from C++ to unregister those elmtIds with UINodeRegisterProxy
        RepeatNative.finishRender(removedChildElmtIds);
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        stateMgmtConsole.debug(`RepeatPU: rerenderNoneVirtual elmtIds need unregister after repeat render: ${JSON.stringify(removedChildElmtIds)}`);
    }

    private initialRenderItem(key: string, repeatItem: __RepeatItemFactoryReturn<T>): void {
        // render new UINode children
        stateMgmtConsole.debug(`new: key ${key} n/a->${repeatItem.index}`)

        // C++: initial render will render to the end of children_
        RepeatNative.createNewChildStart(key);

        // execute the ItemGen function
        this.itemGenFunc_!(repeatItem);

        RepeatNative.createNewChildFinish(key);
    }

}
