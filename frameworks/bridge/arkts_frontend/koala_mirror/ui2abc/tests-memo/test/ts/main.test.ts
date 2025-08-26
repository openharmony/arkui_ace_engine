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

import { assert, suite, test } from "@koalaui/harness"
import { asArray, int32 } from "@koalaui/common"
import { testRoot, testTick, GlobalStateManager } from "@koalaui/runtime"
import { __id, __key, __context } from "@koalaui/runtime"

import { separatedMemoFunction, SharedLog } from "../common/main_test_module_to_import"
import defaultSharedMemoFunction from "../common/main_test_module_to_import"

function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    assert.deepEqual(actual, asArray(expected))
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

    /** @memo */
    static testDefaultImportedFunction(): void {
        GlobalStateHolder.globalState.value
        SharedLog.log.push('testDefaultImportedFunction call')
        defaultSharedMemoFunction()
    }
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

suite("[TS+COMPILER PLUGIN]", () => {
    suite("Basic memo semantic", () => {
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

    suite("Memo functions with all kinds of import and export statements", () => {
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

    suite("tests from [ARKTS+COMPILER PLUGIN]", () => {
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
})
