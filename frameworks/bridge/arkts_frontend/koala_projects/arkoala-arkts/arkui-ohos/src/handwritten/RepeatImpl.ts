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
import { RepeatItem, UIRepeatAttribute, RepeatArray, TemplateTypedFunc, VirtualScrollOptions, TemplateOptions } from './Repeat';
import { RepeatType } from '../PeerNode';

export class RepeatDataNode<T> extends DataNode<T> {
    constructor(kind: uint32 = 1) {
        super(kind);
    }
}

class RepeatItemImpl<T> implements RepeatItem<T> {
    __item: T;
    __index?: number;
    
    constructor(initialItem: T, initialIndex: number) {
        this.__item = initialItem;
        this.__index = initialIndex;
    }

    get item(): T {
        return this.__item;
    }

    get index(): number | undefined {
        return this.__index;
    }

    public updateItem(newItem: T): void {
        this.__item = newItem;
    }

    public updateIndex(newIndex: number): void {
        this.__index = newIndex;
    }
}

export class UIRepeatAttributeImpl<T> implements UIRepeatAttribute<T> {
    arr_: RepeatArray<T>;
    /** @memo */
    itemGenFunc_?: (repeatItem: RepeatItem<T>) => void;
    keyGenFunc_?: (item: T, index: number) => string;
    keyGenFuncSpecified_?: boolean;

    // .vritualScroll
    totalCount_?: number | (() => number);
    totalCountSpecified_?: boolean;
    reusable_?: boolean;
    isVirtualScroll_: boolean = false;

    constructor(arr: RepeatArray<T>) {
        this.arr_ = arr;
    }

    /** @memo */
    each(
        /** @memo */
        itemGenerator: (repeatItem: RepeatItem<T>) => void
    ): UIRepeatAttributeImpl<T> {
        if (itemGenerator === undefined || typeof itemGenerator !== 'function') {
            throw new Error('item generator function missing. Application error!');
        }
        this.itemGenFunc_ = itemGenerator;
        return this;
    }

    /** @memo */
    key(keyGenerator: (item: T, index: number) => string): UIRepeatAttributeImpl<T> {
        if (keyGenerator === undefined || typeof keyGenerator !== 'function') {
            throw new Error('key generator function missing. Application error!');
        }
        this.keyGenFunc_ = keyGenerator;
        this.keyGenFuncSpecified_ = true;
        return this;
    }

    /** @memo */
    virtualScroll(options?: VirtualScrollOptions): UIRepeatAttributeImpl<T> {
        this.isVirtualScroll_ = true;
        return this;
    }

    /** @memo */
    template(type: string,
        /** @memo */
        itemBuilder: (repeatItem: RepeatItem<T>) => void,
        templateOptions?: TemplateOptions
    ): UIRepeatAttributeImpl<T> {
        if (itemBuilder === undefined || typeof itemBuilder !== 'function') {
            throw new Error('template generator function missing. Application error!');
        }
        return this;
    }

    /** @memo */
    templateId(typedFunc: TemplateTypedFunc<T>): UIRepeatAttributeImpl<T> {
        if (typedFunc === undefined || typeof typedFunc !== 'function') {
            throw new Error('templateId generator function missing. Application error!');
        }
        return this;
    }

    /** @memo */
    render(): void {
        attachChild<T>(this.arr_, this.itemGenFunc_!, this.keyGenFunc_);
    }
}

/** @memo */
function attachChild<T>(
    arr: RepeatArray<T>,
    /** @memo */
    itemGenerator: (repeatItem: RepeatItem<T>) => void,
    keyGenerator?: (element: T, index: number) => string
): void {
    if (typeof keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    const keyGen = (ele: T, i: int32): KoalaCallsiteKey =>
        keyGenerator ? hashCodeFromString(keyGenerator!(ele, (i as number))) : i;
    RepeatByArray<T>(arr, keyGen, (ele: T, i: int32) => {
        const ri = new RepeatItemImpl<T>(ele, (i as number));
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
    receiver.render();
}