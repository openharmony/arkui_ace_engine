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

import { Assert, suite, test } from "@koalaui/harness"
import { asArray, int32 } from "@koalaui/common"
import { TestNode, testRoot, testTick, mutableState, GlobalStateManager, StateContext, MutableState } from "@koalaui/runtime"
import { __id, __key, __context } from "@koalaui/runtime"

export class SharedLog {
    static log: Array<string> = new Array<string>()
}

/** @memo */
export function sharedMemoFunction() {
    SharedLog.log.push("sharedMemoFunction")
}

export class GlobalStateHolder {
    static globalState: MutableState<number> = GlobalStateManager.instance.mutableState<number>(0, true)
}

export class Log {
    log: Array<string> = new Array<string>()
}

export function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    Assert.deepEqual(actual, asArray(expected))
}
