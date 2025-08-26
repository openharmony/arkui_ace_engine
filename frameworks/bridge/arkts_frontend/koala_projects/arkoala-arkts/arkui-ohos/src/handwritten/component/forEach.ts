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

import { int32, hashCodeFromString } from '@koalaui/common';
import { memoEntry2, __context, NodeAttach } from '@koalaui/runtime';
import { InteropNativeModule } from '@koalaui/interop';
import { SyntaxItemPeer, ForEachNodePeer } from '../handwritten/RepeatImpl';

/** @memo */
export function ForEach<T>(
    arr: () => Array<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    if (arr === null || arr === undefined) {
        InteropNativeModule._NativeLog('input array function is null or undefined error. Application error!');
        return;
    }
    if (typeof itemGenerator !== 'function') {
        InteropNativeModule._NativeLog('item generator function missing. Application error!');
        return;
    }
    if (keyGenerator !== undefined && typeof keyGenerator !== 'function') {
        InteropNativeModule._NativeLog('key generator is not a function. Application error!');
        return;
    }
    /** @memo */
    const createAndUpdate = (): void => {
        const array: Array<T> = arr();
        if (array === null || array === undefined) {
            InteropNativeModule._NativeLog('input array is null or undefined error. Application error!');
            return;
        }
        const length: number = array.length;
        const key = (element: T, index: int32): int32 => keyGenerator ? hashCodeFromString(keyGenerator!(element, (index as number))) : index;
        /** @memo */
        const action = (element: T, index: int32): void => {
            NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
                itemGenerator(element, (index as number));
            });
        };
        for (let i = 0; i < length; i++) {
            const e: T = array[i];
            memoEntry2<T, int32, void>(__context(), key(e, i), action, e, i);
        }
    }
    NodeAttach(() => ForEachNodePeer.create(), (node: ForEachNodePeer) => {
        createAndUpdate();
    });
}
