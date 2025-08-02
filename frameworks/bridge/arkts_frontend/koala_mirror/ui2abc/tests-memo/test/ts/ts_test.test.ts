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

import { separatedMemoFunction, SharedLog } from "../common/main_test_module_to_import"


function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    Assert.deepEqual(actual, asArray(expected))
}

class GlobalStateHolder {
    static globalState = GlobalStateManager.instance.mutableState<number>(0, true)
}

const globalLog = new Array<string>()


function returnListMemoFunctions(): [
    /** @memo */
    () => void,
    /** @memo */
    () => void
] {
    return [
        /** @memo */
        () => {
            globalLog.push('hi')
        },
        /** @memo */
        () => {
            GlobalStateHolder.globalState.value
            globalLog.push('hello')
        }
    ]
}

/** @memo */
const globalFunctionExpression = function () {
    globalLog.push("globalFunctionExpression")
}

/** @memo */
function testGlobalFunctionExpression() {
    GlobalStateHolder.globalState.value
    globalLog.push("globalFunctionExpression call")
    globalFunctionExpression()
}

const globalObjectLiteral = {
    /** @memo */
    objectLiteralMethod(): void {
        GlobalStateHolder.globalState.value
        globalLog.push("objectLiteralMethod")
    }
}

class TestImportedMemo {

    /** @memo */
    static testSeparatedImport(): void {
        GlobalStateHolder.globalState.value
        SharedLog.log.push('testSeparatedImport call')
        separatedMemoFunction()
    }

}

suite("[TS] Basic memo semantic", () => {
    test("Variable list member of functional type", () => {
        globalLog.length = 0
        const [fun1, fun2] = returnListMemoFunctions()
        const root = testRoot(
            fun2
        )
        assertResultArray(globalLog, "hello")
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(globalLog, "hello", "hello")
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(globalLog, "hello", "hello", "hello")
    })

    test("Function expression declaration", () => {
        globalLog.length = 0
        const root = testRoot(testGlobalFunctionExpression)
        assertResultArray(globalLog,
            "globalFunctionExpression call",
            "globalFunctionExpression"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(globalLog,
            "globalFunctionExpression call",
            "globalFunctionExpression",
            "globalFunctionExpression call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(globalLog,
            "globalFunctionExpression call",
            "globalFunctionExpression",
            "globalFunctionExpression call",
            "globalFunctionExpression call",
        )
    })

    test("Method declaration in object literal", () => {
        globalLog.length = 0
        const root = testRoot(
            /** @memo */
            () => { globalObjectLiteral.objectLiteralMethod() }
        )
        assertResultArray(globalLog, "objectLiteralMethod")

        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(globalLog, "objectLiteralMethod", "objectLiteralMethod")

        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(globalLog, "objectLiteralMethod", "objectLiteralMethod", "objectLiteralMethod")
    })
})

suite("[TS] Memo functions with all kinds of import and export statements", () => {
    test("Separated import", () => {
        SharedLog.log.length = 0
        const root = testRoot(TestImportedMemo.testSeparatedImport)
        assertResultArray(SharedLog.log,
            "testSeparatedImport call",
            "separatedMemoFunction",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(SharedLog.log,
            "testSeparatedImport call",
            "separatedMemoFunction",
            "testSeparatedImport call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(SharedLog.log,
            "testSeparatedImport call",
            "separatedMemoFunction",
            "testSeparatedImport call",
            "testSeparatedImport call",
        )
    })
})
