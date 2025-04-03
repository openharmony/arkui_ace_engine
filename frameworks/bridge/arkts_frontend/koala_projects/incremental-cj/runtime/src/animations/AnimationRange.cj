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
package KoalaRuntime.animations

import std.collection.*
import std.math.*

/**
 * Declares a function that can convert a state to a value.
 * Note that some easings may produce a state outside the `[0..1]` range.
 */
public type AnimationRange<Value> = (value: Float32) -> Value

/**
 * @param from - a first base array that corresponds to the `0` state
 * @param to - a second base array that corresponds to the `1` state
 * @returns a function to generate interpolated values
 * @see ColorAnimationRange
 * @see NumberAnimationRange
 */
public func ArrayAnimationRange<Value>(
    isfrom: Array<Float32>,
    to: Array<Float32>,
    compute: (array: ArrayList<Float32>) -> Value
): AnimationRange<Value> {
    let length = isfrom.size
    if (to.size != length) {
        throw IllegalArgumentException("sizes of input arrays do not match")
    }
    let array = ArrayList<Float32>(length)
    return {
        weight: Float32 =>
        if (isfrom.size != length) {
            throw IllegalArgumentException("size of the first input array is changed unexpectedly")
        }
        if (to.size != length) {
            throw IllegalArgumentException("size of the second input array is changed unexpectedly")
        }
        for (index in 0..length - 1) {
            array[index] = lerp(weight, isfrom[index], to[index])
        }
        return compute(array)
    }
}

/**
 * @param from - a first base value that corresponds to the `0` state
 * @param to - a second base value that corresponds to the `1` state
 * @returns a function to generate interpolated numbers
 */
public func NumberAnimationRange(isfrom: Float32, to: Float32): AnimationRange<Float32> {
    if (isfrom == 0.0 && to == 1.0) {
        return {state: Float32 => state}
    }
    if (!isfrom.isNormal()) {
        throw IllegalArgumentException("illegal start value: ${isfrom}")
    }
    if (!to.isNormal()) {
        throw IllegalArgumentException("illegal end value: ${to}")
    }
    return {weight: Float32 => lerp(weight, isfrom, to)}
}

/**
 * Computes the linear interpolation between `source` and `target` based on `weight`.
 *
 * @param weight - interpolation factor in the range [0..1]
 * @param source - a value corresponding to weight 0
 * @param target - a value corresponding to weight 1
 * @returns interpolated value
 */
public func lerp(weight: Float32, source: Float32, target: Float32) {
    return source * (1.0 - weight) + target * weight
}
