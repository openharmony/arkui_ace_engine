/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


// HANDWRITTEN, DO NOT REGENERATE

import { int32, uint32, hashCodeFromString, KoalaCallsiteKey } from '@koalaui/common';
import { __context, __id, DataNode, RepeatByArray, remember, NodeAttach } from '@koalaui/runtime';
import { RepeatItem, UIRepeatAttribute, RepeatArray, RepeatItemBuilder, TemplateTypedFunc, VirtualScrollOptions, TemplateOptions } from '../component/repeat';
import { IDataSource, DataChangeListener } from '../component/lazyForEach';
import { LazyForEachImpl } from './LazyForEachImpl';
import { RepeatType } from '../PeerNode';
import { ArkColumnPeer } from '../component/column';

class RepeatItemImpl<T> implements RepeatItem<T> {
    __item: T;
    __index: number;
    
    constructor(initialItem: T, initialIndex: number) {
        this.__item = initialItem;
        this.__index = initialIndex;
    }

    get item(): T {
        return this.__item;
    }

    get index(): number {
        return this.__index;
    }

    public updateItem(newItem: T): void {
        this.__item = newItem;
    }

    public updateIndex(newIndex: number): void {
        this.__index = newIndex;
    }
}

class RepeatDataSource<T> implements IDataSource<T> {
    private arr_: RepeatArray<T>;
    private listeners = new Set<DataChangeListener>()

    constructor(arr: RepeatArray<T>) {
        this.arr_ = arr;
    }

    totalCount(): number {
        return this.arr_.length;
    }

    updateData(newArr: RepeatArray<T>) {
        // Compare array references first
        if (this.arr_ === newArr) {
            return;
        }
        // Shallow compare: check length and each element by reference
        if (this.arr_.length !== newArr.length) {
            this.arr_ = newArr;
            this.listeners.forEach(listener => listener.onDataReloaded());
            return;
        }
        for (let i = 0; i < newArr.length; i++) {
            if (this.arr_[i] !== newArr[i]) {
                this.arr_ = newArr;
                this.listeners.forEach(listener => listener.onDataReloaded());
                return;
            }
        }
        // No changes detected
    }

    getData(index: number): T {
        if (index < 0 || index >= this.arr_.length) {
            throw new Error('index out of range. Application error!');
        }
        return this.arr_[index];
    }

    registerDataChangeListener(listener: DataChangeListener): void {
        this.listeners.add(listener)
    }

    unregisterDataChangeListener(listener: DataChangeListener): void {
        this.listeners.delete(listener)
    }
}

export class RepeatDataNode<T> extends DataNode<T> {
    constructor(kind: uint32 = 1) {
        super(kind);
    }
}

// should be empty string, don't change it
const RepeatEachFuncType: string = '';

export class UIRepeatAttributeImpl<T> implements UIRepeatAttribute<T> {
    arr_: RepeatArray<T>;
    itemGenFuncs_: Map<string, RepeatItemBuilder<T>> = new Map<string, RepeatItemBuilder<T>>();
    keyGenFunc_?: (item: T, index: number) => string;
    totalCount_?: number | (() => number);
    totalCountSpecified_?: boolean;
    templateOptions_: Map<string, number> = new Map<string, number>();
    ttypeGenFunc_?: TemplateTypedFunc<T>;
    reusable_?: boolean;
    isVirtualScroll_: boolean = false;

    constructor(arr: RepeatArray<T>) {
        this.arr_ = arr;
    }

    /** @memo */
    each(itemGenerator: RepeatItemBuilder<T>): UIRepeatAttributeImpl<T> {
        if (itemGenerator === undefined || typeof itemGenerator !== 'function') {
            throw new Error('item generator function missing. Application error!');
        }
        this.itemGenFuncs_.set(RepeatEachFuncType, itemGenerator);
        this.templateOptions_.set(RepeatEachFuncType, this.normTemplateOptions({}));
        return this;
    }

    /** @memo */
    key(keyGenerator: (item: T, index: number) => string): UIRepeatAttributeImpl<T> {
        this.keyGenFunc_ = keyGenerator;
        return this;
    }

    /** @memo */
    virtualScroll(options?: VirtualScrollOptions): UIRepeatAttributeImpl<T> {
        // use array length as default value
        this.totalCount_ = this.arr_.length;
        this.totalCountSpecified_ = false;

        if (options?.totalCount && Number.isInteger(options?.totalCount!) && (options?.totalCount as number) >= 0) {
            this.totalCount_ = options?.totalCount;
            this.totalCountSpecified_ = true;
        }
        if (typeof options?.reusable === 'boolean') {
            this.reusable_ = options!.reusable;
        } else if (options?.reusable === null) {
            this.reusable_ = true;
            throw new Error('Repeat.reusable type should be boolean. Use default value: true.');
        } else {
            this.reusable_ = true;
        }

        this.isVirtualScroll_ = true;
        return this;
    }

    /** @memo */
    template(
        type: string, itemBuilder: RepeatItemBuilder<T>, templateOptions?: TemplateOptions): UIRepeatAttributeImpl<T> {
        if (itemBuilder === undefined || typeof itemBuilder !== 'function') {
            throw new Error('template generator function missing. Application error!');
        }
        this.itemGenFuncs_.set(type, itemBuilder);
        this.templateOptions_.set(type, this.normTemplateOptions(templateOptions));
        return this;
    }

    /** @memo */
    templateId(typedFunc: TemplateTypedFunc<T>): UIRepeatAttributeImpl<T> {
        if (typedFunc === undefined || typeof typedFunc !== 'function') {
            throw new Error('templateId generator function missing. Application error!');
        }
        this.ttypeGenFunc_ = typedFunc;
        return this;
    }

    /** @memo */
    render(arr: RepeatArray<T>): void {
        if (!this.itemGenFuncs_.get(RepeatEachFuncType)) {
            throw new Error('Repeat item builder function unspecified. Usage error!');
        }
        this.isVirtualScroll_
            ? virtualRender<T>(arr, this.itemGenFuncs_, this.keyGenFunc_, this.ttypeGenFunc_, this.reusable_)
            : nonVirtualRender<T>(arr, this.itemGenFuncs_.get(RepeatEachFuncType)!, this.keyGenFunc_);
    }

    // normalize the template options
    private normTemplateOptions(options?: TemplateOptions): number {
        if (options && options.cachedCount && Number.isInteger(options.cachedCount!)) {
            return options.cachedCount!;
        }
        return NaN;
    }
}

/** @memo */
function virtualRender<T>(arr: RepeatArray<T>,
    itemGenFuncs: Map<string, RepeatItemBuilder<T>>,
    keyGenerator?: (element: T, index: number) => string,
    typedFunc?: TemplateTypedFunc<T>,
    reusable?: boolean
): void {
    let dataSource = remember(()=> new RepeatDataSource<T>(arr))
    dataSource.updateData(arr)
    /** @memo */
    const itemGen = (item: T, index: number): void => {
        const ri = new RepeatItemImpl<T>(item, index as number);
        let _type: string = typedFunc ? typedFunc!(item, index as number) : RepeatEachFuncType;
        if (!itemGenFuncs.has(_type)) {
            _type = RepeatEachFuncType;
        }
        /** @memo */
        const itemBuilder = itemGenFuncs.get(_type)!;
        /**
         * wrap in reusable node.
         * To optimize performance, insert reuseKey through compiler plugin to the content of itemBuilder.
         */
        if (reusable) {
            NodeAttach(() => ArkColumnPeer.create(undefined), (node: ArkColumnPeer) => {
                itemBuilder(ri);
            }, _type) // using type as reuseKey
        } else {
            itemBuilder(ri);
        }
    }
    LazyForEachImpl<T>(dataSource, itemGen, keyGenerator);
}

/** @memo */
function nonVirtualRender<T>(arr: RepeatArray<T>,
    /** @memo */
    itemGenerator: RepeatItemBuilder<T>,
    keyGenerator?: (element: T, index: number) => string): void {
    if (keyGenerator && typeof keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    const keyGen = (ele: T, i: int32): KoalaCallsiteKey =>
        keyGenerator ? hashCodeFromString(keyGenerator!(ele, (i as number))) : i;
    RepeatByArray<T>(arr, keyGen, (ele: T, i: int32) => {
        const ri = new RepeatItemImpl<T>(ele, (i as number));
        /** @memo */
        itemGenerator(ri);
    });
}

/** @memo */
export function RepeatImpl<T>(
    /** @memo */
    style: ((attributes: UIRepeatAttribute<T>) => void) | undefined,
    arr: RepeatArray<T>
): void {
    const receiver = remember(() => {
        return new UIRepeatAttributeImpl<T>(arr);
    });
    NodeAttach<RepeatDataNode<T>>((): RepeatDataNode<T> => {
        return new RepeatDataNode<T>(RepeatType);
    }, (_: RepeatDataNode<T>) => {
        style?.(receiver);
    });
    receiver.render(arr);
}