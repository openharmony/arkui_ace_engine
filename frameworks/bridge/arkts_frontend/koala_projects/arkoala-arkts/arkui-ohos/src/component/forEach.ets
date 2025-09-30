/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { int32, hashCodeFromString } from '@koalaui/common'
import { memoEntry2, __context, NodeAttach, remember } from '@koalaui/runtime'
import { SyntaxItemPeer, ForEachNodePeer } from '../base/RepeatImpl'
import { DynamicNode, OnMoveHandler, ItemDragEventHandler, LazyForEachOps } from '#generated'
import { NodeHolder } from '../base/LazyForEachImpl'
import { ArkUIAniModule } from '../ani/arkts/ArkUIAniModule'

export interface ForEachAttribute<T> extends DynamicNode {
    arr: () => Array<T>;
    setForEachOptions(arr: () => Array<T>,
        /** @memo */
        itemGenerator: (item: T, index: int32) => void,
        keyGenerator?: (item: T, index: int32) => string): this {
        return this;
    }
    onMove(handler?: OnMoveHandler): this {
        return this;
    }
    onMove(handler?: OnMoveHandler, eventHandler?: ItemDragEventHandler): this {
        return this;
    }
}

export class ArkForEachComponent<T> implements ForEachAttribute<T> {
    arr: () => Array<T> = () => new Array<T>();
    /** @memo */
    itemGenerator: (item: T, index: int32) => void = (item: T, index: int32) => {};
    keyGenerator?: (item: T, index: int32) => string = undefined;
    onMoveEvent?: OnMoveHandler = undefined;
    itemDragEvent?: ItemDragEventHandler = undefined;

    public onMove(handler?: OnMoveHandler): this {
        this.onMoveEvent = handler;
        return this;
    }

    public onMove(handler?: OnMoveHandler, eventHandler?: ItemDragEventHandler): this {
        this.onMoveEvent = handler;
        this.itemDragEvent = eventHandler;
        return this;
    }

    public setForEachOptions(arr: () => Array<T>,
        /** @memo */
        itemGenerator: (item: T, index: int32) => void,
        keyGenerator?: (item: T, index: int32) => string): this {
        this.arr = arr;
        this.itemGenerator = itemGenerator;
        this.keyGenerator = keyGenerator;
        return this;
    }
}

function onMoveFromTo(moveFrom: int32, moveTo: int32): void {}

/** @memo */
export function ForEachImpl<T>(
    /** @memo */
    style: ((attributes: ForEachAttribute<T>) => void) | undefined
) {
    const receiver = remember(() => {
        return new ArkForEachComponent<T>()
    })
    style?.(receiver)
    if (receiver.arr === null || receiver.arr === undefined) {
        throw new Error('input array function is null or undefined error. Application error!');
    }
    if (typeof receiver.itemGenerator !== 'function') {
        throw new Error('item generator function missing. Application error!');
    }
    if (receiver.keyGenerator !== undefined && typeof receiver.keyGenerator !== 'function') {
        throw new Error('key generator is not a function. Application error!');
    }
    let nodeHolder = remember(() => new NodeHolder())
    /** @memo */
    const createAndUpdate = (): void => {
        const array: Array<T> = receiver.arr();
        if (array === null || array === undefined) {
            throw new Error('input array is null or undefined error. Application error!');
        }
        const length: int32 = array.length;
        const key = (element: T, index: int32): int32 =>
            receiver.keyGenerator ? hashCodeFromString(receiver.keyGenerator!(element, index)) : index;
        /** @memo */
        const action = (element: T, index: int32): void => {
            NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
                receiver.itemGenerator(element, index);
            });
        };
        for (let i = 0; i < length; i++) {
            const e: T = array[i];
            memoEntry2<T, int32, void>(__context(), key(e, i), action, e, i);
        }
    }
    NodeAttach(() => ForEachNodePeer.create(), (node: ForEachNodePeer) => {
        createAndUpdate();
        nodeHolder.node = node;
    });

    /**
     * provide onMove callbacks to the backend if onMove is set，and reset callbacks if onMove is unset
     */
    LazyForEachOps.SyncOnMoveOps(nodeHolder.node!.getPeerPtr(),
        onMoveFromTo,
        receiver.onMoveEvent,
        receiver.itemDragEvent);

    ArkUIAniModule._ForEach_FinishRender(nodeHolder.node!.getPeerPtr());
}
