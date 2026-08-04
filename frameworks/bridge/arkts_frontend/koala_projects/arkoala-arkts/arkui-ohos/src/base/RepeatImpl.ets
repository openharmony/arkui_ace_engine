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
import { __context, __id, memoEntry2, remember, NodeAttach, contextNode, scheduleCallback } from '@koalaui/runtime'
import { RepeatItem, RepeatAttribute, RepeatArray, RepeatItemBuilder, TemplateTypedFunc, VirtualScrollOptions, TemplateOptions, RepeatMemOptStrategy } from '../component/repeat'
import { IDataSource, DataChangeListener } from '../component/lazyForEach'
import { OnMoveHandler, ItemDragEventHandler, ForEachOps } from '#generated'
import { LazyForEachImplForOptions } from './LazyForEachImpl'
import { InternalListener } from './DataChangeListener'
import { ArkUIAniModule } from '../ani/arkts/ArkUIAniModule'
import { SyntaxItemPeer, ForEachNodePeer, LazyNodePeer, NodeHolder } from './SyntaxNodeBase'
import { ObserveSingleton } from '../stateManagement/base/observeSingleton'
import { ExtendableComponent } from '../component/extendableComponent'
import { IMutableStateMeta } from '../stateManagement/decorator'
import { FactoryInternal } from '../stateManagement/base/iFactoryInternal'

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
        if (repeat.useTemplate_) {
            throw new Error('Repeat: template function is not supported in non-virtualScroll mode.');
        }
        nonVirtualRender<T>(arr, repeat);
    } else {
        virtualRender<T>(arr, repeat, __id());
    }
}

class RepeatItemImpl<T> implements RepeatItem<T> {
    private arr_: RepeatArray<T>;
    private index_: int32;
    private version: IMutableStateMeta;

    constructor(arr: RepeatArray<T>, index: int32) {
        this.arr_ = arr;
        this.index_ = index;
        this.version = FactoryInternal.mkMutableStateMeta('__backing_repeat_item_version');
    }

    get arr(): RepeatArray<T> {
        this.version;
        return this.arr_;
    }

    get item(): T {
        this.version;
        return this.arr_[this.index_];
    }

    get index(): int32 {
        this.version;
        return this.index_;
    }
}

export class ActiveRangeInfo {
    start: int32 = -1;
    end: int32 = -1;
    cacheStart: int32 = -1;
    cacheEnd: int32 = -1;
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

    updateData(newArr: RepeatArray<T>, totalCount: int32, updateAll: boolean = false) {
        // Shallow compare: check length and each element by reference
        if (totalCount !== this.total_ || updateAll) {
            this.listener_?.update(0, Number.POSITIVE_INFINITY.toInt(), totalCount - this.total_);
            this.arr_ = newArr;
            this.total_ = totalCount;
            return;
        }
        // check each element
        for (let i = 0; i < newArr.length; i++) {
            if (this.arr_[i] !== newArr[i]) {
                this.listener_?.update(i, Number.POSITIVE_INFINITY.toInt(), 0);
                this.arr_ = newArr;
                this.total_ = totalCount;
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
    key2Index_: Map<string, int32> = new Map<string, int32>();
    reuseCount_: Map<string, int32> = new Map<string, int32>();
    activeRange_: ActiveRangeInfo = new ActiveRangeInfo();

    reusable_: boolean = true;
    disableVirtualScroll_: boolean = false;
    memoryOptimizationStrategy_: int32 = 0;

    useTemplate_: boolean = false; // whether use template function

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
        this.memoryOptimizationStrategy_ =
            (options?.memoryOptimizationStrategy ?? RepeatMemOptStrategy.DEFAULT).valueOf() as int32;
        return this;
    }

    template(
        type: string, itemBuilder: RepeatItemBuilder<T>, templateOptions?: TemplateOptions): RepeatAttributeImpl<T> {
        if (itemBuilder === undefined || typeof itemBuilder !== 'function') {
            throw new Error('template generator function missing. Application error!');
        }
        this.itemGenFuncs_.set(type, itemBuilder);
        this.templateCacheSize_.set(type, templateOptions?.cachedCount ?? Number.POSITIVE_INFINITY.toInt());
        this.useTemplate_ = true;
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
    
    debugLine(sourceLine: string, moduleName?: string): this {
        return this
    }
}

/** @memo:intrinsic */
function getCurrentEnv(): [int32, object | undefined] {
    return [ObserveSingleton.RenderingComponentV2, ExtendableComponent.current];
}

/** @memo:intrinsic */
function wrapBuilder(env: [int32, object | undefined], builder_: () => void): void {
    const lastRenderingComponent = ObserveSingleton.RenderingComponentV2;
    const lastExtendableComponent = ExtendableComponent.current;
    ObserveSingleton.instance.renderingComponent = env[0];
    ExtendableComponent.current = env[1];
    builder_();
    ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
    ExtendableComponent.current = lastExtendableComponent;
}

function defaultRepeatKey<T>(item: T, index: int32): string {
    try {
        return `${index}__${JSON.stringify(item)}`;
    } catch (e) {
        throw new Error(
            'unstable key generator function. Need to specify Repeat.key()' +
            'Application Error: ' + (e as Error).message);
    }
}

function getRepeatItemKey<T>(
    keyGenerator: ((item: T, index: int32) => string) | undefined,
    item: T,
    index: int32
): string {
    return keyGenerator ? keyGenerator(item, index) : defaultRepeatKey(item, index);
}

function getRepeatTemplateKey(templateType: string, repeatId: KoalaCallsiteKey): string {
    return `${templateType}${repeatId}`;
}

export function getRepeatReuseKey<T>(
    item: T,
    index: int32,
    repeatId: KoalaCallsiteKey,
    itemGenFuncs: Map<string, RepeatItemBuilder<T>>,
    ttypeGenFunc: TemplateTypedFunc<T>,
    keyGenerator?: (item: T, index: int32) => string
): string {
    let templateType = ttypeGenFunc(item, index);
    if (!itemGenFuncs.has(templateType)) {
        templateType = REPEAT_EACH_FUNC_TYPE;
    }
    return `${getRepeatTemplateKey(templateType, repeatId)}@Repeat@${getRepeatItemKey(keyGenerator, item, index)}`;
}

/** @memo:intrinsic */
function virtualRender<T>(
    arr: RepeatArray<T>,
    attributes: RepeatAttributeImpl<T>,
    repeatId: KoalaCallsiteKey,
): void {
    const keyGenerator = attributes.keyGenFunc_;
    if (keyGenerator && typeof keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    let dataSource = remember(() => new RepeatDataSource<T>(arr));
    const total = attributes.userDefinedTotal_ ?? arr.length;
    dataSource.updateData(arr, total >= 0 ? total : arr.length,
        ArkUIAniModule._Repeat_IsImplicitAnimationOpen(0) !== 0);
    if (!attributes.onLazyLoading_ && dataSource.totalCount() > arr.length) {
        console.error(`(${repeatId}) totalCount must not exceed the array length without onLazyLoading callback.`);
    }
    dataSource.setOnLazyLoading(attributes.onLazyLoading_);
    const activeRangeReuseKeys = remember(() => new Map<int32, string>());
    const initRepeatReusePool = (node: LazyNodePeer): void => {
        attributes.templateCacheSize_.forEach((size: int32, template: string) => {
            node.setRepeatTemplatePoolSize(size, getRepeatTemplateKey(template, repeatId));
        });
    };
    const updateRepeatActiveRange = (
        node: LazyNodePeer,
        activeIndices: int32[],
        missingActiveIndices: int32[]
    ): void => {
        const previousActiveRangeReuseKeys = node.getRepeatActiveRangeReuseKeys();
        activeRangeReuseKeys.clear();
        activeIndices.forEach((activeIndex: int32) => {
            if (activeIndex < 0 || activeIndex >= arr.length) {
                return;
            }
            activeRangeReuseKeys.set(activeIndex, getRepeatReuseKey(arr[activeIndex], activeIndex, repeatId,
                attributes.itemGenFuncs_, attributes.ttypeGenFunc_, keyGenerator));
        });
        node.setRepeatActiveRangeReuseKeys(activeRangeReuseKeys);

        const targetReuseKeys: string[] = [];
        missingActiveIndices.forEach((activeIndex: int32) => {
            if (activeIndex < 0 || activeIndex >= arr.length) {
                return;
            }
            targetReuseKeys.push(activeRangeReuseKeys.get(activeIndex)!);
        });
        if (targetReuseKeys.length === 0 && previousActiveRangeReuseKeys.size === 0) {
            return;
        }
        node.prepareRepeatReusePlan(targetReuseKeys);
    };

    /** @memo */
    const itemGen = (item: T, index: int32): void => {
        const ri = new RepeatItemImpl<T>(arr, index);
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
            const tag = getRepeatReuseKey(item, index, repeatId, attributes.itemGenFuncs_, attributes.ttypeGenFunc_,
                keyGenerator);
            const env = getCurrentEnv();
            NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
                wrapBuilder(env, () => { itemBuilder(ri); })
            }, tag); // using template + repeat key as reuseKey
        } else {
            itemBuilder(ri);
        }
    };
    LazyForEachImplForOptions<T>(dataSource, itemGen, attributes.keyGenFunc_, attributes.onMove_,
        attributes.itemDragEvent_, undefined, true, attributes.memoryOptimizationStrategy_, initRepeatReusePool,
        updateRepeatActiveRange, arr, attributes.itemGenFuncs_, attributes.ttypeGenFunc_, repeatId);
}

/** @memo */
function nonVirtualRender<T>(
    arr: RepeatArray<T>,
    attributes: RepeatAttributeImpl<T>
): void {
    const keyGenerator = attributes.keyGenFunc_;
    if (keyGenerator && typeof keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    let nodeHolder = remember(() => new NodeHolder())
    const indexInActiveRange = (index: int32): boolean => {
        return index >= attributes.activeRange_.start - attributes.activeRange_.cacheStart &&
        index <= attributes.activeRange_.end + attributes.activeRange_.cacheEnd;
    }

    const keyGen = (ele: T, i: int32): KoalaCallsiteKey => {
        const rawKey = getRepeatItemKey(keyGenerator, ele, i);
        const oldIndex = attributes.key2Index_.get(rawKey);
        let keyWithCount = rawKey;

        if (oldIndex && !indexInActiveRange(oldIndex!) && indexInActiveRange(i) &&
            ArkUIAniModule._ForEach_IsImplicitAnimationOpen()) {
                // the key is new in active range
                const val = attributes.reuseCount_.has(rawKey)? attributes.reuseCount_.get(rawKey): 0;
                attributes.reuseCount_.set(rawKey, (val! + 1));
            }

            if (attributes.reuseCount_.has(rawKey)) {
                keyWithCount = rawKey + '_' + attributes.reuseCount_.get(rawKey);
            }
            const ret = hashCodeFromString(keyWithCount);
            return ret;
    }

    /** @memo */
    const itemGen = (ele: T, i: int32) => {
        /** @memo */
        const itemGenerator = attributes.itemGenFuncs_.get(REPEAT_EACH_FUNC_TYPE)!;
        const ri = new RepeatItemImpl<T>(arr, i);
        const env = getCurrentEnv();
        NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
            wrapBuilder(env, () => { itemGenerator(ri); })
        });
    };

    const env = getCurrentEnv();
    NodeAttach(() => ForEachNodePeer.create(true), (node: ForEachNodePeer) => {
        wrapBuilder(env, () => {
            for (let i = 0; i < arr.length; i++) {
                const e: T = arr[i];
                memoEntry2<T, int32, void>(__context(), keyGen(e, i), itemGen, e, i);
                attributes.key2Index_.set(getRepeatItemKey(keyGenerator, e, i), i);
            }
        })
        nodeHolder.node = node;
    });

    ForEachOps.Sync(nodeHolder.node!.getPeerPtr(), (start: int32, end: int32, cacheStart: int32, cacheEnd: int32,
        isLoop: boolean) => {
        attributes.activeRange_.start = Math.max(0, start - cacheStart).toInt();
        attributes.activeRange_.end = end + cacheEnd;
        attributes.activeRange_.cacheStart = cacheStart;
        attributes.activeRange_.cacheEnd = cacheEnd;
    });

    /**
     * provide onMove callbacks to the backend if onMove is set，and reset callbacks if onMove is unset
     */
    ForEachOps.SyncOnMoveOps(
        nodeHolder.node!.getPeerPtr(), new Array<KPointer>(), attributes.onMove_, attributes.itemDragEvent_);

    ArkUIAniModule._ForEach_FinishRender(nodeHolder.node!.getPeerPtr());
}
