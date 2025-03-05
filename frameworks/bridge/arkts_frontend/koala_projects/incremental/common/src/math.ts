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

import { asFloat64, asString, float64 } from "@koalaui/compat"

/**
 * Computes the linear interpolation between `source` and `target` based on `weight`.
 *
 * @param weight - interpolation factor in the range [0..1]
 * @param source - a value corresponding to weight 0
 * @param target - a value corresponding to weight 1
 * @returns interpolated value
 */
export function lerp(weight: float64, source: float64, target: float64): float64 {
    return source * (1.0 - weight) + target * weight
}

/**
 * Clamps a {@link value} within the specified range.
 *
 * @param value - a value to clamp
 * @param min - the lower boundary of the range
 * @param max - the upper boundary of the range
 * @returns `min` if `value` is less than `min`,
 *          `max` if `value` is greater than `max`,
 *          `value` otherwise
 */
export function clamp(value: float64, min: float64, max: float64): float64 {
    return value <= min ? min : value >= max ? max : value
}

/**
 * Calculates the difference between the argument and
 * the largest (closest to positive infinity) integer value
 * that is less than or equal to the argument.
 *
 * @param value a floating-point value to process
 * @returns a floor modulus of the given value in the range [0..1)
 */
export function modulo(value: float64): float64 {
    // The casts below are needed since floor returns double in ArkTS
    const modulo: float64 = value - Math.floor(value)
    return (modulo < 1.0) ? modulo : 0.0
}

/**
 * @param str a string to parse
 * @param name a name for error message
 * @param verify whether to verify parsing validity
 * @returns a floating-point number
 * @throws Error if `str` cannot be parsed
 */
export function parseNumber(str: string, name: string = "number", verify: boolean = false): float64 {
    if (str != "") { // do not parse empty string to 0
        // ArkTS does not support NaN, isNaN, parseFloat
        const value = asFloat64(str)
        if (verify) {
            const reverseStr = asString(value)
            if (reverseStr !== undefined && reverseStr?.length == str.length && reverseStr == str) {
                return value
            }
        }
        else {
            return value
        }
    }
    throw new Error(`cannot parse ${name}: "${str}"`)
}

/**
 * An ArkTS-compliant replacement for {@link isFinite}.
 */
export function isFiniteNumber(number: float64): boolean {
    // With Node.js:
    // isFiniteNumber(Number.NEGATIVE_INFINITY) == false
    // isFiniteNumber(Number.POSITIVE_INFINITY) == false
    // isFiniteNumber(NaN) == false
    return number >= Number.MIN_SAFE_INTEGER && number <= Number.MAX_SAFE_INTEGER
}

export function getDistancePx(startX: float64, startY: float64, endX: float64, endY: float64): float64 {
    const cathetA = Math.abs(endX - startX)
    const cathetB = Math.abs(endY - startY)
    return Math.sqrt(cathetA * cathetA + cathetB * cathetB) as float64
}