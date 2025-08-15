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

import { int32, hashCodeFromString, KoalaCallsiteKey } from '@koalaui/common';
import { KPointer } from '@koalaui/interop';
import { __context, __id, RepeatByArray, remember, NodeAttach, contextNode, scheduleCallback } from '@koalaui/runtime';
import { RepeatItem, RepeatAttribute, RepeatArray, RepeatItemBuilder, TemplateTypedFunc, VirtualScrollOptions, TemplateOptions } from '../component/repeat';
import { IDataSource, DataChangeListener } from '../component/lazyForEach';
import { LazyForEachImpl } from './LazyForEachImpl';
import { InternalListener } from '../DataChangeListener';
import { PeerNode } from '../PeerNode';
import { ArkUIAniModule } from '../ani/arkts/ArkUIAniModule';

/** @memo:intrinsic */
export function RepeatImpl<T>(
    /** @memo */
    style: ((attributes: RepeatAttribute<T>) => void) | undefined,
    arr: RepeatArray<T>
): void {
    const repeat = remember(() => {
        return new RepeatAttributeImpl<T>();
    });
    style?.(repeat);
    if (!repeat.itemGenFuncs_.get(RepeatEachFuncType)) {
        throw new Error('Repeat item builder function unspecified. Usage error!');
    }
    if (repeat.disableVirtualScroll_) {
        nonVirtualRender<T>(arr, repeat.itemGenFuncs_.get(RepeatEachFuncType)!, repeat.keyGenFunc_);
    } else {
        const repeatId = __id();
        const node = contextNode<PeerNode>();
        scheduleCallback(() => // postpone until node is attached
            repeat.templateCacheSize_.forEach((size: number, template: string) => node.setReusePoolSize(size, template + repeatId))
        );
        virtualRender<T>(arr, repeat, repeatId);
    }
}

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
    private listener_?: InternalListener;
    private total_: number;
    private onLazyLoading_?: (index: number) => void;

    constructor(arr: RepeatArray<T>) {
        this.arr_ = arr;
    }

    totalCount(): number {
        return this.total_;
    }

    updateData(newArr: RepeatArray<T>, totalCount: number) {
        if (this.total_ != totalCount) {
            this.listener_?.update(Math.min(this.total_, totalCount), Number.POSITIVE_INFINITY, totalCount - this.total_);
        }
        this.total_ = totalCount;
        // Compare array references first
        if (this.arr_ === newArr) {
            return;
        }
        // Shallow compare: check length and each element by reference
        if (this.arr_.length !== newArr.length) {
            this.listener_?.update(0, Number.POSITIVE_INFINITY, this.arr_.length - newArr.length);
            this.arr_ = newArr;
            return;
        }
        for (let i = 0; i < newArr.length; i++) {
            if (this.arr_[i] !== newArr[i]) {
                this.listener_?.update(i, Number.POSITIVE_INFINITY, 0);
                this.arr_ = newArr;
                return;
            }
        }
        // No changes detected
    }

    getData(index: number): T {
        if (index < 0 || index >= this.total_) {
            throw new Error('index out of range. Application error!');
        }
        if (index >= this.arr_.length && index < this.total_) {
            try {
                this.onLazyLoading_?.(index);
            } catch (error) {
                console.error(`onLazyLoading function execute error: ${error}`);
            }
        }
        return this.arr_[index];
    }

    setOnLazyLoading(onLazyLoading?: (index: number) => void): void {
        this.onLazyLoading_ = onLazyLoading;
    }

    registerDataChangeListener(listener: DataChangeListener): void {
        if (listener instanceof InternalListener)
            this.listener_ = listener as InternalListener;
        else
            throw Error("Invalid listener registration. Repeat's data source object shouldn't be exposed to other modules");
    }

    unregisterDataChangeListener(listener: DataChangeListener): void {
        if (listener !== this.listener_) throw Error("Invalid deregistration");
        this.listener_ = undefined;
    }
}

// should be empty string, don't change it
const RepeatEachFuncType: string = '';

export class RepeatAttributeImpl<T> implements RepeatAttribute<T> {
    itemGenFuncs_: Map<string, RepeatItemBuilder<T>> = new Map<string, RepeatItemBuilder<T>>();
    keyGenFunc_?: (item: T, index: number) => string;
    templateCacheSize_: Map<string, number> = new Map<string, number>(); // size of spare nodes for each template
    ttypeGenFunc_: TemplateTypedFunc<T> = () => RepeatEachFuncType;

    userDefinedTotal_?: number; // if totalCount is specified
    onLazyLoading_?: (index: number) => void;

    reusable_: boolean = false;
    disableVirtualScroll_: boolean = false;

    each(itemGenerator: RepeatItemBuilder<T>): RepeatAttributeImpl<T> {
        if (itemGenerator === undefined || typeof itemGenerator !== 'function') {
            throw new Error('item generator function missing. Application error!');
        }
        this.itemGenFuncs_.set(RepeatEachFuncType, itemGenerator);
        this.templateCacheSize_.set(RepeatEachFuncType, Number.POSITIVE_INFINITY);
        return this;
    }

    key(keyGenerator: (item: T, index: number) => string): RepeatAttributeImpl<T> {
        this.keyGenFunc_ = keyGenerator;
        return this;
    }

    virtualScroll(options?: VirtualScrollOptions): RepeatAttributeImpl<T> {
        this.userDefinedTotal_ = options?.onTotalCount?.() ?? options?.totalCount;
        this.reusable_ = options?.reusable !== false;
        this.onLazyLoading_ = options?.onLazyLoading;

        this.disableVirtualScroll_ = options?.disableVirtualScroll ?? false;
        return this;
    }

    template(
        type: string, itemBuilder: RepeatItemBuilder<T>, templateOptions?: TemplateOptions): RepeatAttributeImpl<T> {
        if (itemBuilder === undefined || typeof itemBuilder !== 'function') {
            throw new Error('template generator function missing. Application error!');
        }
        this.itemGenFuncs_.set(type, itemBuilder);
        this.templateCacheSize_.set(type, templateOptions?.cachedCount ?? Number.POSITIVE_INFINITY);
        return this;
    }

    templateId(typedFunc: TemplateTypedFunc<T>): RepeatAttributeImpl<T> {
        if (typedFunc === undefined || typeof typedFunc !== 'function') {
            throw new Error('templateId generator function missing. Application error!');
        }
        this.ttypeGenFunc_ = typedFunc;
        return this;
    }
}

export class SyntaxNodePeer extends PeerNode {
    public static create(): SyntaxNodePeer {
        const peerId = PeerNode.nextId();
        const _peerPtr = ArkUIAniModule._SyntaxNode_Construct(peerId);
        if (!_peerPtr) {
            throw new Error(`Failed to create SyntaxNodePeer with id: ${peerId}`);
        }
        return new SyntaxNodePeer(_peerPtr, peerId, 'SyntaxNode');
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
    }
}

/** @memo:intrinsic */
function virtualRender<T>(
    arr: RepeatArray<T>,
    attributes: RepeatAttributeImpl<T>,
    repeatId: KoalaCallsiteKey,
): void {
    let dataSource = remember(() => new RepeatDataSource<T>(arr));
    const total = attributes.userDefinedTotal_ ?? arr.length.toDouble();
    dataSource.updateData(arr, (Number.isInteger(total) && total >= 0) ? total : arr.length);
    if (!attributes.onLazyLoading_ && dataSource.totalCount() > arr.length) {
        console.error(`(${repeatId}) totalCount must not exceed the array length without onLazyLoading callback.`);
    }
    dataSource.setOnLazyLoading(attributes.onLazyLoading_);

    /** @memo */
    const itemGen = (item: T, index: number): void => {
        const ri = new RepeatItemImpl<T>(item, index);
        let _type: string = attributes.ttypeGenFunc_(item, index);
        if (!attributes.itemGenFuncs_.has(_type)) {
            _type = RepeatEachFuncType;
        }
        /** @memo */
        const itemBuilder = attributes.itemGenFuncs_.get(_type)!;
        /**
         * wrap in reusable node.
         * To optimize performance, insert reuseKey through compiler plugin to the content of itemBuilder.
         */
        if (attributes.reusable_) {
            NodeAttach(() => SyntaxNodePeer.create(), (node: SyntaxNodePeer) => {
                itemBuilder(ri);
            }, _type + repeatId); // using type as reuseKey
        } else {
            itemBuilder(ri);
        }
    };
    LazyForEachImpl<T>(dataSource, itemGen, attributes.keyGenFunc_);
}

/** @memo */
function nonVirtualRender<T>(arr: RepeatArray<T>,
    /** @memo */
    itemGenerator: RepeatItemBuilder<T>,
    keyGenerator?: (element: T, index: number) => string
): void {
    if (keyGenerator && typeof keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    const keyGen = (ele: T, i: int32): KoalaCallsiteKey =>
        keyGenerator ? hashCodeFromString(keyGenerator!(ele, (i as number))) : i;
    RepeatByArray<T>(arr, keyGen, (ele: T, i: int32) => {
        const ri = new RepeatItemImpl<T>(ele, (i as number));
        itemGenerator(ri);
    });
}
