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

/**
 * Tests for specific arkts constructions
 * separate file because of incompatibility with ts syntax
 */

import { Assert, suite, test } from "@koalaui/harness"
import { asArray, int32 } from "@koalaui/common"
import { testRoot, testTick, GlobalStateManager } from "@koalaui/runtime"
import { __id, __key, __context } from "@koalaui/runtime"

import {
    SharedLog,
    sharedMemoFunction,
    GlobalStateHolder,
    Log,
    assertResultArray,
} from "./utils"

GlobalStateHolder.globalState = GlobalStateManager.instance.mutableState<number>(0, true)
SharedLog.log = new Array<string>()

class Dummy {}

/** @memo */
function functionWithReceiver(this: Dummy, log: Array<string>) {
    log.push("function with receiver")
}

class TestFunctionWithReceiver extends Log {
    /** @memo */
    callFunctionWithReceiver(log: Array<string>) {
		let a = new Dummy()
		functionWithReceiver(a, log)
		a.functionWithReceiver(log)
    }

    /** @memo */
    test() {
        this.log.push("function with receiver call")
        GlobalStateHolder.globalState.value
        this.callFunctionWithReceiver(this.log)
    }
}

suite("Functions with receiver", () => {
    test("Global function with receiver", () => {
        const instance = new TestFunctionWithReceiver()
        const root = testRoot(instance.test)
        assertResultArray(instance.log,
            "function with receiver call",
            "function with receiver",
            "function with receiver",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "function with receiver call",
            "function with receiver",
            "function with receiver",
            "function with receiver call",
        )
    })
})

export const __ARKTEST__ = "basic.test"
