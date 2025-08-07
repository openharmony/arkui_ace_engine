/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { KoalaCallsiteKey, int32 } from "@koalaui/common"
import { __context, __id } from "../internals"
import { memoEntry1, memoEntry2 } from "./entry"
import { __memo_context_type, __memo_id_type } from "../internals"

/**
 * Sequentially repeats the {@link action}.
 *
 * An {@link action} unit accepts a sequential index as an argument.
 *
 * @param count the number of {@link action}'s to repeat, 0 by default
 * @param action an action to repeat
 *
 * @see RepeatWithKey
 * @see RepeatByArray
 * @see Items
 */
/** @memo */
export function Repeat(
    count: int32,
    /** @memo */
    action: (index: int32) => void
): void {
    for (let i = 0; i < count; i++) {
        memoEntry1<int32, void>(__context(), i, action, i)
    }
}

/**
 * Sequentially repeats the {@link action} using the {@link key} callback.
 *
 * By default, each {@link action} has an implicit key which provides the {@link action}'s
 * result uniqueness. The {@link key} callback can be used to provide a custom key per
 * {@link action}, based on the {@link action}'s index accepted as an argument.
 *
 * @param count the number of {@link action}'s to repeat, 0 by default
 * @param key a callback to provide custom keys
 * @param action an action to repeat
 *
 * @see Repeat
 */
/** @memo */
export function RepeatWithKey(
    count: int32,
    key: (index: int32) => KoalaCallsiteKey,
    /** @memo */
    action: (index: int32) => void
): void {
    for (let i = 0; i < count; i++) {
        memoEntry1<int32, void>(__context(), key(i), action, i)
    }
}

/**
 * Sequentially repeats the {@link action} by iterating the {@link array},
 * passing an element of the {@link array} as the {@link action}'s argument.
 *
 * @param array the array to iterate
 * @param key a callback to provide custom keys
 * @param action an action to repeat
 *
 * @see RepeatWithKey
 */
/** @memo */
export function RepeatByArray<T>(
    array: ReadonlyArray<T>,
    key: (element: T, index: int32) => KoalaCallsiteKey,
    /** @memo */
    action: (element: T, index: int32) => void
): void {
    const length = array.length
    for (let i = 0; i < length; i++) {
        const e: T = array[i]
        memoEntry2<T, int32, void>(__context(), key(e, i), action, e, i)
    }
}

/**
 * Sequentially repeats the {@link action} for every element in the given range.
 *
 * @param start - the start index, inclusive
 * @param end - the end index, exclusive
 * @param element - the function to provide an element by its index
 * @param key - the function to provide a key for the element
 * @param action - the memo function to be invoked for every element
 */
/** @memo */
export function RepeatRange<T>(
    start: int32,
    end: int32,
    element: (index: int32) => T,
    key: (element: T, index: int32) => KoalaCallsiteKey,
    /** @memo */
    action: (element: T, index: int32) => void
): void {
    for (let i: int32 = start; i < end; i++) {
        const e: T = element(i)
        memoEntry2<T, int32, void>(__context(), key(e, i), action, e, i)
    }
}
