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

import { int32, hashCodeFromString, KoalaCallsiteKey } from '@koalaui/common'
import { KPointer } from '@koalaui/interop'
import { __context, __id, RepeatByArray, remember, NodeAttach, contextNode, scheduleCallback } from '@koalaui/runtime'
import { RepeatItem, RepeatAttribute, RepeatArray, RepeatItemBuilder, TemplateTypedFunc, VirtualScrollOptions, TemplateOptions } from '../component/repeat'
import { IDataSource, DataChangeListener } from '../component/lazyForEach'
import { OnMoveHandler, ItemDragEventHandler, ForEachOps } from '#generated'
import { LazyForEachImplForOptions, NodeHolder } from './LazyForEachImpl'
import { InternalListener } from './DataChangeListener'
import { PeerNode } from '../PeerNode'
import { ArkUIAniModule } from '../ani/arkts/ArkUIAniModule'

/** @memo:intrinsic */
export function RepeatImplForOptions<T>(
    /** @memo */
    style: ((attributes: RepeatAttribute<T>) => void) | undefined,
    arr: RepeatArray<T>
): void {
    const repeat = remember(() => {
        return new RepeatAttributeImpl<T>();
    });
    style?.(repeat);
    if (!repeat.itemGenFuncs_.get(REPEAT_EACH_FUNC_TYPE)) {
        throw new Error('Repeat item builder function unspecified. Usage error!');
    }
    if (repeat.disableVirtualScroll_) {
        nonVirtualRender<T>(arr, repeat.itemGenFuncs_.get(REPEAT_EACH_FUNC_TYPE)!, repeat.keyGenFunc_,
            repeat.onMove_, repeat.itemDragEvent_);
    } else {
        const repeatId = __id();
        const node = contextNode<PeerNode>();
        scheduleCallback(() => // postpone until node is attached
            repeat.templateCacheSize_.forEach((size: int32, template: string) =>
                node.setReusePoolSize(size, template + repeatId))
        );
        virtualRender<T>(arr, repeat, repeatId);
    }
}

class RepeatItemImpl<T> implements RepeatItem<T> {
    item_: T;
    index_: int32;

    constructor(initialItem: T, initialIndex: int32) {
        this.item_ = initialItem;
        this.index_ = initialIndex;
    }

    get item(): T {
        return this.item_;
    }

    get index(): int32 {
        return this.index_;
    }

    public updateItem(newItem: T): void {
        this.item_ = newItem;
    }

    public updateIndex(newIndex: int32): void {
        this.index_ = newIndex;
    }
}

class RepeatDataSource<T> implements IDataSource<T> {
    private arr_: RepeatArray<T>;
    private listener_?: InternalListener;
    private total_: int32;
    private onLazyLoading_?: (index: int32) => void;

    constructor(arr: RepeatArray<T>) {
        this.arr_ = arr;
    }

    totalCount(): int32 {
        return this.total_;
    }

    updateData(newArr: RepeatArray<T>, totalCount: int32) {
        if (this.total_ != totalCount) {
            this.listener_?.update(
                Math.min(this.total_, totalCount).toInt(), Number.POSITIVE_INFINITY.toInt(), totalCount - this.total_);
        }
        this.total_ = totalCount;
        // Compare array references first
        if (this.arr_ === newArr) {
            return;
        }
        // Shallow compare: check length and each element by reference
        if (this.arr_.length !== newArr.length) {
            this.listener_?.update(0, Number.POSITIVE_INFINITY.toInt(), this.arr_.length - newArr.length);
            this.arr_ = newArr;
            return;
        }
        for (let i = 0; i < newArr.length; i++) {
            if (this.arr_[i] !== newArr[i]) {
                this.listener_?.update(i, Number.POSITIVE_INFINITY.toInt(), 0);
                this.arr_ = newArr;
                return;
            }
        }
        // No changes detected
    }

    getData(index: int32): T {
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

    setOnLazyLoading(onLazyLoading?: (index: int32) => void): void {
        this.onLazyLoading_ = onLazyLoading;
    }

    registerDataChangeListener(listener: DataChangeListener): void {
        if (listener instanceof InternalListener) {
            this.listener_ = listener as InternalListener;
        } else {
            throw new Error(
                'Invalid listener registration. Repeat\'s data source object shouldn\'t be exposed to other modules');
        }
    }

    unregisterDataChangeListener(listener: DataChangeListener): void {
        if (listener !== this.listener_) {
            throw new Error('Invalid deregistration');
        }
        this.listener_ = undefined;
    }
}

// should be empty string, don't change it
const REPEAT_EACH_FUNC_TYPE: string = '';

export class RepeatAttributeImpl<T> implements RepeatAttribute<T> {
    arr: RepeatArray<T> = [];
    itemGenFuncs_: Map<string, RepeatItemBuilder<T>> = new Map<string, RepeatItemBuilder<T>>();
    keyGenFunc_?: (item: T, index: int32) => string;
    templateCacheSize_: Map<string, int32> = new Map<string, int32>(); // size of spare nodes for each template
    ttypeGenFunc_: TemplateTypedFunc<T> = () => REPEAT_EACH_FUNC_TYPE;

    userDefinedTotal_?: int32; // if totalCount is specified
    onLazyLoading_?: (index: int32) => void;
    onMove_?: OnMoveHandler;
    itemDragEvent_?: ItemDragEventHandler;

    reusable_: boolean = true;
    disableVirtualScroll_: boolean = false;

    setRepeatOptions(arr: RepeatArray<T>): this {
        return this;
    }

    each(itemGenerator: RepeatItemBuilder<T>): RepeatAttributeImpl<T> {
        if (itemGenerator === undefined || typeof itemGenerator !== 'function') {
            throw new Error('item generator function missing. Application error!');
        }
        this.itemGenFuncs_.set(REPEAT_EACH_FUNC_TYPE, itemGenerator);
        this.templateCacheSize_.set(REPEAT_EACH_FUNC_TYPE, Number.POSITIVE_INFINITY.toInt());
        return this;
    }

    key(keyGenerator: (item: T, index: int32) => string): RepeatAttributeImpl<T> {
        this.keyGenFunc_ = keyGenerator;
        return this;
    }

    virtualScroll(options?: VirtualScrollOptions): RepeatAttributeImpl<T> {
        this.userDefinedTotal_ = options?.onTotalCount?.() ?? options?.totalCount;
        this.reusable_ = options?.reusable ?? true;
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
        this.templateCacheSize_.set(type, templateOptions?.cachedCount ?? Number.POSITIVE_INFINITY.toInt());
        return this;
    }

    templateId(typedFunc: TemplateTypedFunc<T>): RepeatAttributeImpl<T> {
        if (typedFunc === undefined || typeof typedFunc !== 'function') {
            throw new Error('templateId generator function missing. Application error!');
        }
        this.ttypeGenFunc_ = typedFunc;
        return this;
    }

    onMove(handler: OnMoveHandler | undefined): this {
        this.onMove_ = handler;
        return this;
    }

    onMove(handler: OnMoveHandler | undefined,
        eventHandler: ItemDragEventHandler | undefined): this {
        this.onMove_ = handler;
        this.itemDragEvent_ = eventHandler;
        return this;
    }

    applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
    }
}

export class SyntaxItemPeer extends PeerNode {
    public static create(): SyntaxItemPeer {
        const peerId = PeerNode.nextId();
        const _peerPtr = ArkUIAniModule._SyntaxItem_Construct(peerId);
        if (!_peerPtr) {
            throw new Error(`Failed to create SyntaxItemPeer with id: ${peerId}`);
        }
        return new SyntaxItemPeer(_peerPtr, peerId, 'SyntaxItem');
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
    }
}

export class ForEachNodePeer extends PeerNode {
    public static create(isRepeat: boolean = false): ForEachNodePeer {
        const peerId = PeerNode.nextId();
        const _peerPtr = ArkUIAniModule._ForEachNode_Construct(peerId, isRepeat);
        if (!_peerPtr) {
            throw new Error(`Failed to create ForEachNodePeer with id: ${peerId}`);
        }
        return new ForEachNodePeer(_peerPtr, peerId, isRepeat ? 'Repeat' : 'ForEach');
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
    const total = attributes.userDefinedTotal_ ?? arr.length;
    dataSource.updateData(arr, total >= 0 ? total : arr.length);
    if (!attributes.onLazyLoading_ && dataSource.totalCount() > arr.length) {
        console.error(`(${repeatId}) totalCount must not exceed the array length without onLazyLoading callback.`);
    }
    dataSource.setOnLazyLoading(attributes.onLazyLoading_);

    /** @memo */
    const itemGen = (item: T, index: int32): void => {
        const ri = new RepeatItemImpl<T>(item, index);
        let _type: string = attributes.ttypeGenFunc_(item, index);
        if (!attributes.itemGenFuncs_.has(_type)) {
            _type = REPEAT_EACH_FUNC_TYPE;
        }
        /** @memo */
        const itemBuilder = attributes.itemGenFuncs_.get(_type)!;
        /**
         * wrap in reusable node.
         * To optimize performance, insert reuseKey through compiler plugin to the content of itemBuilder.
         */
        if (attributes.reusable_) {
            NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
                itemBuilder(ri);
            }, _type + repeatId); // using type as reuseKey
        } else {
            itemBuilder(ri);
        }
    };
    LazyForEachImplForOptions<T>(dataSource, itemGen, attributes.keyGenFunc_,
        attributes.onMove_, attributes.itemDragEvent_, true);
}

// onMoveFromTo has no operation in non-virtual mode
function onMoveFromTo(moveFrom: int32, moveTo: int32): void {}

/** @memo */
function nonVirtualRender<T>(arr: RepeatArray<T>,
    /** @memo */
    itemGenerator: RepeatItemBuilder<T>,
    keyGenerator?: (element: T, index: int32) => string,
    onMove?: OnMoveHandler,
    itemDragEvent?: ItemDragEventHandler,
): void {
    if (keyGenerator && typeof keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    let nodeHolder = remember(() => new NodeHolder())
    const defaultKey = (e: T, idx: int32): string => {
        try {
            return `${idx}__${JSON.stringify(e)}`
        } catch (e) {
            throw new Error(
                'Repeat: use of default key generator not possible on provided data structure.' +
                'Need to specify key(). Application Error!')
        }
    };
    const keyGen = (ele: T, i: int32): KoalaCallsiteKey =>
        keyGenerator ? hashCodeFromString(keyGenerator!(ele, i)) : hashCodeFromString(defaultKey(ele, i));
    /** @memo */
    const action = (ele: T, i: int32) => {
        const ri = new RepeatItemImpl<T>(ele, i);
        NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
            itemGenerator(ri);
        });
    };
    NodeAttach(() => ForEachNodePeer.create(true), (node: ForEachNodePeer) => {
        RepeatByArray<T>(arr, keyGen, action);
        nodeHolder.node = node;
    });

    /**
     * provide onMove callbacks to the backend if onMove is set，and reset callbacks if onMove is unset
     */
    ForEachOps.SyncOnMoveOps(nodeHolder.node!.getPeerPtr(), new Array<KPointer>(), onMove, itemDragEvent);

    ArkUIAniModule._ForEach_FinishRender(nodeHolder.node!.getPeerPtr());
}
