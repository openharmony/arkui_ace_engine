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

const stack = new Array<Test>()
const array = new Array<Test>()
let passedCount = 0
let failedCount = 0

function addTest(test: Test, content?: () => void) {
    array.push(test)
    const length = stack.length
    const parent = 0 < length ? stack[length - 1] : undefined
    if (parent?.suite == false) throw new Error("test is already running")
    try {
        console.log(test.prefix + test.name)
        stack.push(test)
        content?.()
        if (!test.suite) passedCount++
    } catch (error) {
        if (!test.suite) failedCount++
        test.passed = false
        console.log(error instanceof Error ? error.stack : error)
    } finally {
        stack.pop()
        if (parent) {
            if (!test.passed) parent.passed = false
        } else {
            console.log("-".repeat(50))
            array.forEach(logFailedTest)
            console.log("failed tests: " + failedCount)
            console.log("passed tests: " + passedCount)
            if (!test.passed) throw new Error("TEST FAILED")
        }
    }
}

function logFailedTest(test: Test) {
    if (!test.passed) console.log(test.prefix + "failed " + test.name)
}

class Test {
    readonly name: string
    readonly suite: boolean
    readonly prefix: string
    public passed: boolean = true
    constructor(name: string, suite: boolean) {
        this.name = name
        this.suite = suite
        this.prefix = "  ".repeat(stack.length)
    }
}

export function test(name: string, content?: () => void) {
    addTest(new Test(`test: "${name}"`, false), content)
}

export function suite(name: string, content?: () => void) {
    addTest(new Test(`suite: "${name}"`, true), content)
}

export function suiteSetup(name: string, content?: () => void) {
    throw new Error("unsupported suiteSetup: " + name)
}

export function startTests(generateGolden: boolean = false) {
    throw new Error("unsupported startTests: " + generateGolden)
}
