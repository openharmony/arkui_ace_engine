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
import { pointer } from '@koalaui/interop'
import { memoEntry2, __context, NodeAttach, remember } from '@koalaui/runtime'
import { SyntaxItemPeer, ForEachNodePeer } from '../base/SyntaxNodeBase'
import { DynamicNode, OnMoveHandler, ItemDragEventHandler, ForEachOps } from '#generated'
import { PeerNode } from '../PeerNode'
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

class ForEachManager {
    node?: PeerNode
    keys: Array<int32> = new Array<int32>()
    additionalChild: Array<pointer> = new Array<pointer>()
}

/** @memo:intrinsic */
function forEachAttach<T>(receiver: ArkForEachComponent<T>, manager: ForEachManager) {
    manager.additionalChild = new Array<pointer>()
    let newKeys = new Array<int32>()
    let duplicateIndex = new Array<int32>()
    let diffIndex = new Array<int32>()
    let key2Index = new Map<int32, int32>()
    /** @memo */
    const createAndUpdate = (): void => {
        const array: Array<T> = receiver.arr();
        if (array === null || array === undefined) {
            throw new Error('input array is null or undefined error. Application error!');
        }
        const defaultKey = (e: T, idx: int32): string => {
            try {
                return `${idx}__${JSON.stringify(e)}`
            } catch (e) {
                throw new Error('ForEach: use of default key generator not possible on provided data structure.' +
                    'Need to specify key generator function (ForEach 3rd parameter). Application Error!')
            }
        }
        const keyGen = (e: T, idx: int32): int32 => receiver.keyGenerator
            ? hashCodeFromString(receiver.keyGenerator!(e, idx)) : hashCodeFromString(defaultKey(e, idx))
        array.forEach((item: T, idx: number) => {
            const key: int32 = keyGen(item, idx.toInt())
            newKeys.push(key)
            if (manager.keys.indexOf(key) === -1) {
                diffIndex.push(idx.toInt())
            }
        })
        newKeys.forEach((key: int32, idx: number) => {
            if (key2Index.has(key)) {
                duplicateIndex.push(idx.toInt())
            } else {
                key2Index.set(key, idx.toInt())
            }
        })

        /** @memo */
        const action = (e: T, idx: int32): void => {
            NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
                receiver.itemGenerator(e, idx);
                if (diffIndex.indexOf(idx) !== -1) {
                    manager.additionalChild.push(node.getPeerPtr())
                }
            }, 'for_each_item_' + newKeys[idx])
        }
        key2Index.forEach((idx: int32, key: int32) => {
            memoEntry2<T, int32, void>(__context(), key, action, array[idx], idx);
        })
        manager.keys = newKeys
    }
    NodeAttach(() => ForEachNodePeer.create(), (node: ForEachNodePeer) => {
        createAndUpdate();
        manager.node = node;
    });
}

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
    let manager = remember(() => new ForEachManager())
    forEachAttach<T>(receiver, manager);

    /**
     * provide onMove callbacks to the backend if onMove is set, and reset callbacks if onMove is unset
     */
    ForEachOps.SyncOnMoveOps(manager.node!.getPeerPtr(),
        manager.additionalChild,
        receiver.onMoveEvent,
        receiver.itemDragEvent);

    ArkUIAniModule._ForEach_FinishRender(manager.node!.getPeerPtr());
}
