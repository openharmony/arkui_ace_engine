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

import { float64, isFiniteNumber, lerp } from "@koalaui/common"

/**
 * Declares a function that can convert a state to a value.
 * Note that some easings may produce a state outside the `[0..1]` range.
 */
export type AnimationRange<Value> = (value: float64) => Value

/**
 * @param from - a first base array that corresponds to the `0` state
 * @param to - a second base array that corresponds to the `1` state
 * @returns a function to generate interpolated values
 * @see ColorAnimationRange
 * @see NumberAnimationRange
 */
export function ArrayAnimationRange<Value>(from: ReadonlyArray<float64>, to: ReadonlyArray<float64>, compute: (array: ReadonlyArray<float64>) => Value): AnimationRange<Value> {
    const length = from.length
    if (to.length != length) throw new Error("sizes of input arrays do not match")
    const array = new Array<float64>(length)
    return (weight: float64) => {
        if (from.length != length) throw new Error("size of the first input array is changed unexpectedly")
        if (to.length != length) throw new Error("size of the second input array is changed unexpectedly")
        for (let index = 0; index < length; index++) {
            array[index] = lerp(weight, from[index], to[index])
        }
        return compute(array)
    }
}

/**
 * @param from - a first base value that corresponds to the `0` state
 * @param to - a second base value that corresponds to the `1` state
 * @returns a function to generate interpolated numbers
 */
export function NumberAnimationRange(from: float64, to: float64): AnimationRange<float64> {
    if (from == 0 && to == 1) return (state: float64) => state
    if (!isFiniteNumber(from)) throw new Error("illegal start value: " + from)
    if (!isFiniteNumber(to)) throw new Error("illegal end value: " + to)
    return (weight: float64) => lerp(weight, from, to)
}
