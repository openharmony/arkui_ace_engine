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
class __RepeatItemPU<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {

    // ObservedPropertyPU is the framework class that implements @State, @Provide
    // and App/LocalStorage properties
    private _observedItem: ObservedPropertyPU<T>;
    private _observedIndex?: ObservedPropertyPU<number>;

    constructor(owningView: ViewPU, initialItem: T, initialIndex?: number) {
        this._observedItem = new ObservedPropertyPU<T>(initialItem, owningView, 'Repeat item');
        if (initialIndex !== undefined) {
            this._observedIndex = new ObservedPropertyPU<number>(initialIndex, owningView, 'Repeat index');
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
        if (this._observedIndex?.getUnmonitored() !== newIndex) {
            this._observedIndex?.set(newIndex);
        }
    }
}

// Framework internal, deep observation
// Using @ObservedV2_Internal instead of @ObservedV2 to avoid forcing V2 usage.
@ObservedV2_Internal
class __RepeatItemV2<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {

    constructor(initialItem: T, initialIndex?: number) {
        this.item = initialItem;
        this.index = initialIndex;
    }
    // Using @Trace_Internal instead of @Trace to avoid forcing V2 usage.
    @Trace_Internal item: T;
    @Trace_Internal index?: number;

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
    private static weakMap_ = new WeakMap<Object | Symbol, number>();
    private static lastKey_ = 0;

    // Return the same IDs for the same items
    public static func<T>(item: T): string {
        try {
            return __RepeatDefaultKeyGen.funcImpl(item);
        } catch (e) {
            throw new Error(`Repeat(). Default id gen failed. Application Error!`);
        }
    }

    // Return the same IDs for the same pairs <item, index>
    public static funcWithIndex<T>(item: T, index: number) {
        return `${index}__` + __RepeatDefaultKeyGen.func(item);
    }

    private static funcImpl<T>(item: T) {
        // fast keygen logic can be used with objects/symbols only
        if (typeof item != 'object' && typeof item !== 'symbol') {
            return JSON.stringify(item);
        }
        // generate a numeric key, store mappings in WeakMap
        if (!this.weakMap_.has(item)) {
            return this.weakMap_.set(item, ++this.lastKey_), `${this.lastKey_}`;
        }
        // use cached key
        return `${this.weakMap_.get(item)}`;
    }
};

// TBD comments
interface __RepeatAPIConfig<T> {
    arr?: Array<T>;
    itemGenFuncs?: { [type: string]: RepeatItemGenFunc<T> };
    keyGenFunc?: RepeatKeyGenFunc<T>;
    typeGenFunc?: RepeatTypeGenFunc<T>;
    //
    totalCount?: number;
    templateOptions?: { [type: string]: RepeatTemplateOptions };
    //
    mkRepeatItem?: (item: T, index?: number) => __RepeatItemFactoryReturn<T>;
    onMoveHandler?: OnMoveHandler;
};

// __Repeat implements ForEach with child re-use for both existing state observation
// and deep observation , for non-virtual and virtual code paths (TODO)
class __RepeatV2<T> implements RepeatAPI<T> {
    private config: __RepeatAPIConfig<T> = {};
    private impl: __RepeatImpl<T> | __RepeatVirtualScrollImpl<T>;
    private isVirtualScroll = false;

    constructor(arr: Array<T>) {
        //console.log('__RepeatV2 ctor')
        this.config.arr = arr ?? [];
        this.config.itemGenFuncs = {};
        this.config.keyGenFunc = __RepeatDefaultKeyGen.func;
        this.config.typeGenFunc= (() => '');
        this.config.totalCount = this.config.arr.length;
        this.config.templateOptions = {};
        this.config.mkRepeatItem = this.mkRepeatItem;
    }

    public each(itemGenFunc: RepeatItemGenFunc<T>): RepeatAPI<T> {
        //console.log('__RepeatV2.each()')
        this.config.itemGenFuncs[''] = itemGenFunc;
        this.config.templateOptions[''] = { ...this.defaultTemplateOptions() };
        return this;
    }

    public key(keyGenFunc: RepeatKeyGenFunc<T>): RepeatAPI<T> {
        //console.log('__RepeatV2.key()')
        this.config.keyGenFunc = keyGenFunc ?? __RepeatDefaultKeyGen.func;
        return this;
    }

    public virtualScroll(options? : { totalCount?: number }): RepeatAPI<T> {
        //console.log('__RepeatV2.virtualScroll()')
        this.config.totalCount = options?.totalCount ?? this.config.arr.length;
        this.isVirtualScroll = true;
        return this;
    }

    // function to decide which template to use, each template has an id
    public templateId(typeFunc: RepeatTypeGenFunc<T>): RepeatAPI<T> {
        //console.log('__RepeatV2.templateId()')
        this.config.typeGenFunc = typeFunc;
        return this;
    }

    // template: id + builder function to render specific type of data item 
    public template(type: string, itemGenFunc: RepeatItemGenFunc<T>,
        options?: RepeatTemplateOptions): RepeatAPI<T>
    {
        //console.log('__RepeatV2.template()')
        this.config.itemGenFuncs[type] = itemGenFunc;
        this.config.templateOptions[type] = { ...this.defaultTemplateOptions(), ...options };
        return this;
    }

    public updateArr(arr: Array<T>): RepeatAPI<T> {
        //console.log('__RepeatV2.updateArr()')
        this.config.arr = arr ?? [];
        return this;
    }

    public render(isInitialRender: boolean): void {
        //console.log('__RepeatV2.render()')
        if (!this.config.itemGenFuncs?.['']) {
            throw new Error(`__RepeatV2 item builder function unspecified. Usage error`);
        }
        if (!this.isVirtualScroll) {
          // Repeat
          this.impl ??= new __RepeatImpl<T>();
          this.impl.render(this.config, isInitialRender);
        } else {
          // RepeatVirtualScroll
          this.impl ??= new __RepeatVirtualScrollImpl<T>();
          this.impl.render(this.config, isInitialRender);
        }
    }

    public onMove(handler: OnMoveHandler): RepeatAPI<T> {
        this.config.onMoveHandler = handler;
        return this;
    }

    private defaultTemplateOptions (): RepeatTemplateOptions {
        return { cachedCount: 1 };
    }

    protected mkRepeatItem<T>(item: T, index?: number): __RepeatItemFactoryReturn<T> {
        return new __RepeatItemV2(item as T, index);
    }
}; // __RepeatV2<T>

// __Repeat implements ForEach with child re-use for both existing state observation
// and deep observation , for non-virtual and virtual code paths (TODO)

class __RepeatPU<T> extends __RepeatV2<T> implements RepeatAPI<T> {
    private owningView_: ViewPU;

    constructor(owningView: ViewPU, arr: Array<T>) {
        super(arr);
        this.owningView_ = owningView;
    }

    protected mkRepeatItem<T>(item: T, index?: number): __RepeatItemFactoryReturn<T> {
        return new __RepeatItemPU(this.owningView_, item, index);
    }
}