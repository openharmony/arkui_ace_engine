/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { KoalaCallsiteKey } from "@koalaui/common"
import { __context, __id } from "../internals"
import { StateContext } from "../states/State"
import { memoEntry1 } from "./entry"

/** @internal */
export class MemoCallbackContext {
    private readonly context: StateContext
    private readonly id: KoalaCallsiteKey

    private constructor(context: StateContext, id: KoalaCallsiteKey) {
        this.context = context
        this.id = id
    }

    /**
     * This method stores a memo context to call a memo-function later from non-memo-context.
     * Do not use this dangerous API if you do not understand the incremental engine deeply.
     * @see call
     * @internal
     */
     /** @memo */
    static Make(): MemoCallbackContext {
        return new MemoCallbackContext(__context(), __id())
    }

    /**
     * This method allows you to call a memo-function from non-memo-context.
     * It can be used only if the state manager is not available, for example, from native code.
     * Do not use this dangerous API if you do not understand the incremental engine deeply.
     * @internal
     */
    call(
        /** @memo */
        callback: (args: Int32Array) => number,
        args: Int32Array
    ): number {
        return memoEntry1(this.context, this.id, callback, args)
    }
}

/** @internal */
export function memoBind<T>(
    /** @memo */
    item: (arg: T) => void, value: T
):
    /** @memo */
    () => void
{
    return (
        /** @memo */
        () => { item(value) }
    )
}

/** @internal */
export function memoBind2<T1, T2>(
    /** @memo */
    item: (arg1: T1, arg2: T2) => void, value1: T1, value2: T2
):
    /** @memo */
    () => void
{
    return (
        /** @memo */
        () => { item(value1, value2) }
    )
}

/** @internal */
export function memoPartialBind2_1<T1, T2>(
    /** @memo */
    item: (arg1: T1, arg2: T2) => void,
    value1: T1
):
    /** @memo */
    (arg2: T2) => void
{
    return (
        /** @memo */
        (arg2: T2) => { item(value1, arg2) }
    )
}

/** @internal */
export function memoPartialBind3_2<T1, T2, T3>(
    /** @memo */
    item: (arg1: T1, arg2: T2, arg3: T3) => void,
    value1: T1
):
    /** @memo */
    (arg2: T2, arg3: T3) => void
{
    return (
        /** @memo */
    (arg2: T2, arg3: T3) => { item(value1, arg2, arg3) }
    )
}
