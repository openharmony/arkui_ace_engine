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

import { errorAsString, int32 } from "@koalaui/common"

const stack = new Array<Test>()
const array = new Array<Test>()

const PASSED_PREFIX = "✅ \x1b[32m passed \x1b[0m"
const FAILED_PREFIX = "❌ \x1b[31m failed \x1b[0m"
const SKIPPED_PREFIX = "➡️  \x1b[36m skipped \x1b[0m"
const FAILED_AS_EXPECTED_PREFIX = "⚠️  \x1b[33m expected failed \x1b[0m"
const PASSED_UNEXPECTEDLY_PREFIX = "❌ \x1b[31m passed unexpectedly \x1b[0m"

export enum TestKind {
    PASS, // test something and expect it is passed
    FAIL, // test something and expect it is failed
    SKIP, // skip something from testing
}

export function doTest(kind: TestKind, name: string, content?: () => void, suite: boolean = false) {
    const time = Date.now()
    const test = new Test(kind, name, suite)
    console.log(`start processing ${name}`)
    array.push(test)
    const length = stack.length
    const parent = 0 < length ? stack[length - 1] : undefined
    if (parent?.suite == false) throw new Error("test is already running")

    try {
        stack.push(test)
        if (kind != TestKind.SKIP) content?.()
    } catch (error) {
        test.error = error instanceof Error
            ? errorAsString(error)
            : JSON.stringify(error)
        console.log(test.error)
    } finally {
        stack.pop()
        console.log(`${Date.now() - time}ms to process ${name}`)
        if (parent) {
            if (test.passed == (test.kind == TestKind.FAIL)) parent.error = ""
        } else {
            logResults(array.splice(0, array.length))
            if (!test.passed) throw new Error("TEST FAILED")
        }
    }
}

function logResults(array: ReadonlyArray<Test>) {
    console.log("-".repeat(50))
    const map = new Map<string, int32>
    array.forEach((test: Test) => {
        const result = test.result
        console.log(test.prefix + result + test.name)
        if (!test.suite) map.set(result, (map.get(result) ?? 0) + 1)
    })
    console.log("-".repeat(50))
    logResult(map, PASSED_PREFIX)
    logResult(map, SKIPPED_PREFIX)
    logResult(map, FAILED_AS_EXPECTED_PREFIX)
    logResult(map, PASSED_UNEXPECTEDLY_PREFIX)
    logResult(map, FAILED_PREFIX)
}

function logResult(map: Map<string, int32>, key: string) {
    const count = map.get(key) ?? 0
    if (count > 0) console.log(key + "tests: " + count)
}

class Test {
    readonly kind: TestKind
    readonly name: string
    readonly suite: boolean
    readonly prefix: string
    error: string | undefined = undefined
    constructor(kind: TestKind, name: string, suite: boolean = false) {
        this.kind = kind
        this.name = name
        this.suite = suite
        this.prefix = "  ".repeat(stack.length + 1)
    }
    get passed(): boolean {
        return this.error === undefined
    }
    get result(): string {
        if (this.kind == TestKind.PASS) {
            return this.passed ? PASSED_PREFIX : FAILED_PREFIX
        }
        if (this.kind == TestKind.FAIL) {
            return this.passed ? PASSED_UNEXPECTEDLY_PREFIX : FAILED_AS_EXPECTED_PREFIX
        }
        return SKIPPED_PREFIX
    }
}
