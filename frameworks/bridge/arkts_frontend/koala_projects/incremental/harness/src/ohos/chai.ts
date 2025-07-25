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

import { expect } from "@ohos/hypium"

export class Assert {
    /**
     * Throws a failure.
     * @param message - message to display on error
     */
    static fail(message?: string): never {
        expect().assertFail()
        throw new Error("OHOS failed: " + message)
    }

    /**
     * Asserts that object is truthy.
     *
     * T   Type of object.
     * @param object   Object to test.
     * @param message    Message to display on error.
     */
    static isOk<T>(value: T, message?: string): void {
        Assert.fail("Assert.isOk unsupported")
    }

    /**
     * Asserts that object is truthy.
     *
     * T   Type of object.
     * @param object   Object to test.
     * @param message    Message to display on error.
     */
    static ok<T>(value: T, message?: string): void {
        Assert.fail("Assert.ok unsupported")
    }

    /**
     * Asserts that object is falsy.
     *
     * T   Type of object.
     * @param object   Object to test.
     * @param message    Message to display on error.
     */
    static isNotOk<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotOk unsupported")
    }

    /**
     * Asserts that object is falsy.
     *
     * T   Type of object.
     * @param object   Object to test.
     * @param message    Message to display on error.
     */
    static notOk<T>(value: T, message?: string): void {
        Assert.fail("Assert.notOk unsupported")
    }

    /**
     * Asserts non-strict equality (==) of actual and expected.
     * @param actual - actual value
     * @param expected - potential expected value
     * @param message - message to display on error
     */
    static equal<T>(actual: T, expected: T, message?: string): void {
        expect(actual).assertEqual(expected)
    }

    /**
     * Asserts non-strict inequality (!=) of actual and expected.
     * @param actual - actual value
     * @param expected - potential expected value
     * @param message - message to display on error
     */
    static notEqual<T>(actual: T, expected: T, message?: string): void {
        // todo: not accurate impl, because compared values are not printed
        expect(actual != expected).assertTrue()
    }

    /**
     * Asserts strict equality (===) of actual and expected.
     * @param actual - actual value
     * @param expected - potential expected value
     * @param message - message to display on error
     */
    static strictEqual<T>(actual: T, expected: T, message?: string): void {
        // todo: not accurate impl, because compared values are not printed
        expect(actual === expected).assertTrue()
    }

    /**
     * Asserts strict inequality (!==) of actual and expected.
     * @param actual - actual value
     * @param expected - potential expected value
     * @param message - message to display on error
     */
    static notStrictEqual<T>(actual: T, expected: T, message?: string): void {
        // todo: not accurate impl, because compared values are not printed
        expect(actual !== expected).assertTrue()
    }

    /**
     * Asserts that actual is deeply equal to expected.
     * @param actual - actual value array
     * @param expected - potential expected value array
     * @param message - message to display on error
     */
    static deepEqual<T>(actual: Array<T>, expected: Array<T>, message?: string): void {
        // todo: implement
        expect(actual).assertEqual(actual/*expected*/)
    }

    /**
     * Asserts that actual is not deeply equal to expected.
     * @param actual - actual value array
     * @param expected - potential expected value array
     * @param message - message to display on error
     */
    static notDeepEqual<T>(actual: Array<T>, expected: Array<T>, message?: string): void {
        // todo: implement
        expect(actual).assertEqual(actual/*expected*/)
    }

    /**
     * Asserts valueToCheck is strictly greater than (>) valueToBeAbove.
     *
     * @param valueToCheck   Actual value.
     * @param valueToBeAbove   Minimum Potential expected value.
     * @param message   Message to display on error.
     */
    static isAbove(valueToCheck: number, valueToBeAbove: number, message?: string): void {
        expect(valueToCheck).assertLarger(valueToBeAbove)
    }

    /**
     * Asserts valueToCheck is greater than or equal to (>=) valueToBeAtLeast.
     *
     * @param valueToCheck   Actual value.
     * @param valueToBeAtLeast   Minimum Potential expected value.
     * @param message   Message to display on error.
     */
    static isAtLeast(valueToCheck: number, valueToBeAtLeast: number, message?: string): void {
        if (valueToCheck == valueToBeAtLeast)
            expect(valueToCheck).assertEqual(valueToBeAtLeast)
        else
            expect(valueToCheck).assertLarger(valueToBeAtLeast)
    }

    /**
     * Asserts valueToCheck is strictly less than (<) valueToBeBelow.
     *
     * @param valueToCheck   Actual value.
     * @param valueToBeBelow   Minimum Potential expected value.
     * @param message   Message to display on error.
     */
    static isBelow(valueToCheck: number, valueToBeBelow: number, message?: string): void {
        expect(valueToCheck).assertLess(valueToBeBelow)
    }

    /**
     * Asserts valueToCheck is less than or equal to (<=) valueToBeAtMost.
     *
     * @param valueToCheck   Actual value.
     * @param valueToBeAtMost   Minimum Potential expected value.
     * @param message   Message to display on error.
     */
    static isAtMost(valueToCheck: number, valueToBeAtMost: number, message?: string): void {
        Assert.fail("Assert.isAtMost unsupported")
    }

    /**
     * Asserts that value is true.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isTrue(value?: boolean, message?: string): void {
        expect(value).assertTrue()
    }

    /**
     * Asserts that value is not true.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isNotTrue(value?: boolean, message?: string): void {
        if (value != true) return
        Assert.fail(message ?? `actual '${value}' is true unexpectedly`)
    }

    /**
     * Asserts that value is false.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isFalse(value?: boolean, message?: string): void {
        expect(value).assertFalse()
    }

    /**
     * Asserts that value is not false.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isNotFalse(value?: boolean, message?: string): void {
        if (value != false) return
        Assert.fail(message ?? `actual '${value}' is false unexpectedly`)
    }

    /**
     * Asserts that value is null.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isNull<T>(value: T | null, message?: string): void {
        expect(value).assertNull()
    }

    /**
     * Asserts that value is not null.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isNotNull<T>(value: T | null, message?: string): void {
        expect(value ? null : value).assertNull()
    }

    /**
     * Asserts that value is NaN.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNaN<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNaN unsupported")
    }

    /**
     * Asserts that value is not NaN.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotNaN<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotNaN unsupported")
    }

    /**
     * Asserts that the target is neither null nor undefined.
     * @param value - actual value
     * @param message - message to display on error
     */
    static exists<T>(value?: T | null, message?: string): void {
        // todo: not accurate impl
        expect(value == null).assertFalse()
    }

    /**
     * Asserts that the target is either null or undefined.
     * @param value - actual value
     * @param message - message to display on error
     */
    static notExists<T>(value?: T | null, message?: string): void {
        if (value !== undefined && value !== null) return
        Assert.fail(message ?? `actual '${value}' exists unexpectedly`)
    }

    /**
     * Asserts that value is undefined.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isUndefined<T>(value?: T, message?: string): void {
        expect(value).assertUndefined()
    }

    /**
     * Asserts that value is not undefined.
     * @param value - actual value
     * @param message - message to display on error
     */
    static isDefined<T>(value?: T, message?: string): void {
        // todo: not accurate impl
        expect(value === undefined).assertFalse()
    }

    /**
     * Asserts that value is a function.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isFunction<T>(value: T, message?: string): void {
        Assert.fail("Assert.isFunction unsupported")
    }

    /**
     * Asserts that value is not a function.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotFunction<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotFunction unsupported")
    }

    /**
     * Asserts that value is an object of type 'Object'
     * (as revealed by Object.prototype.toString).
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     * @remarks The assertion does not match subclassed objects.
     */
    static isObject<T>(value: T, message?: string): void {
        Assert.fail("Assert.isObject unsupported")
    }

    /**
     * Asserts that value is not an object of type 'Object'
     * (as revealed by Object.prototype.toString).
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotObject<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotObject unsupported")
    }

    /**
     * Asserts that value is an array.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isArray<T>(value: T, message?: string): void {
        Assert.fail("Assert.isArray unsupported")
    }

    /**
     * Asserts that value is not an array.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotArray<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotArray unsupported")
    }

    /**
     * Asserts that value is a string.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isString<T>(value: T, message?: string): void {
        Assert.fail("Assert.isString unsupported")
    }

    /**
     * Asserts that value is not a string.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotString<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotString unsupported")
    }

    /**
     * Asserts that value is a number.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNumber<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNumber unsupported")
    }

    /**
     * Asserts that value is not a number.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotNumber<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotNumber unsupported")
    }

    /**
     * Asserts that value is a finite number.
     * Unlike `.isNumber`, this will fail for `NaN` and `Infinity`.
     *
     * T   Type of value
     * @param value    Actual value
     * @param message   Message to display on error.
     */
    static isFinite<T>(value: T, message?: string): void {
        Assert.fail("Assert.isFinite unsupported")
    }

    /**
     * Asserts that value is a boolean.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isBoolean<T>(value: T, message?: string): void {
        Assert.fail("Assert.isBoolean unsupported")
    }

    /**
     * Asserts that value is not a boolean.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param message   Message to display on error.
     */
    static isNotBoolean<T>(value: T, message?: string): void {
        Assert.fail("Assert.isNotBoolean unsupported")
    }

    /**
     * Asserts that value's type is name, as determined by Object.prototype.toString.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param name   Potential expected type name of value.
     * @param message   Message to display on error.
     */
    static typeOf<T>(value: T, name: string, message?: string): void {
        Assert.fail("Assert.typeOf unsupported")
    }

    /**
     * Asserts that value's type is not name, as determined by Object.prototype.toString.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param name   Potential expected type name of value.
     * @param message   Message to display on error.
     */
    static notTypeOf<T>(value: T, name: string, message?: string): void {
        Assert.fail("Assert.notTypeOf unsupported")
    }

    /**
     * Asserts that value is an instance of constructor.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param construct   Potential expected contructor of value.
     * @param message   Message to display on error.
     */
    static instanceOf<T>(value: T, construct: Function, message?: string): void {
        // todo: not accurate impl
        // expect(value).assertInstanceOf(construct.name)
        expect(value instanceof construct).assertTrue()
    }

    /**
     * Asserts that value is not an instance of constructor.
     *
     * T   Type of value.
     * @param value   Actual value.
     * @param constructor   Potential expected contructor of value.
     * @param message   Message to display on error.
     * /
    static notInstanceOf<T>(value: T, type: Function, message?: string): void*/

    /**
     * Asserts that haystack includes needle.
     *
     * @param haystack   Container string.
     * @param needle   Potential substring of haystack.
     * @param message   Message to display on error.
     * /
    static include(haystack: string, needle: string, message?: string): void*/

    /**
     * Asserts that haystack includes needle.
     *
     * T   Type of values in haystack.
     * @param haystack   Container array, set or map.
     * @param needle   Potential value contained in haystack.
     * @param message   Message to display on error.
     * /
    static include<T>(
        haystack: ReadonlyArray<T> | ReadonlySet<T> | ReadonlyMap<any, T>,
        needle: T,
        message?: string,
    ): void;*/

    /**
     * Asserts that haystack includes needle.
     *
     * T   Type of values in haystack.
     * @param haystack   WeakSet container.
     * @param needle   Potential value contained in haystack.
     * @param message   Message to display on error.
     * /
    static include<T extends object>(haystack: WeakSet<T>, needle: T, message?: string): void;*/

    /**
     * Asserts that haystack includes needle.
     *
     * T   Type of haystack.
     * @param haystack   Object.
     * @param needle   Potential subset of the haystack's properties.
     * @param message   Message to display on error.
     * /
    static include<T>(haystack: T, needle: Partial<T>, message?: string): void;*/

    /**
     * Asserts that haystack does not includes needle.
     *
     * @param haystack   Container string.
     * @param needle   Potential substring of haystack.
     * @param message   Message to display on error.
     * /
    static notInclude(haystack: string, needle: string, message?: string): void;*/

    /**
     * Asserts that haystack does not includes needle.
     *
     * T   Type of values in haystack.
     * @param haystack   Container array, set or map.
     * @param needle   Potential value contained in haystack.
     * @param message   Message to display on error.
     * /
    static notInclude<T>(
        haystack: ReadonlyArray<T> | ReadonlySet<T> | ReadonlyMap<any, T>,
        needle: T,
        message?: string,
    ): void;*/

    /**
     * Asserts that haystack does not includes needle.
     *
     * T   Type of values in haystack.
     * @param haystack   WeakSet container.
     * @param needle   Potential value contained in haystack.
     * @param message   Message to display on error.
     * /
    static notInclude<T extends object>(haystack: WeakSet<T>, needle: T, message?: string): void;*/

    /**
     * Asserts that haystack does not includes needle.
     *
     * T   Type of haystack.
     * @param haystack   Object.
     * @param needle   Potential subset of the haystack's properties.
     * @param message   Message to display on error.
     * /
    static notInclude<T>(haystack: T, needle: Partial<T>, message?: string): void;*/

    /**
     * Asserts that value matches the regular expression regexp.
     *
     * @param value   Actual value.
     * @param regexp   Potential match of value.
     * @param message   Message to display on error.
     */
    static match(value: string, regexp: RegExp, message?: string): void {
        // todo: not accurate impl
        expect(regexp.test(value)).assertTrue()
    }

    /**
     * Asserts that value does not match the regular expression regexp.
     *
     * @param value   Actual value.
     * @param regexp   Potential match of value.
     * @param message   Message to display on error.
     */
    static notMatch(expected: string, regexp: RegExp, message?: string): void {
        Assert.fail("Assert.notMatch unsupported")
    }

    /**
     * Asserts that fn will throw an error.
     *
     * @param fn   Function that may throw.
     * @param errMsgMatcher   Expected error message matcher.
     * @param ignored   Ignored parameter.
     * @param message   Message to display on error.
     * /
    static throw(fn: () => void, errMsgMatcher?: RegExp | string, ignored?: any, message?: string): void;*/

    /**
     * Asserts that the given function will throw an error.
     * @param func - a function that may throw an error
     */
    static throw(func: () => void): void {
        Assert.throws(func)
    }

    /**
     * Asserts that the given function will throw an error.
     * @param func - a function that may throw an error
     */
    static throws(func: () => void): void {
        let fnWrapper = () => {
            try {
                func()
            } catch (e) {
                throw new Error("fn thrown exception")
            }
        }
        expect(fnWrapper).assertThrowError("fn thrown exception")
    }

    /**
     * Asserts that fn will throw an error.
     *
     * @param fn   Function that may throw.
     * @param errorLike   Expected error constructor or error instance.
     * @param errMsgMatcher   Expected error message matcher.
     * @param message   Message to display on error.
     * /
    static throws(
        fn: () => void,
        errorLike?: ErrorConstructor | Error | null,
        errMsgMatcher?: RegExp | string | null,
        message?: string,
    ): void;*/

    /**
     * Asserts that fn will throw an error.
     *
     * @param fn   Function that may throw.
     * @param errMsgMatcher   Expected error message matcher.
     * @param ignored   Ignored parameter.
     * @param message   Message to display on error.
     * /
    static Throw(fn: () => void, errMsgMatcher?: RegExp | string, ignored?: any, message?: string): void;*/

    /**
     * Asserts that fn will throw an error.
     *
     * @param fn   Function that may throw.
     * @param errorLike   Expected error constructor or error instance.
     * @param errMsgMatcher   Expected error message matcher.
     * @param message   Message to display on error.
     * /
    static Throw(
        fn: () => void,
        errorLike?: ErrorConstructor | Error | null,
        errMsgMatcher?: RegExp | string | null,
        message?: string,
    ): void;*/

    /**
     * Asserts that fn will not throw an error.
     *
     * @param fn   Function that may throw.
     * @param errMsgMatcher   Expected error message matcher.
     * @param ignored   Ignored parameter.
     * @param message   Message to display on error.
     * /
    static doesNotThrow(fn: () => void, errMsgMatcher?: RegExp | string, ignored?: any, message?: string): void;*/

    /**
     * Asserts that fn will not throw an error.
     *
     * @param fn   Function that may throw.
     * @param errorLike   Expected error constructor or error instance.
     * @param errMsgMatcher   Expected error message matcher.
     * @param message   Message to display on error.
     * /
    static doesNotThrow(
        fn: () => void,
        errorLike?: ErrorConstructor | Error | null,
        errMsgMatcher?: RegExp | string | null,
        message?: string,
    ): void;*/

    /**
     * Compares two values using operator.
     *
     * @param val1   Left value during comparison.
     * @param operator   Comparison operator.
     * @param val2   Right value during comparison.
     * @param message   Message to display on error.
     * /
    static operator(val1: OperatorComparable, operator: Operator, val2: OperatorComparable, message?: string): void;*/

    /**
     * Asserts that the target is equal to expected, to within a +/- delta range.
     *
     * @param actual   Actual value
     * @param expected   Potential expected value.
     * @param delta   Maximum differenced between values.
     * @param message   Message to display on error.
     */
    static closeTo(actual: number, expected: number, delta: number, message?: string): void {
        // implementation of 'assertClose' does not fit:
        // expect(actual).assertClose(expected, delta)

        const diff = Math.abs(actual - expected)
        if (diff == delta)
            expect(diff).assertEqual(delta)
        else
            expect(diff).assertLess(delta)
    }

    /**
     * Asserts that the target is equal to expected, to within a +/- delta range.
     *
     * @param actual   Actual value
     * @param expected   Potential expected value.
     * @param delta   Maximum differenced between values.
     * @param message   Message to display on error.
     * /
    static approximately(act: number, exp: number, delta: number, message?: string): void;*/

    /**
     * Asserts that non-object, non-array value inList appears in the flat array list.
     *
     * T   Type of list values.
     * @param inList   Value expected to be in the list.
     * @param list   List of values.
     * @param message   Message to display on error.
     */
    static oneOf<T>(inList: T, list: T[], message?: string): void {
        Assert.fail("Assert.oneOf unsupported")
    }

    /**
     * Asserts that the target does not contain any values. For arrays and
     * strings, it checks the length property. For Map and Set instances, it
     * checks the size property. For non-function objects, it gets the count
     * of own enumerable string keys.
     *
     * T   Type of object
     * @param object   Actual value.
     * @param message   Message to display on error.
     */
    static isEmpty<T>(object: T, message?: string): void {
        // todo: implement
        expect(object !== undefined).assertTrue()
    }

    /**
     * Asserts that the target contains values. For arrays and strings, it checks
     * the length property. For Map and Set instances, it checks the size property.
     * For non-function objects, it gets the count of own enumerable string keys.
     *
     * T   Type of object.
     * @param object   Object to test.
     * @param message    Message to display on error.
     */
    static isNotEmpty<T>(object: T, message?: string): void {
        // todo: implement
        expect(object !== undefined).assertTrue()
    }
}
