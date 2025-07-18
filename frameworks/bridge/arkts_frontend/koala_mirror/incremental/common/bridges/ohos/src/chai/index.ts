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

import { expect } from "@ohos/hypium"

export interface Assert {
    (expression: any, message?: string): asserts expression

    /**
     * Asserts non-strict equality (==) of actual and expected.
     */
    equal<T>(actual: T, expected: T, message?: string): void

    /**
     * Asserts non-strict inequality (!=) of actual and expected.
     */
    notEqual<T>(actual: T, expected: T, message?: string): void

    /**
     * Asserts strict equality (===) of actual and expected.
     */
    strictEqual<T>(actual: T, expected: T, message?: string): void

    /**
     * Asserts strict inequality (!==) of actual and expected.
     */
    notStrictEqual<T>(actual: T, expected: T, message?: string): void

    deepEqual(actual: any, expected: any, message?: string): void

    notDeepEqual(actual: any, expected: any, message?: string): void

    isTrue(value: any, message?: string): void

    isFalse(value: any, message?: string): void

    closeTo(actual: number, expected: number, delta: number, message?: string): void

    fail(message?: string): void

    isNull(value: any, message?: string): void

    isNotNull(value: any, message?: string): void

    instanceOf(value: any, constructor: Function, message?: string): void

    isAtLeast(valueToCheck: number, valueToBeAtLeast: number, message?: string): void

    exists(value: any, message?: string): void

    throw(fn: () => void, message?: string): void

    throws(fn: () => void, message?: string): void

    isAbove(valueToCheck: number, valueToBeAbove: number, message?: string): void

    isBelow(valueToCheck: number, valueToBeBelow: number, message?: string): void

    match(value: string, regexp: RegExp, message?: string): void

    isDefined(value: any, message?: string): void

    isUndefined(value: any, message?: string): void

    isEmpty(object: any, message?: string): void

    isNotEmpty(object: any, message?: string): void
}

// Improve: the 'message' arg is ignored

export var assert: Assert = ((expression: any, message?: string): void => {
    expect(Boolean(expression)).assertTrue()
}) as Assert

assert.equal = <T>(actual: T, expected: T, message?: string): void => {
    expect(actual).assertEqual(expected)
}

assert.notEqual = <T>(actual: T, expected: T, message?: string): void => {
    // Improve: not accurate impl, because compared values are not printed
    expect(actual != expected).assertTrue()
}

assert.strictEqual = <T>(actual: T, expected: T, message?: string): void => {
    // Improve: not accurate impl, because compared values are not printed
    expect(actual === expected).assertTrue()
}

assert.notStrictEqual = <T>(actual: T, expected: T, message?: string): void => {
    // Improve: not accurate impl, because compared values are not printed
    expect(actual !== expected).assertTrue()
}

assert.deepEqual = (actual: any, expected: any, message?: string): void => {
    // Improve: implement
    expect(actual).assertEqual(actual/*expected*/)
}

assert.notDeepEqual = (actual: any, expected: any, message?: string): void => {
    // Improve: implement
    expect(actual).assertEqual(actual/*expected*/)
}

assert.isTrue = (value: any, message?: string): void => {
    expect(value).assertTrue()
}

assert.isFalse = (value: any, message?: string): void => {
    expect(value).assertFalse()
}

assert.closeTo = (actual: number, expected: number, delta: number, message?: string): void => {
    // implementation of 'assertClose' does not fit:
    // expect(actual).assertClose(expected, delta)

    const diff = Math.abs(actual - expected)
    if (diff == delta)
        expect(diff).assertEqual(delta)
    else
        expect(diff).assertLess(delta)
}

assert.fail = (message?: string): void => {
    expect().assertFail()
}

assert.isNull = (value: any, message?: string): void => {
    expect(value).assertNull()
}

assert.isNotNull = (value: any, message?: string): void => {
    expect(value ? null : value).assertNull()
}

assert.instanceOf = (value: any, constructor: Function, message?: string): void => {
    // Improve: not accurate impl
    // expect(value).assertInstanceOf(constructor.name)
    expect(value instanceof constructor).assertTrue()
}

assert.isAtLeast = (valueToCheck: number, valueToBeAtLeast: number, message?: string): void => {
    if (valueToCheck == valueToBeAtLeast)
        expect(valueToCheck).assertEqual(valueToBeAtLeast)
    else
        expect(valueToCheck).assertLarger(valueToBeAtLeast)
}

assert.exists = (value: any, message?: string): void => {
    // Improve: not accurate impl
    expect(value == null).assertFalse()
}

assert.throw = (fn: () => void, message?: string): void => {
    let fnWrapper = () => {
        try {
            fn()
        } catch (e) {
            throw new Error("fn thrown exception")
        }
    }
    expect(fnWrapper).assertThrowError("fn thrown exception")
}

assert.throws = (fn: () => void, message?: string): void => {
    assert.throw(fn, message)
}

assert.isAbove = (valueToCheck: number, valueToBeAbove: number, message?: string): void => {
    expect(valueToCheck).assertLarger(valueToBeAbove)
}

assert.isBelow = (valueToCheck: number, valueToBeBelow: number, message?: string): void => {
    expect(valueToCheck).assertLess(valueToBeBelow)
}

assert.match = (value: string, regexp: RegExp, message?: string): void => {
    // Improve: not accurate impl
    expect(regexp.test(value)).assertTrue()
}

assert.isDefined = (value: any, message?: string): void => {
    // Improve: not accurate impl
    expect(value === undefined).assertFalse()
}

assert.isUndefined = (value: any, message?: string): void => {
    expect(value).assertUndefined()
}

assert.isEmpty = (object: any, message?: string): void => {
    // Improve: implement
    expect(object !== undefined).assertTrue()
}

assert.isNotEmpty = (object: any, message?: string): void => {
    // Improve: implement
    expect(object !== undefined).assertTrue()
}


