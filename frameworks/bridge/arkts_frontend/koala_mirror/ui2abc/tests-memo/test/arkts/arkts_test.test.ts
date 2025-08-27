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
import { TestNode, testRoot, testTick, mutableState, GlobalStateManager, StateContext } from "@koalaui/runtime"
import { __id, __key, __context } from "@koalaui/runtime"

import defaultSharedMemoFunction from "../common/main_test_module_to_import"
import { SharedLog } from "../common/test_module_to_import"


function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    Assert.deepEqual(actual, asArray(expected))
}

class GlobalStateHolder {
    static globalState = GlobalStateManager.instance.mutableState<number>(0, true)
}

interface B {
    /** @memo */
    propFunctionB: () => void
    /** @memo */
    testPropB(): void

    localLog: Array<string>
}

class A implements B {
    localLog: Array<string>
    constructor(localLog: Array<string>) {
        this.localLog = localLog
    }

    /** @memo */
    testPropB(): void {
        GlobalStateHolder.globalState.value
        this.localLog.push("propFunctionB call")
        this.propFunctionB()
    }

    /** @memo */
    propFunctionB =
        /** @memo */
        () => {
            this.localLog.push("propFunctionB")
        }

    /** @memo */
    private privatePropFunction =
        /** @memo */
        () => {
            this.localLog.push("initial privatePropFunction")
        }

    /** @memo */
    set customPropFunction(
        /** @memo */
        value:
            () => void
    ) {
        this.privatePropFunction = value
    }

    /** @memo */
    get customPropFunction():
        () => void {
        return this.privatePropFunction
    }

    /** @memo */
    testCustomPropFunction() {
        GlobalStateHolder.globalState.value
        this.localLog.push("customPropFunction call")
        this.privatePropFunction()
    }
}

class TestImportedMemo {
    /** @memo */
    static testDefaultImportedFunction(): void {
        GlobalStateHolder.globalState.value
        SharedLog.log.push('testDefaultImportedFunction call')
        defaultSharedMemoFunction()
    }
}

suite("[ARKTS+COMPILER PLUGIN] Basic memo semantic", () => {
    test("Property of functional type in interface", () => {
        // NOTE: should work with memo-plugin in the future

        const instance: B = new A(new Array<string>())
        const root = testRoot(
            /** @memo */
            () => { instance.testPropB() }
        )
        assertResultArray(instance.localLog,
            "propFunctionB call",
            "propFunctionB"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.localLog,
            "propFunctionB call",
            "propFunctionB",
            "propFunctionB call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.localLog,
            "propFunctionB call",
            "propFunctionB",
            "propFunctionB call",
            "propFunctionB call",
        )
    })

    test("Getter/setter of functional type", () => {
        // NOTE: should work with memo-plugin in the future

        const instance: A = new A(new Array<string>())
        instance.customPropFunction =
            /** @memo */
            () => { instance.localLog.push('lala') }
        const root = testRoot(
            /** @memo */
            () => { instance.testCustomPropFunction() }
        )
        assertResultArray(instance.localLog,
            "customPropFunction call",
            "lala"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.localLog,
            "customPropFunction call",
            "lala",
            "customPropFunction call"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.localLog,
            "customPropFunction call",
            "lala",
            "customPropFunction call",
            "customPropFunction call"
        )
    })
})

suite("[ARKTS+COMPILER PLUGIN] Memo functions with all kinds of import and export statements", () => {
    test("Default import", () => {
        // NOTE: should work with memo-plugin in the future

        SharedLog.log.length = 0
        const root = testRoot(
            /** @memo */
            () => { TestImportedMemo.testDefaultImportedFunction() }
        )
        assertResultArray(SharedLog.log,
            "testDefaultImportedFunction call",
            "defaultSharedMemoFunction"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(SharedLog.log,
            "testDefaultImportedFunction call",
            "defaultSharedMemoFunction",
            "testDefaultImportedFunction call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(SharedLog.log,
            "testDefaultImportedFunction call",
            "defaultSharedMemoFunction",
            "testDefaultImportedFunction call",
            "testDefaultImportedFunction call",
        )
    })
})

export const __ARKTEST__ = "arkts_test.test"
