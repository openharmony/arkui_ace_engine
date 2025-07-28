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
import { assertResultArray, GlobalStateHolder } from "../testUtils"

GlobalStateHolder.globalState = GlobalStateManager.instance.mutableState<number>(0, true)
class Log {
    log = new Array<string>()
}

interface DataClass {
    value: number
    message: string
}

class TestObjectLiteralMemoization extends Log {
    /** @memo */
    test() {
        this.log.push("method with object parameter call")
        GlobalStateHolder.globalState.value
        this.methodWithObjectParameter({ message: "hello", value: 47 } as DataClass)
    }

    /** @memo */
    testWithParentheses() {
        this.log.push("method with object parameter call with parentheses")
        GlobalStateHolder.globalState.value
        this.methodWithObjectParameter(((({ message: "hello", value: 47 }))) as DataClass)
    }

    /** @memo */
    methodWithObjectParameter(data: DataClass) {
        this.log.push("method with object parameter", data.message)
    }
}

class TestMemoLambdaLiteralMemoization extends Log {
    /** @memo */
    test() {
        this.log.push("method with memo lambda parameter call")
        GlobalStateHolder.globalState.value
        this.methodWithMemoLambdaParameter((): void => { })
    }

    /** @memo */
    methodWithMemoLambdaParameter(
        /** @memo */
        param: () => void
    ) {
        param
        this.log.push("method with memo lambda parameter")
    }
}

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

class TestLambdaWithReceiver extends Log {
    /** @memo */
    callFunctionWithReceiver(log: Array<string>) {
        let a = new Dummy()
        type MemoT = @memo (this: Dummy, log: Array<string>) => void
        @memo let f: MemoT = (this: Dummy, log: Array<string>): void => {
            log.push("lambda with receiver")
        }
        f(a, log)
        a.f(log)
    }

    /** @memo */
    test() {
        this.log.push("lambda with receiver call")
        GlobalStateHolder.globalState.value
        this.callFunctionWithReceiver(this.log)
    }
}

suite("[ARKTS+MEMO PLUGIN] Memoizing non-primitive arguments", () => {
    test("Object literal memoization with parentheses", () => {
        const test = new TestObjectLiteralMemoization()
        const root = testRoot(
            /** @memo */
            () => { test.testWithParentheses() }
        )
        assertResultArray(test.log,
            "method with object parameter call with parentheses",
            "method with object parameter",
            "hello",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(test.log,
            "method with object parameter call with parentheses",
            "method with object parameter",
            "hello",
            "method with object parameter call with parentheses"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(test.log,
            "method with object parameter call with parentheses",
            "method with object parameter", "hello",
            "method with object parameter call with parentheses",
            "method with object parameter call with parentheses"
        )
    })

    test("Memo-lambda literal memoization", () => {
        const test = new TestMemoLambdaLiteralMemoization()
        const root = testRoot(
            /** @memo */
            () => { test.test() }
        )
        assertResultArray(test.log,
            "method with memo lambda parameter call",
            "method with memo lambda parameter"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(test.log,
            "method with memo lambda parameter call",
            "method with memo lambda parameter",
            "method with memo lambda parameter call"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(test.log,
            "method with memo lambda parameter call",
            "method with memo lambda parameter",
            "method with memo lambda parameter call",
            "method with memo lambda parameter call"
        )
    })
})

suite("[ARKTS+MEMO PLUGIN] Functions with receiver", () => {
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

    test.expectFailure("conditional expectFailure", "Lambda function with receiver", () => {
        const instance = new TestLambdaWithReceiver()
        const root = testRoot(instance.test)
        assertResultArray(instance.log,
            "lambda with receiver call",
            "lambda with receiver",
            "lambda with receiver",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "lambda with receiver call",
            "lambda with receiver",
            "lambda with receiver",
            "lambda with receiver call",
        )
    })
})

export const __ARKTEST__ = "ui2abc_test.test"
